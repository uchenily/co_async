/* #define CO_ASYNC_PERF 1 */
#include <co_async/utils/debug.hpp>
#include <co_async/co_async.hpp>/*{import co_async;}*/
#include <co_async/std.hpp>/*{import std;}*/

using namespace co_async;
using namespace std::literals;

Task<> amain() {
    SSLClientTrustAnchor ta;
    ta.add(co_await file_read(make_path("scripts/certificates/cert-root-rsa.pem")));
    HTTPProtocol http(co_await SSLClientSocketStream::connect("localhost", 4433, ta, {}, {}, std::chrono::seconds(5)));
    HTTPRequest req = {
        .method = "GET",
        .uri = URI::parse("/"),
    };
    co_await http.write_header(req);
    co_await http.write_nobody(req);
    HTTPResponse res;
    co_await http.read_header(res);
    debug(), co_await http.read_body(res.encoding);
}

int main() {
    co_synchronize(amain());
    return 0;
}