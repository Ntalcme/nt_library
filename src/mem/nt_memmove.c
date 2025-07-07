#include "libnt/nt_mem.h"

/**
 * Copy an amount of bytes from a source to a destination
 * @param dst The destination
 * @param src The source
 * @return The destination's pointer
 */
void *nt_memmove(void *dst, const void *src, size_t num_bytes)
{
    unsigned char *d;
    unsigned char *s;

    if (!dst || !src)
        return (dst);
    if (dst == src)
        return (dst);

    d = (unsigned char *)dst;
    s = (unsigned char *)src;

    if (d > s)
    {
        while (num_bytes--)
        {
            d[num_bytes] = s[num_bytes];
        }
        return (dst);
    }

    while (num_bytes--)
    {
        *d++ = *s++;
    }
    return (dst);
}
