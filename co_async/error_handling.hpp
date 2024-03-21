#pragma once

#include <cerrno>
#include <system_error>
#if !defined(NDEBUG)
#include <source_location>
#endif

namespace co_async {

#if !defined(NDEBUG)
auto checkError(auto res, std::source_location const &loc = std::source_location::current()) {
    if (res == -1) [[unlikely]] {
        throw std::system_error(errno, std::system_category(),
                                (std::string)loc.file_name() + ":" + std::to_string(loc.line()));
    }
    return res;
}
#else
auto checkError(auto res) {
    if (res == -1) [[unlikely]] {
        throw std::system_error(errno, std::system_category());
    }
    return res;
}
#endif

}
