/*
 * Source code from 'Incremental-Fluids'
 * link: https://github.com/tunabrain/incremental-fluids/tree/master/2-better-advection
 */

#include "fluid_solver.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <future>
#include <memory>
#include <utility>
#include <vector>

namespace {

const double kEps = 1e-4;
const double kTimestep = 0.05;

/* Linear intERPolate for x ranging from 0 to 1
 */
double LERPHelper(double a, double b, double x) {
  return a * (1.0 - x) + b * x;
}

/* Cubic intERPolate using samples a through d for x ranging from 0 to 1
 * A Catmull-Rom spline is used. Over- and undershoots are clamped to prevent blow-up
 */
double CERPHelper(double a, double b, double c, double d, double x) {
  double xsq = x * x;
  double xcu = xsq * x;

  double minV = std::min(a, std::min(b, std::min(c, d)));
  double maxV = std::max(a, std::max(b, std::max(c, d)));

  double t = a * (0.0 - 0.5 * x + 1.0 * xsq - 0.5 * xcu) + b * (1.0 + 0.0 * x - 2.5 * xsq + 1.5 * xcu) +
             c * (0.0 + 0.5 * x + 2.0 * xsq - 1.5 * xcu) + d * (0.0 + 0.0 * x - 0.5 * xsq + 0.5 * xcu);

  return std::min(std::max(t, minV), maxV);
}

}  // namespace

