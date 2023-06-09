#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_print_hexa(unsigned int hexa)
{
	char	hexa_dec[16] = "0123456789abcdef";
	int		size;

	size = 0;
	if (hexa > 15)
		size = ft_print_hexa(hexa / 16);
	write(1, &hexa_dec[hexa % 16], 1);
	size++;
	return (size);
}

int	ft_print_int(int d)
{
	int		size;
	char	*str;
	char	c;
	
	size = 0;
	if (d == -2147483648)
	{
		str = "-2147483648";
		while (size < 11)
		{
			write(1, &str[size], 1);
			size++;
		}
	}
	else if (d < 0)
	{
		c = '-';
		write(1, &c, 1);
		size++;
		size += ft_print_int(d * -1);
	}
	else if (d > 9)
	{
		size += ft_print_int(d / 10);
		c = (d % 10) + '0';
		write(1, &c, 1);
		size++;
	}
	else
	{
		c = (d % 10) + '0';
		write(1, &c, 1);
		size++;
	}
	return (size);
}

int	ft_print_str(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		write(1, &str[size], 1);
		size++;
	}
	return (size);
}

int ft_printf(const char *format, ...)
{
	int	i;
	int	size;
	va_list	args;
	char	c;

	i = 0;
	size = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				c = '%';
				write(1, &c, 1);
				size++;
			}
			else if (format[i + 1] == 's')
				size += ft_print_str(va_arg(args, char *));
			else if (format[i + 1] == 'd')
				size += ft_print_int(va_arg(args, int));
			else if (format[i + 1] == 'x')
				size += ft_print_hexa(va_arg(args, unsigned int));
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			size++;
		}
		i++;
	}
	va_end(args);
	return (size);
}

int main(void)
{
	int	i;
	i = ft_printf("Hexadecimal for %d is %x\n", -2147447, 42);
	printf("SIZE MY PRINTF = %d\n", i);
	i = printf("Hexadecimal for %d is %x\n", -2147447, 42);
	printf("SIZE ORIGINAL PRINTF = %d\n", i);
	return (0);
}
