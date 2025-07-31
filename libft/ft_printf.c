/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:01:25 by lpin              #+#    #+#             */
/*   Updated: 2024/03/26 19:59:47 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	select_format(va_list arg, int type, int *count)
{
	if (type == 'c')
		ft_printchar(va_arg(arg, int), count);
	else if (type == 's')
		ft_printstr(va_arg(arg, char *), count);
	else if (type == 'i' || type == 'd')
		ft_castnbr(va_arg(arg, int), 10, 0, count);
	else if (type == 'u')
		ft_castnbr(va_arg(arg, unsigned int), 10, 0, count);
	else if (type == 'x')
		ft_castnbr(va_arg(arg, unsigned int), 16, 0, count);
	else if (type == 'X')
		ft_castnbr(va_arg(arg, unsigned int), 16, 1, count);
	else if (type == 'p')
	{
		ft_printstr("0x", count);
		ft_unsigned_castnbr(va_arg(arg, unsigned long long), 16, 0, count);
	}
}

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (write(1, "", 0) == -1)
		return (-1);
	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i] && count != -1)
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '%')
				ft_printchar(str[i], &count);
			else
				select_format(ap, str[i], &count);
		}
		else
			ft_printchar(str[i], &count);
		i++;
	}
	va_end(ap);
	return (count);
}

/*int	main(void)
{
	int		i;
	int		j;

	j = ft_printf("%d", -10);
	printf("\n");
	i = printf("%d", -10);
	printf("\n");
	ft_printf("ft_printf Son %d caracteres", j);
	printf("\n");
	printf("printf Son %d caracteres\n", i);
	return (0);
}*/
