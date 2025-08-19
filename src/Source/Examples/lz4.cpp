#include "Examples/lz4.h"
#include <cstring>
#include <iostream>
#include <lz4.h>

void Twiz::Lz4Example()
{
    const char* src = "lz4 test data";
    char compressed[64];
    int const compressedSize = LZ4_compress_default(src, compressed, strlen(src), sizeof(compressed));
    std::cout << "[lz4 compressed size: " << compressedSize << "]\n";
}