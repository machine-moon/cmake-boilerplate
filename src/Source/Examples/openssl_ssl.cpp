#include "Examples/openssl_ssl.h"
#include <iostream>
#include <openssl/ssl.h>
namespace Twiz
{
    void OpensslSslDemo()
    {
        std::cout << "OpenSSL SSL version: " << OpenSSL_version(OPENSSL_VERSION) << '\n';
    }
} // namespace Twiz
