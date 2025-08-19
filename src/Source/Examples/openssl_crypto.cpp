#include "Examples/openssl_crypto.h"
#include <iostream>
#include <openssl/crypto.h>
namespace Twiz
{
    void OpensslCryptoDemo()
    {
        std::cout << "OpenSSL crypto version: " << OpenSSL_version(OPENSSL_VERSION) << '\n';
    }
} // namespace Twiz
