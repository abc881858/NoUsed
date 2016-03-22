#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdint.h>

class utils
{
public:
    utils();
    const unsigned char *FindPattern(const void *address, size_t size, const unsigned char *signature, const char *mask);
};

#endif // UTILS_H
