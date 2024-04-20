/*{module;}*/

#include <bearssl.h>

#pragma once /*{export module co_async:ssl.ssl_socket;}*/

#include <co_async/std.hpp>/*{import std;}*/

#ifdef __linux__
#include <co_async/system/error_handling.hpp>/*{import :system.error_handling;}*/
#include <co_async/system/fs.hpp>            /*{import :system.fs;}*/
#include <co_async/system/socket.hpp>        /*{import :system.socket;}*/
#include <co_async/system/socket_proxy.hpp>  /*{import :system.socket_proxy;}*/
#include <co_async/system/system_loop.hpp>   /*{import :system.system_loop;}*/
#include <co_async/awaiter/task.hpp>         /*{import :awaiter.task;}*/
#include <co_async/utils/string_utils.hpp>   /*{import :utils.string_utils;}*/
#include <co_async/iostream/socket_stream.hpp>/*{import :iostream.socket_stream;}*/
#include <co_async/iostream/stream_base.hpp>/*{import :iostream.stream_base;}*/

namespace co_async {

inline std::string bearSSLErrorName(int err) {
    static std::pair<int, char const *> errors[] = {
        {
            BR_ERR_BAD_PARAM,
            "BR_ERR_BAD_PARAM",
        },
        {
            BR_ERR_BAD_STATE,
            "BR_ERR_BAD_STATE",
        },
        {
            BR_ERR_UNSUPPORTED_VERSION,
            "BR_ERR_UNSUPPORTED_VERSION",
        },
        {
            BR_ERR_BAD_VERSION,
            "BR_ERR_BAD_VERSION",
        },
        {
            BR_ERR_BAD_LENGTH,
            "BR_ERR_BAD_LENGTH",
        },
        {
            BR_ERR_TOO_LARGE,
            "BR_ERR_TOO_LARGE",
        },
        {
            BR_ERR_BAD_MAC,
            "BR_ERR_BAD_MAC",
        },
        {
            BR_ERR_NO_RANDOM,
            "BR_ERR_NO_RANDOM",
        },
        {
            BR_ERR_UNKNOWN_TYPE,
            "BR_ERR_UNKNOWN_TYPE",
        },
        {
            BR_ERR_UNEXPECTED,
            "BR_ERR_UNEXPECTED",
        },
        {
            BR_ERR_BAD_CCS,
            "BR_ERR_BAD_CCS",
        },
        {
            BR_ERR_BAD_ALERT,
            "BR_ERR_BAD_ALERT",
        },
        {
            BR_ERR_BAD_HANDSHAKE,
            "BR_ERR_BAD_HANDSHAKE",
        },
        {
            BR_ERR_OVERSIZED_ID,
            "BR_ERR_OVERSIZED_ID",
        },
        {
            BR_ERR_BAD_CIPHER_SUITE,
            "BR_ERR_BAD_CIPHER_SUITE",
        },
        {
            BR_ERR_BAD_COMPRESSION,
            "BR_ERR_BAD_COMPRESSION",
        },
        {
            BR_ERR_BAD_FRAGLEN,
            "BR_ERR_BAD_FRAGLEN",
        },
        {
            BR_ERR_BAD_SECRENEG,
            "BR_ERR_BAD_SECRENEG",
        },
        {
            BR_ERR_EXTRA_EXTENSION,
            "BR_ERR_EXTRA_EXTENSION",
        },
        {
            BR_ERR_BAD_SNI,
            "BR_ERR_BAD_SNI",
        },
        {
            BR_ERR_BAD_HELLO_DONE,
            "BR_ERR_BAD_HELLO_DONE",
        },
        {
            BR_ERR_LIMIT_EXCEEDED,
            "BR_ERR_LIMIT_EXCEEDED",
        },
        {
            BR_ERR_BAD_FINISHED,
            "BR_ERR_BAD_FINISHED",
        },
        {
            BR_ERR_RESUME_MISMATCH,
            "BR_ERR_RESUME_MISMATCH",
        },
        {
            BR_ERR_INVALID_ALGORITHM,
            "BR_ERR_INVALID_ALGORITHM",
        },
        {
            BR_ERR_BAD_SIGNATURE,
            "BR_ERR_BAD_SIGNATURE",
        },
        {
            BR_ERR_WRONG_KEY_USAGE,
            "BR_ERR_WRONG_KEY_USAGE",
        },
        {
            BR_ERR_NO_CLIENT_AUTH,
            "BR_ERR_NO_CLIENT_AUTH",
        },
        {
            BR_ERR_IO,
            "BR_ERR_IO",
        },
        {
            BR_ERR_X509_INVALID_VALUE,
            "BR_ERR_X509_INVALID_VALUE",
        },
        {
            BR_ERR_X509_TRUNCATED,
            "BR_ERR_X509_TRUNCATED",
        },
        {
            BR_ERR_X509_EMPTY_CHAIN,
            "BR_ERR_X509_EMPTY_CHAIN",
        },
        {
            BR_ERR_X509_INNER_TRUNC,
            "BR_ERR_X509_INNER_TRUNC",
        },
        {
            BR_ERR_X509_BAD_TAG_CLASS,
            "BR_ERR_X509_BAD_TAG_CLASS",
        },
        {
            BR_ERR_X509_BAD_TAG_VALUE,
            "BR_ERR_X509_BAD_TAG_VALUE",
        },
        {
            BR_ERR_X509_INDEFINITE_LENGTH,
            "BR_ERR_X509_INDEFINITE_LENGTH",
        },
        {
            BR_ERR_X509_EXTRA_ELEMENT,
            "BR_ERR_X509_EXTRA_ELEMENT",
        },
        {
            BR_ERR_X509_UNEXPECTED,
            "BR_ERR_X509_UNEXPECTED",
        },
        {
            BR_ERR_X509_NOT_CONSTRUCTED,
            "BR_ERR_X509_NOT_CONSTRUCTED",
        },
        {
            BR_ERR_X509_NOT_PRIMITIVE,
            "BR_ERR_X509_NOT_PRIMITIVE",
        },
        {
            BR_ERR_X509_PARTIAL_BYTE,
            "BR_ERR_X509_PARTIAL_BYTE",
        },
        {
            BR_ERR_X509_BAD_BOOLEAN,
            "BR_ERR_X509_BAD_BOOLEAN",
        },
        {
            BR_ERR_X509_OVERFLOW,
            "BR_ERR_X509_OVERFLOW",
        },
        {
            BR_ERR_X509_BAD_DN,
            "BR_ERR_X509_BAD_DN",
        },
        {
            BR_ERR_X509_BAD_TIME,
            "BR_ERR_X509_BAD_TIME",
        },
        {
            BR_ERR_X509_UNSUPPORTED,
            "BR_ERR_X509_UNSUPPORTED",
        },
        {
            BR_ERR_X509_LIMIT_EXCEEDED,
            "BR_ERR_X509_LIMIT_EXCEEDED",
        },
        {
            BR_ERR_X509_WRONG_KEY_TYPE,
            "BR_ERR_X509_WRONG_KEY_TYPE",
        },
        {
            BR_ERR_X509_BAD_SIGNATURE,
            "BR_ERR_X509_BAD_SIGNATURE",
        },
        {
            BR_ERR_X509_TIME_UNKNOWN,
            "BR_ERR_X509_TIME_UNKNOWN",
        },
        {
            BR_ERR_X509_EXPIRED,
            "BR_ERR_X509_EXPIRED",
        },
        {
            BR_ERR_X509_DN_MISMATCH,
            "BR_ERR_X509_DN_MISMATCH",
        },
        {
            BR_ERR_X509_BAD_SERVER_NAME,
            "BR_ERR_X509_BAD_SERVER_NAME",
        },
        {
            BR_ERR_X509_CRITICAL_EXTENSION,
            "BR_ERR_X509_CRITICAL_EXTENSION",
        },
        {
            BR_ERR_X509_NOT_CA,
            "BR_ERR_X509_NOT_CA",
        },
        {
            BR_ERR_X509_FORBIDDEN_KEY_USAGE,
            "BR_ERR_X509_FORBIDDEN_KEY_USAGE",
        },
        {
            BR_ERR_X509_WEAK_PUBLIC_KEY,
            "BR_ERR_X509_WEAK_PUBLIC_KEY",
        },
        {
            BR_ERR_X509_NOT_TRUSTED,
            "BR_ERR_X509_NOT_TRUSTED",
        },
        {0, 0},
    };
    std::size_t u;
    for (u = 0; errors[u].second; u++) {
        if (errors[u].first == err) {
            return errors[u].second;
        }
    }
    return to_string(err);
}

struct SSLPemDecoder {
private:
    std::unique_ptr<br_pem_decoder_context> pemDec =
        std::make_unique<br_pem_decoder_context>();
    std::string result;
    std::string objName;
    std::vector<std::pair<std::string, std::string>> objs;

