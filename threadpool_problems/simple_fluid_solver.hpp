#pragma once
#include "../utils/threadpool_suite.hpp"

#include <functional>
#include <future>
#include <utility>
#include <vector>

namespace bench::tp {

namespace detail {
struct FluidQuantity final {
  FluidQuantity(int w, int h, double ox, double oy, double hx);

  /* Third order Runge-Kutta for velocity integration in time */
  void RungeKutta3(double& x, double& y, const FluidQuantity& u, const FluidQuantity& v) const;

  void Flip();

  double At(int x, int y) const;

  double& At(int x, int y);

  double LERP(double x, double y) const;

  /* Cubic intERPolate on grid at coordinates (x, y).
   * Coordinates will be clamped to lie in simulation domain
   */
  double CERP(double x, double y) const;

  /* Advect grid in velocity field u, v with given timestep */
  void Advect(const FluidQuantity& u, const FluidQuantity& v);

  std::vector<double> src;
  std::vector<double> dst;

  int w;
  int h;
  double ox;
  double oy;
  double hx;
};

struct FluidSolver final {
  FluidSolver(int w, int h, double density);

  void BuildRhs();

  void Project(int limit);

  void ApplyPressure();

  std::pair<size_t, size_t> Dimensions() const;

  double hx;
  double density;

  FluidQuantity d;
  FluidQuantity u;
  FluidQuantity v;

  int w;
  int h;

  std::vector<double> r;
  std::vector<double> p;
};

}  // namespace detail

struct SimpleFluidSolverSuite final {
  SimpleFluidSolverSuite();

  bool CheckResult();

  void Prepare();

  size_t _grid_size;
  size_t _problem_size;
  detail::FluidSolver _solver;
  detail::FluidSolver _solver_blank;
  detail::FluidSolver _solver_answer;
};

}  // namespace bench::tp
