#include <co_async/co_async.hpp>/*{import co_async;}*/
#include <cmake/clang_std_modules_source/std.hpp>/*{import std;}*/

using namespace co_async;
using namespace std::literals;

Task<> amain() {
    auto path = make_path("/home/bate/Downloads/Screenshot_2024-04-04_19-24-13.png");
    auto file = co_await fs_open(path, OpenMode::Read);
    auto size = co_await fs_stat_size(path);
    std::vector<char> buffer(size);
    co_await fs_read(file, buffer);
}

int main() {
    co_spawn_and_wait(amain());
    return 0;
}
