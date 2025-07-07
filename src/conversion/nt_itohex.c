#include "libnt/nt_conversion.h"

static int hex_digits_needed(unsigned long long value)
{
    int res = 0;

    if (value == 0)
        return 1;

    while (value)
    {
        value >>= 4;
        res++;
    }
    return res;
}

char *nt_itohex(unsigned long long value, const char *base)
{
    char *res;
    int   digits_needed;
    int   i;

    digits_needed = hex_digits_needed(value);

    res = malloc(sizeof(char) * (digits_needed + 1));
    if (!res)
        return (NULL);

    for (i = digits_needed - 1; i >= 0; --i)
    {
        res[i] = base[value & 0xF];
        value >>= 4;
    }

    res[digits_needed] = '\0';
    return (res);
}
