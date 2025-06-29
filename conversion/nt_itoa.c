# include "nt_conversion.h"

/**
 * Return the number of digits of an integer 
 * @param n The integer
 * @return The number of digit
 */
static int digits_size(int n)
{
    int res;

    res = 0;
    if (n < 0)
    {
        res++;
        n *= -1;
    }

    while (n)
    {
        n /= 10;
        res++;
    }

    return (res);
}

/**
 * Convert an integer to a character string
 * @param value - The integer
 * @return  A char pointer to the converted integer
 */
char* nt_itoa(long long value)
{
    char *res;
    int i;

    if (value == 0)
    {
        return nt_strdup("0");
    }

    if (value == MIN_INT)
    {
        return nt_strdup(MIN_INT_STR);
    }

    i = digits_size(value);
    res = malloc(sizeof(char) * (i+1));

    if (!res) 
    {
        return (NULL);
    }

    res[i--] = '\0';
    if (value < 0)
    {
        res[0] = '-';
        value *= -1;
    }

    while (value)
    {
        res[i--] = nt_itochar(value % 10);
        value /= 10;
    }

    return (res);
}