    static void pemResultAppender(void *self, void const *buf, size_t len) {
        reinterpret_cast<SSLPemDecoder *>(self)->onResult(
            {reinterpret_cast<char const *>(buf), len});
    }

    void onResult(std::string_view s) {
        result.append(s);
    }

public:
    SSLPemDecoder() {
        br_pem_decoder_init(pemDec.get());
        br_pem_decoder_setdest(pemDec.get(), pemResultAppender, this);
    }

    SSLPemDecoder &decode(std::string_view s) {
        while (auto n = br_pem_decoder_push(pemDec.get(), s.data(), s.size())) {
            switch (br_pem_decoder_event(pemDec.get())) {
            case BR_PEM_BEGIN_OBJ:
                objName = br_pem_decoder_name(pemDec.get());
                break;
            case BR_PEM_END_OBJ:
                objs.emplace_back(std::move(objName), std::move(result));
                result.clear();
                break;
            case BR_PEM_ERROR:
#if CO_ASYNC_DEBUG
                std::cerr << "PEM decoder error\n";
#endif
                throw std::runtime_error("PEM decoder error");
            }
            s.remove_prefix(n);
        }
        return *this;
    }

    std::vector<std::pair<std::string, std::string>> const &objects() const {
        return objs;
    }

    static std::vector<std::string> tryDecode(std::string_view s) {
        std::vector<std::string> res;
        if (s.find("-----BEGIN ") != s.npos) {
            SSLPemDecoder dec;
            dec.decode(s);
            for (auto &[k, v]: dec.objs) {
                res.push_back(std::move(v));
            }
        } else {
            res.emplace_back(s);
        }
        return res;
    }
};

struct SSLX509Decoder {
private:
    std::unique_ptr<br_x509_decoder_context> x509Dec =
        std::make_unique<br_x509_decoder_context>();
    std::string result;

