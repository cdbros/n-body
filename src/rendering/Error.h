#pragma once

#include <string>

#ifndef NDEBUG
#define glCheck(call) detail::check_err([&]() { return call; }, __LINE__, __FILE__, __func__, #call)
#else
#define glCheck(call) call
#endif

namespace detail {

void check_err(int line, std::string file, std::string func, std::string call);

template <typename ret_t> struct func_caller {
    template <typename func_t> static ret_t call(func_t f) { return f(); }
};

template <> struct func_caller<void> {
    template <typename func_t> static int call(func_t f) {
        f();
        return 0;
    }
};

template <typename func_t>
auto check_err(func_t func_call, int line, std::string file, std::string func, std::string call) {
    auto ret = func_caller<decltype(func_call())>::call(func_call);
    check_err(line, std::move(file), std::move(func), std::move(call));
    return ret;
}

} // namespace detail
