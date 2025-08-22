#include "lz4_example.h"
#include <iostream>
#include <lz4.h>
#include <cstring>

void twiz::lz4_example()
{
    const char* src = "lz4 test data";
    char compressed[64];
    int compressedSize = LZ4_compress_default(src, compressed, strlen(src), sizeof(compressed));
    std::cout << "[lz4 compressed size: " << compressedSize << "]\n";
}