    static void x509ResultAppender(void *self, void const *buf, size_t len) {
        reinterpret_cast<SSLX509Decoder *>(self)->onResult(
            {reinterpret_cast<char const *>(buf), len});
    }

    void onResult(std::string_view s) {
        result.append(s);
    }

public:
    SSLX509Decoder() {
        br_x509_decoder_init(x509Dec.get(), x509ResultAppender, this);
    }

    SSLX509Decoder &decode(std::string_view s) {
        br_x509_decoder_push(x509Dec.get(), s.data(), s.size());
        return *this;
    }

    std::string_view getDN() const {
        int err = br_x509_decoder_last_error(x509Dec.get());
        if (err != BR_ERR_OK) {
#if CO_ASYNC_DEBUG
            std::cerr << "X509 decoder error: " + bearSSLErrorName(err) + "\n";
#endif
            throw std::runtime_error("X509 decoder error: " +
                                     bearSSLErrorName(err));
        }
        return result;
    }

    br_x509_pkey *getPubKey() const {
        return br_x509_decoder_get_pkey(x509Dec.get());
    }
};

/*[export]*/ struct SSLPrivateKey {
private:
    std::unique_ptr<br_skey_decoder_context> skeyDec =
        std::make_unique<br_skey_decoder_context>();

public:
    SSLPrivateKey() {
        br_skey_decoder_init(skeyDec.get());
    }

    SSLPrivateKey &decodeBinary(std::string_view s) {
        br_skey_decoder_push(skeyDec.get(), s.data(), s.size());
        return *this;
    }

    SSLPrivateKey &set(std::string_view pkey) {
        for (auto &s: SSLPemDecoder::tryDecode(pkey)) {
            decodeBinary(s);
        }
        return *this;
    }

    br_ec_private_key const *getEC() const {
        return br_skey_decoder_get_ec(skeyDec.get());
    }

    br_rsa_private_key const *getRSA() const {
        return br_skey_decoder_get_rsa(skeyDec.get());
    }
};

struct SSLClientTrustAnchor {
public:
    std::vector<br_x509_trust_anchor> trustAnchors;

