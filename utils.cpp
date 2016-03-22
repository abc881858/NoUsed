#include "utils.h"

__forceinline bool FindPatternCompare(const unsigned char* address, const unsigned char* signature, const char* mask)
{
    while (*mask)
    {
        if (*reinterpret_cast<const uint32_t*>(mask) == 'xxxx')
        {
            if (*reinterpret_cast<const uint32_t*>(address) != *reinterpret_cast<const uint32_t*>(signature))
            {
                return false;
            }

            address += 4;
            signature += 4;
            mask += 4;
            continue;
        }
        else if (*reinterpret_cast<const uint16_t*>(mask) == 'xx')
        {
            if (*reinterpret_cast<const uint16_t*>(address) != *reinterpret_cast<const uint16_t*>(signature))
            {
                return false;
            }

            address += 2;
            signature += 2;
            mask += 2;
            continue;
        }
        else if (*mask == 'x' && *address != *signature)
        {
            return false;
        }

        ++address;
        ++signature;
        ++mask;
    }

    return *mask == 0;
}

const unsigned char* FindPatternInternal(const unsigned char* address, size_t size, const unsigned char* signature, const char* mask)
{
    for (size_t i = 0; i < size; i++)
    {
        if (IsBadReadPtr(address + i, 4))
        {
            return nullptr;
        }
        if (FindPatternCompare(address + i, signature, mask))
        {
            return address + i;
        }
    }
    return nullptr;
}

utils::utils()
{

}

const unsigned char* utils::FindPattern(const void* address, size_t size, const unsigned char* signature, const char* mask)
{
    size_t mask_length = strlen(mask);
    return FindPatternInternal(reinterpret_cast<const unsigned char*>(address), size - mask_length, signature, mask);
}
