find_package(OpenSSL COMPONENTS Crypto SSL REQUIRED)

add_system_dependency(OpenSSL::Crypto)
add_system_dependency(OpenSSL::SSL)