    SSLClientTrustAnchor &addBinary(std::string_view certX506) {
        auto &x506 = x506Stores.emplace_back();
        x506.decode(certX506);
        auto dn = x506.getDN();
        auto &k = x506.getPubKey()->key.rsa;
        trustAnchors.push_back({
            {(unsigned char *)dn.data(), dn.size()},
            BR_X509_TA_CA,
            *x506.getPubKey(),
        });
        return *this;
    }

    SSLClientTrustAnchor &add(std::string_view certX506) {
        for (auto &s: SSLPemDecoder::tryDecode(certX506)) {
            addBinary(s);
        }
        return *this;
    }

private:
    std::vector<SSLX509Decoder> x506Stores;
};

struct SSLServerCertificate {
public:
    std::vector<br_x509_certificate> certificates;

    SSLServerCertificate &addBinary(std::string certX506) {
        auto &cert = strStores.emplace_back(std::move(certX506));
        certificates.push_back({(unsigned char *)cert.data(), cert.size()});
        return *this;
    }

    SSLServerCertificate &add(std::string_view certX506) {
        for (auto &s: SSLPemDecoder::tryDecode(certX506)) {
            addBinary(s);
        }
        return *this;
    }

private:
    std::vector<std::string> strStores;
};

struct SSLSessionCache {
    std::unique_ptr<unsigned char[]> mLruBuf;
    br_ssl_session_cache_lru mLru;

    explicit SSLSessionCache(std::size_t size) {
        mLruBuf = std::make_unique<unsigned char[]>(size);
        br_ssl_session_cache_lru_init(&mLru, mLruBuf.get(), size);
    }
};

struct SSLSocketBufBase : SocketBuf {
private:
    br_ssl_engine_context *eng = nullptr;
    std::unique_ptr<char[]> iobuf =
        std::make_unique<char[]>(BR_SSL_BUFSIZE_BIDI);

public:
    explicit SSLSocketBufBase(SocketHandle file) : SocketBuf(std::move(file)) {}

protected:
    void setEngine(br_ssl_engine_context *eng_) {
        eng = eng_;
        br_ssl_engine_set_buffer(eng, iobuf.get(), BR_SSL_BUFSIZE_BIDI, 1);
    }

