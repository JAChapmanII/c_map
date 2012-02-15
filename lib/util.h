#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>

// Write a size_t to a file in a endian independant way
size_t util_writeSizeT(FILE *outFile, size_t toWrite);
// Read a size_t from a file in a endian independant way
size_t util_readSizeT(FILE *inFile);

#endif // UTIL_H
