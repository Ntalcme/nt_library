#include "libnt/nt_conversion.h"

/**
 * Return the number of digits of an integer
 * @param n The integer
 * @return The number of digit
 */
static int digits_size(int n)
{
    int          res;
    unsigned int abs_val;

    res = 0;
    if (n < 0)
    {
        res++;
        abs_val = (unsigned int)(-(n + 1)) + 1;
    }
    else
    {
        abs_val = (unsigned int)n;
    }

    while (abs_val)
    {
        abs_val /= 10;
        res++;
    }

    return (res);
}

/**
 * Convert a digit to a char
 * @param n The digit
 * @return The converted digit
 */
char nt_itochar(const int n)
{
    return n + '0';
}

/**
 * Convert an integer to a character string
 * @param value - The integer
 * @return  A char pointer to the converted integer
 */
char *nt_itoa(int value)
{
    char        *res;
    int          i;
    unsigned int abs_val;

    if (value >= 0 && value < 10)
    {
        res = malloc(2);
        if (!res)
            return (NULL);
        res[0] = nt_itochar(value);
        res[1] = '\0';
        return (res);
    }

    i = digits_size(value);
    res = malloc(sizeof(char) * (i + 1));

    if (!res)
    {
        return (NULL);
    }

    res[i--] = '\0';
    if (value < 0)
    {
        res[0] = '-';
        abs_val = (unsigned int)(-(value + 1)) + 1;
    }

    else
    {
        abs_val = (unsigned int)value;
    }

    while (abs_val)
    {
        res[i--] = nt_itochar(abs_val % 10);
        abs_val /= 10;
    }

    return (res);
}