    Task<> bearSSLRunUntil(unsigned target) {
        for (;;) {
            unsigned state = br_ssl_engine_current_state(eng);
            if (state & BR_SSL_CLOSED) {
                int err = br_ssl_engine_last_error(eng);
                if (err != BR_ERR_OK) [[unlikely]] {
#if CO_ASYNC_DEBUG
                    std::cerr << "SSL error: " + bearSSLErrorName(err) + "\n";
#endif
                    throw std::runtime_error("SSL error: " +
                                             bearSSLErrorName(err));
                }
                co_return;
            }

            if (state & BR_SSL_SENDREC) {
                unsigned char *buf;
                size_t len, wlen;

                buf = br_ssl_engine_sendrec_buf(eng, &len);
#if CO_ASYNC_EXCEPT
                try {
#endif
                    wlen =
                        co_await SocketBuf::raw_write({(char const *)buf, len});
#if CO_ASYNC_EXCEPT
                } catch (...) {
                    if (!eng->shutdown_recv) {
                        if (eng->iomode != 0) {
                            eng->iomode = 0;
                            eng->err = BR_ERR_IO;
                        }
                    }
                    throw;
                }
#endif
                if (wlen > 0) [[likely]] {
                    br_ssl_engine_sendrec_ack(eng, wlen);
                } else {
                    co_return;
                }
                continue;
            }

            if (state & target) {
                co_return;
            }

            if (state & BR_SSL_RECVAPP) [[unlikely]] {
#if CO_ASYNC_DEBUG
                std::cerr << "SSL write not ready\n";
#endif
                throw std::runtime_error("SSL write not ready");
            }

            if (state & BR_SSL_RECVREC) {
                unsigned char *buf;
                size_t len, rlen;

                buf = br_ssl_engine_recvrec_buf(eng, &len);
#if CO_ASYNC_EXCEPT
                try {
#endif
                    rlen = co_await SocketBuf::raw_read({(char *)buf, len});
#if CO_ASYNC_EXCEPT
                } catch (...) {
                    if (!eng->shutdown_recv) {
                        if (eng->iomode != 0) {
                            eng->iomode = 0;
                            eng->err = BR_ERR_IO;
                        }
                    }
                    throw;
                }
#endif
                if (rlen > 0) [[likely]] {
                    br_ssl_engine_recvrec_ack(eng, rlen);
                } else {
                    co_return;
                }
                continue;
            }

            br_ssl_engine_flush(eng, 0);
        }
    }

public:
    Task<> ssl_flush() {
        br_ssl_engine_flush(eng, 0);
        co_await bearSSLRunUntil(BR_SSL_SENDAPP | BR_SSL_RECVAPP);
    }

    Task<std::size_t> raw_read(std::span<char> buffer) {
        unsigned char *buf;
        size_t alen;

        if (buffer.empty()) [[unlikely]] {
            co_return 0;
        }
        co_await bearSSLRunUntil(BR_SSL_RECVAPP);
        buf = br_ssl_engine_recvapp_buf(eng, &alen);
        if (alen > buffer.size()) {
            alen = buffer.size();
        }
        memcpy(buffer.data(), buf, alen);
        br_ssl_engine_recvapp_ack(eng, alen);
        co_return alen;
    }

    Task<std::size_t> raw_write(std::span<char const> buffer) {
        unsigned char *buf;
        size_t alen;

        if (buffer.empty()) [[unlikely]] {
            co_return 0;
        }
        co_await bearSSLRunUntil(BR_SSL_SENDAPP);
        buf = br_ssl_engine_sendapp_buf(eng, &alen);
        if (alen > buffer.size()) {
            alen = buffer.size();
        }
        memcpy(buf, buffer.data(), alen);
        br_ssl_engine_sendapp_ack(eng, alen);
        co_return alen;
    }

    void ssl_close() {
        br_ssl_engine_close(eng);
#if CO_ASYNC_DEBUG
        if (br_ssl_engine_current_state(eng) != BR_SSL_CLOSED) [[unlikely]] {
            std::cerr << "SSL closed improperly\n";
        }
#endif
        int err = br_ssl_engine_last_error(eng);
        if (err != BR_ERR_OK) [[unlikely]] {
#if CO_ASYNC_DEBUG
            std::cerr << "SSL closed with error: " + bearSSLErrorName(err) +
                             "\n";
#endif
            throw std::runtime_error("SSL closed with error: " +
                                     bearSSLErrorName(err));
        }
    }

