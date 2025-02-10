/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:38:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:56:00 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	verify(char c)
{
	if (c == 'c' || c == 'd' || c == 'x' || c == 'p'
		|| c == 's' || c == 'X' || c == 'u' || c == 'i' || c == '%')
		return (1);
	return (0);
}

static int	ft_format(va_list args, const char format)
{
	if (verify (format) == 0)
		return (-1);
	if (format == 'c')
		return (ft_printf_c((va_arg(args, int))));
	else if (format == 'd' || format == 'i')
		return (ft_printf_d((va_arg(args, int))));
	else if (format == 'p')
		return (ft_printf_p((va_arg(args, void *))));
	else if (format == 's')
		return (ft_printf_s((va_arg(args, char *))));
	else if (format == 'x')
		return (ft_printf_x((va_arg(args, unsigned int))));
	else if (format == 'X')
		return (ft_printf__((va_arg(args, unsigned int))));
	else if (format == 'u')
		return (ft_printf_u((va_arg(args, unsigned int))));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && (verify(str[i + 1])))
		{
			len += ft_format(args, str[i + 1]);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {

//     int num = 42;
//     unsigned int uns_num = -123;
//     char ch = 'A';
//     char *str = "Hello, world!";
//     void *ptr = &num;

//     printf("-- Testing ft_printf implementation --\n");
//     ft_printf("Character: %c\n", ch);
// 	printf("Character: %c\n", ch);
//     ft_printf("Integer (d): %d\n", num);
// 	printf("Integer (d): %d\n", num);
//     ft_printf("Integer (i): %i\n", num);
// 	printf("Integer (i): %i\n", num);
//     ft_printf("Unsigned Integer (u): %u\n", uns_num);
// 	printf("Unsigned Integer (u): %u\n", uns_num);;
//     ft_printf("Hexadecimal (lowercase x): %x\n", uns_num);
// 	printf("Hexadecimal (lowercase x): %x\n", uns_num);
//     ft_printf("Hexadecimal (uppercase X): %X\n", uns_num);
// 	printf("Hexadecimal (uppercase X): %X\n", uns_num);
//     ft_printf("Pointer (p): %p\n", ptr);
// 	printf("Pointer (p): %p\n", ptr);
//     ft_printf("String (s): %s\n", str);
// 	printf("String (s): %s\n", str);
//     ft_printf("Percent sign: %%5\n");
// 	printf("Percent sign: %%\n");

//     return 0;
// }
// int main ()
// {
// 	printf("%d",printf(" %p ", 1255));
// 	ft_printf("%d",ft_printf(" %p ", 1255));
// }