namespace bench::tp {

namespace detail {
FluidQuantity::FluidQuantity(int w, int h, double ox, double oy, double hx)
    : src(w * h, 0.0), dst(w * h, 0.0), w(w), h(h), ox(ox), oy(oy), hx(hx) {
}

void FluidQuantity::RungeKutta3(double& x, double& y, const FluidQuantity& u, const FluidQuantity& v) const {
  const double first_u = u.LERP(x, y) / hx;
  const double first_v = v.LERP(x, y) / hx;

  const double mid_x = x - 0.5 * kTimestep * first_u;
  const double mid_y = y - 0.5 * kTimestep * first_v;

  const double mid_u = u.LERP(mid_x, mid_y) / hx;
  const double mid_v = v.LERP(mid_x, mid_y) / hx;

  const double lastX = x - 0.75 * kTimestep * mid_u;
  const double lastY = y - 0.75 * kTimestep * mid_v;

  const double last_u = u.LERP(lastX, lastY);
  const double last_v = v.LERP(lastX, lastY);

  x -= kTimestep * ((2.0 / 9.0) * first_u + (3.0 / 9.0) * mid_u + (4.0 / 9.0) * last_u);
  y -= kTimestep * ((2.0 / 9.0) * first_v + (3.0 / 9.0) * mid_v + (4.0 / 9.0) * last_v);
}

void FluidQuantity::Flip() {
  swap(src, dst);
}

double FluidQuantity::At(int x, int y) const {
  return src[x + y * w];
}

double& FluidQuantity::At(int x, int y) {
  return src[x + y * w];
}

double FluidQuantity::LERP(double x, double y) const {
  x = std::min(std::max(x - ox, 0.0), w - 1.001);
  y = std::min(std::max(y - oy, 0.0), h - 1.001);
  int ix = static_cast<int>(x);
  int iy = static_cast<int>(y);
  x -= ix;
  y -= iy;

  const double x00 = At(ix + 0, iy + 0), x10 = At(ix + 1, iy + 0);
  const double x01 = At(ix + 0, iy + 1), x11 = At(ix + 1, iy + 1);

  return LERPHelper(LERPHelper(x00, x10, x), LERPHelper(x01, x11, x), y);
}

double FluidQuantity::CERP(double x, double y) const {
  x = std::min(std::max(x - ox, 0.0), w - 1.001);
  y = std::min(std::max(y - oy, 0.0), h - 1.001);

  const int ix = static_cast<int>(x);
  const int iy = static_cast<int>(y);

  x -= ix;
  y -= iy;

  const int x0 = std::max(ix - 1, 0), x1 = ix, x2 = ix + 1, x3 = std::min(ix + 2, w - 1);
  const int y0 = std::max(iy - 1, 0), y1 = iy, y2 = iy + 1, y3 = std::min(iy + 2, h - 1);

  const double q0 = CERPHelper(At(x0, y0), At(x1, y0), At(x2, y0), At(x3, y0), x);
  const double q1 = CERPHelper(At(x0, y1), At(x1, y1), At(x2, y1), At(x3, y1), x);
  const double q2 = CERPHelper(At(x0, y2), At(x1, y2), At(x2, y2), At(x3, y2), x);
  const double q3 = CERPHelper(At(x0, y3), At(x1, y3), At(x2, y3), At(x3, y3), x);

  return CERPHelper(q0, q1, q2, q3, y);
}

void FluidQuantity::Advect(const FluidQuantity& u, const FluidQuantity& v) {
  for (int iy = 0, idx = 0; iy < h; iy++) {
    for (int ix = 0; ix < w; ix++, idx++) {
      double x = ix + ox;
      double y = iy + oy;

      /* First component: Integrate in time */
      RungeKutta3(x, y, u, v);

      /* Second component: Interpolate from grid */
      dst[idx] = CERP(x, y);
    }
  }
}

FluidSolver::FluidSolver(int w, int h, double density)
    : hx(1.0 / std::min(w, h)),
      density(density),
      d(w, h, 0.5, 0.5, hx),
      u(w + 1, h, 0.0, 0.5, hx),
      v(w, h + 1, 0.5, 0.0, hx),
      w(w),
      h(h),
      r(w * h, 0),
      p(w * h, 0) {
}

void FluidSolver::BuildRhs() {
  const double scale = 1.0 / hx;

  for (int y = 0, idx = 0; y < h; y++) {
    for (int x = 0; x < w; x++, idx++) {
      r[idx] = -scale * (u.At(x + 1, y) - u.At(x, y) + v.At(x, y + 1) - v.At(x, y));
    }
  }
}

void FluidSolver::Project(int limit) {
  const double scale = kTimestep / (density * hx * hx);

  double maxDelta;
  for (int iter = 0; iter < limit; iter++) {
    maxDelta = 0.0;
    for (int y = 0, idx = 0; y < h; y++) {
      for (int x = 0; x < w; x++, idx++) {
        const int idx = x + y * w;

        double diag = 0.0, offDiag = 0.0;

        if (x > 0) {
          diag += scale;
          offDiag -= scale * p[idx - 1];
        }
        if (y > 0) {
          diag += scale;
          offDiag -= scale * p[idx - w];
        }
        if (x < w - 1) {
          diag += scale;
          offDiag -= scale * p[idx + 1];
        }
        if (y < h - 1) {
          diag += scale;
          offDiag -= scale * p[idx + w];
        }

        const double newP = (r[idx] - offDiag) / diag;
        maxDelta = std::max(maxDelta, std::fabs(p[idx] - newP));
        p[idx] = newP;
      }
    }

    if (maxDelta < 1e-5) {
      return;
    }
  }
}

void FluidSolver::ApplyPressure() {
  const double scale = kTimestep / (density * hx);

  for (int y = 0, idx = 0; y < h; y++) {
    for (int x = 0; x < w; x++, idx++) {
      u.At(x, y) -= scale * p[idx];
      u.At(x + 1, y) += scale * p[idx];
      v.At(x, y) -= scale * p[idx];
      v.At(x, y + 1) += scale * p[idx];
    }
  }

  for (int y = 0; y < h; y++) {
    u.At(0, y) = u.At(w, y) = 0.0;
  }
  for (int x = 0; x < w; x++) {
    v.At(x, 0) = v.At(x, h) = 0.0;
  }
}

std::pair<size_t, size_t> FluidSolver::Dimensions() const {
  return {w, h};
}

}  // namespace detail

FluidSolverSuite::FluidSolverSuite()
    : _grid_size{2048},
      _problem_size{_grid_size * 3 * 4},
      _solver_answer(_grid_size, _grid_size, 0.1),
      _solver_blank(_grid_size, _grid_size, 0.1),
      _solver(_grid_size, _grid_size, 0.1) {
}

size_t FluidSolverSuite::ProblemSize() const {
  return _problem_size;
}

std::string FluidSolverSuite::Name() const {
  return "Fluid Solver";
}

bool FluidSolverSuite::CheckResult() {
  auto shape = _solver.Dimensions();
  for (size_t i = 0; i < shape.first * shape.second; i++) {
    if (std::abs(_solver.d.src[i] - _solver_answer.d.src[i]) > kEps) {
      return false;
    }
  }
  return true;
}

void FluidSolverSuite::Prepare() {
  _solver_blank = _solver_answer;

  for (size_t i = 0; i < 4; ++i) {
    _solver_answer.BuildRhs();
    _solver_answer.Project(1000);
    _solver_answer.ApplyPressure();

    _solver_answer.d.Advect(_solver_answer.u, _solver_answer.v);
    _solver_answer.u.Advect(_solver_answer.u, _solver_answer.v);
    _solver_answer.v.Advect(_solver_answer.u, _solver_answer.v);

    _solver_answer.d.Flip();
    _solver_answer.u.Flip();
    _solver_answer.v.Flip();
  }
}

void FluidSolverSuite::Teardown() {
}

void FluidSolverSuite::Run(std::function<std::future<void>(std::function<void(void)>&&)>&& async) {
  _solver = _solver_blank;

  for (size_t i = 0; i < 4; ++i) {
    auto tasks = std::vector<std::future<void>>();
    tasks.reserve(_grid_size);

    _solver.BuildRhs();
    _solver.Project(1000);
    _solver.ApplyPressure();

    for (size_t j = 0; j < _grid_size; ++j) {
      auto d_advect = [this, j] {
        size_t idx = 0;
        size_t iy = j;
        for (int ix = 0; ix < _solver.w; ix++, idx++) {
          double x = ix + _solver.d.ox;
          double y = iy + _solver.d.oy;

          _solver.d.RungeKutta3(x, y, _solver.u, _solver.v);

          _solver.d.dst[idx] = _solver.d.CERP(x, y);
        }
      };

      tasks.emplace_back(async(d_advect));
    }

    for (size_t j = 0; j < _grid_size; ++j) {
      auto u_advect = [this, j] {
        size_t idx = 0;
        size_t iy = j;
        for (int ix = 0; ix < _solver.w; ix++, idx++) {
          double x = ix + _solver.u.ox;
          double y = iy + _solver.u.oy;

          _solver.u.RungeKutta3(x, y, _solver.u, _solver.v);

          _solver.u.dst[idx] = _solver.u.CERP(x, y);
        }
      };

      tasks.emplace_back(async(u_advect));
    }

    for (size_t j = 0; j < _grid_size; ++j) {
      auto v_advect = [this, j] {
        size_t idx = 0;
        size_t iy = j;
        for (int ix = 0; ix < _solver.w; ix++, idx++) {
          double x = ix + _solver.v.ox;
          double y = iy + _solver.v.oy;

          _solver.v.RungeKutta3(x, y, _solver.u, _solver.v);

          _solver.v.dst[idx] = _solver.v.CERP(x, y);
        }
      };

      tasks.emplace_back(async(v_advect));
    }

    for (auto& task : tasks) {
      task.wait();
    }

    _solver.u.Flip();
    _solver.d.Flip();
    _solver.v.Flip();
  }
}

SuitePtr MakeFluidSolverSuite() {
  return std::make_unique<FluidSolverSuite>();
}

}  // namespace bench::tp