    /*     SSLSocketBufBase(SSLSocketBufBase &&that) noexcept */
    /*     : SocketBuf(std::move(that)), eng(std::exchange(that.eng, nullptr)), iobuf(std::move(that.iobuf)) {} */
    /*  */
    /*     SSLSocketBufBase &operator=(SSLSocketBufBase &&that) noexcept { */
    /*         SocketBuf::operator=(std::move(that)); */
    /*         std::swap(eng, that.eng); */
    /*         std::swap(iobuf, that.iobuf); */
    /*         return *this; */
    /*     } */
    /*  */
    /*     ~SSLSocketBufBase() { */
    /*         if (eng) { */
    /*             br_ssl_engine_close(eng); */
    /* #if CO_ASYNC_DEBUG */
    /*             if (br_ssl_engine_current_state(eng) != BR_SSL_CLOSED) [[unlikely]] { */
    /*                 std::cerr << "SSL closed improperly\n"; */
    /*             } */
    /*             int err = br_ssl_engine_last_error(eng); */
    /*             if (err != BR_ERR_OK) [[unlikely]] { */
    /*                 std::cerr << "SSL closed with error: " + bearSSLErrorName(err) + "\n"; */
    /*             } */
    /* #endif */
    /*         } */
    /*     } */
};

struct SSLServerSocketBuf : SSLSocketBufBase {
private:
    std::unique_ptr<br_ssl_server_context> ctx =
        std::make_unique<br_ssl_server_context>();

public:
    explicit SSLServerSocketBuf(SocketHandle file,
                                SSLServerCertificate const &cert,
                                SSLPrivateKey const &pkey,
                                SSLSessionCache *cache = nullptr)
        : SSLSocketBufBase(std::move(file)) {
        if (auto rsa = pkey.getRSA()) {
            br_ssl_server_init_full_rsa(ctx.get(), std::data(cert.certificates),
                                        std::size(cert.certificates), rsa);
        } else if (auto ec = pkey.getEC()) {
            br_ssl_server_init_full_ec(ctx.get(), std::data(cert.certificates),
                                       std::size(cert.certificates),
                                       BR_KEYTYPE_EC, ec);
        } else [[unlikely]] {
            throw std::runtime_error("invalid private key type");
        }
        setEngine(&ctx->eng);
        if (cache) {
            br_ssl_server_set_cache(ctx.get(), &cache->mLru.vtable);
        }
        br_ssl_server_reset(ctx.get());
    }
};

struct SSLClientSocketBuf : SSLSocketBufBase {
private:
    std::unique_ptr<br_ssl_client_context> ctx =
        std::make_unique<br_ssl_client_context>();
    std::unique_ptr<br_x509_minimal_context> x509Ctx =
        std::make_unique<br_x509_minimal_context>();

public:
    explicit SSLClientSocketBuf(SocketHandle file,
                                SSLClientTrustAnchor const &ta,
                                char const *host,
                                std::span<char const *const> protocols)
        : SSLSocketBufBase(std::move(file)) {
        br_ssl_client_init_full(ctx.get(), x509Ctx.get(),
                                std::data(ta.trustAnchors),
                                std::size(ta.trustAnchors));
        setEngine(&ctx->eng);
        br_ssl_engine_set_protocol_names(
            &ctx->eng, const_cast<char const **>(protocols.data()),
            protocols.size());
        br_ssl_client_reset(ctx.get(), host, 0);
    }

    void ssl_reset(char const *host, bool resume) {
        br_ssl_client_reset(ctx.get(), host, resume);
    }

    std::string ssl_get_selected_protocol() {
        if (auto p = br_ssl_engine_get_selected_protocol(&ctx->eng)) {
            return p;
        }
        return {};
    }
};

/*[export]*/ struct SSLClientSocketStream : IOStream<SSLClientSocketBuf> {
    using IOStream<SSLClientSocketBuf>::IOStream;

    static Task<SSLClientSocketStream>
    connect(char const *host, int port, SSLClientTrustAnchor const &ta,
            std::span<char const *const> protocols, std::string_view proxy,
            std::chrono::nanoseconds timeout) {
        auto conn = co_await socket_proxy_connect(host, port, proxy, timeout);
        SSLClientSocketStream sock(std::move(conn), ta, host, protocols);
        co_return sock;
    }

    Task<> flush() {
        co_await IOStream<SSLClientSocketBuf>::flush();
        co_await ssl_flush();
    }
};

/*[export]*/ struct SSLServerSocketStream : IOStream<SSLServerSocketBuf> {
    using IOStream<SSLServerSocketBuf>::IOStream;

    static Task<SSLServerSocketStream>
    accept(SocketListener &listener, SSLServerCertificate const &cert,
           SSLPrivateKey const &skey, SSLSessionCache *cache = nullptr) {
        auto conn = co_await listener_accept(listener);
        SSLServerSocketStream sock(std::move(conn), cert, skey, cache);
        co_return sock;
    }

    Task<> flush() {
        co_await IOStream<SSLServerSocketBuf>::flush();
        co_await ssl_flush();
    }
};

} // namespace co_async
#endif