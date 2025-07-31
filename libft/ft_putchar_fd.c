/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:00:03 by lpin              #+#    #+#             */
/*   Updated: 2023/10/06 19:24:11 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
		write(fd, &c, 1);
}

/*#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	c;

	c = 'c';
	fd = open("prueba_txt.txt", O_RDWR);
	if (fd != -1)
	{
		ft_putchar_fd(c, fd);
		printf("El fd es: %i", fd);
		close(fd);
	}
	else
		printf("Fallo la apertura");
	return (0);
}*/
//En open utilizo el flag 'O_RDWR' para tener acceso de lectura y escritura