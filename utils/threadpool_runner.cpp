#include "threadpool_runner.hpp"

namespace bench::tp {

Runner::Runner(std::function<std::future<void>(std::function<void()>&&)>&& callback) : _run{std::move(callback)} {
}

}  // namespace bench::tp
