#include "ft_virus.h"


// maybe do those in assembly

size_t ft_strlen(char *str)
{
	size_t index;

	index = 0;
	while (str[index])
		index += 1;
	return (index);
}

int ft_memcmp(char *str1, char *str2, size_t len)
{
	size_t index;

	index = 0;
	while (index < len && str1[index] == str2[index])
		index += 1;
	return (index == len ? 0 : str1[index] - str2[index]);
}

void *ft_memcpy(char *dest, char *src, size_t len)
{
	while (len)
	{
		dest[len - 1] = src[len - 1];
		len -= 1;
	}
	return (dest);
}

void ft_putnbr(int n)
{
	char c;

	if (n == -2147483648)
		WRITE(1, "-2147483648", 11);
	else
	{
		if (n < 0 && n > -2147483648)
		{
			WRITE(1, "-", 1);
			n = -n;
		}
		if (n < 10 && n > -2147483648)
		{
			c = '0' + n;
			WRITE(1, &c, 1);
		}
		else if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
	}
}
