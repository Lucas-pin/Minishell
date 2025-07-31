/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:47:56 by lpin              #+#    #+#             */
/*   Updated: 2024/03/26 19:59:45 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

int		ft_printf(char const *str, ...);
/*
@brief: print a string with format
@param: str: string to print
@return: count of printed characters
*/

void	ft_printchar(char c, int *count);
/*
@brief: print a character
@param: c: character to print
@param: count: pointer to the count of printed characters
*/

void	ft_printstr(char *str, int *count);
/*
@brief: print a string
@param: str: string to print
@param: count: pointer to the count of printed characters
*/

void	ft_castnbr(long long n, int base, int flag, int *count);
/*
@brief: cast a number to a string
@param: n: number to cast
@param: len_base: length of the base
@param: str: base to cast the number
@param: count: pointer to the count of printed characters
*/

void	ft_unsigned_castnbr(unsigned long long n, int base,
			int flag, int *count);
/*
@brief: cast an unsigned number to a string
@param: n: number to cast
@param: len_base: length of the base
@param: str: base to cast the number
@param: count: pointer to the count of printed characters
*/

/*
char	*ft_pointer_descomposer(unsigned long long p, char *str);
@brief: print a pointer
@param: n: pointer to print
@param: count: pointer to the count of printed characters


int		ft_left_ceros(unsigned long n);

@brief: This function counts the number of groups of four zeros 
at the leftmost part in the binary representation of an unsigned long number.
@param: n: number to count the left ceros
@return: count of left ceros
*/

#endif