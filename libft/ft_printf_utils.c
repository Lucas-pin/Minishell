/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:01:29 by lpin              #+#    #+#             */
/*   Updated: 2024/09/17 19:22:29 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar(char c, int *count)
{
	if (write(1, &c, 1) == -1)
		*count = -1;
	else
		*count = *count + 1;
}

void	ft_printstr(char *str, int *count)
{
	if (str == NULL)
	{
		ft_printstr("(null)", count);
		return ;
	}
	while (*str)
	{
		ft_printchar(*str, count);
		str++;
	}
}

void	ft_castnbr(long long n, int base, int flag, int *count)
{
	if (n < 0)
	{
		ft_printchar('-', count);
		ft_castnbr(-n, base, flag, count);
	}
	else if (n > base - 1)
	{
		ft_castnbr(n / base, base, flag, count);
		ft_castnbr(n % base, base, flag, count);
	}
	if (n >= 0 && n <= 9)
		ft_printchar(n + '0', count);
	else if (n > 9 && n < 16 && base == 16)
	{
		if (flag == 0)
			ft_printchar(n + 87, count);
		else if (flag == 1)
			ft_printchar(n + 55, count);
	}
}

void	ft_unsigned_castnbr(unsigned long long n, int base, int flag,
			int *count)
{
	if (n > (unsigned long long)base - 1)
	{
		ft_unsigned_castnbr(n / base, base, flag, count);
		ft_unsigned_castnbr(n % base, base, flag, count);
	}
	if (n > 0 && n <= 9)
		ft_printchar(n + '0', count);
	else if (n > 9 && n < 16 && base == 16)
	{
		if (flag == 0)
			ft_printchar(n + 87, count);
		else if (flag == 1)
			ft_printchar(n + 55, count);
	}
}

/*int	ft_left_ceros(unsigned long n)
{
	int	count;

	count = 0;
	while ((n & 0xF0000000UL) == 0)
	{
		n <<= 4;
		count++;
		if (count == 7)
			return (count);
	}
	return (count);
}

char	*ft_pointer_descomposer(unsigned long long pointer, char *str)
{
	unsigned long	low;
	unsigned long	high;
	int				left_ceros;

	low = pointer & 0xFFFFFFFFUL;
	high = (pointer >> 32) & 0xFFFFFFFFUL;
	if (high == 0 && low == 0)
		return (str = ft_strjoin_free(str, "0"));
	if (high != 0)
	{
		str = ft_castnbr(high, 16, str);
		left_ceros = ft_left_ceros(low);
		while (left_ceros > 0)
		{
			str = ft_strjoin_free(str, "0");
			left_ceros--;
		}
	}
	return (str = ft_castnbr(low, 16, str));
}

	-El valor ASCII de 'a' es 97, por ende si n = 10 
	se debería representar la 'a'. Por eso sumo 87.
	- Para imprimir valores Hexadecimales se evalua 
	que el numero sea menor a la base, ya que sino
	se imprime la letra 'a' cuando el numero es en base 10.
*/
