/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:38:17 by lpin              #+#    #+#             */
/*   Updated: 2023/10/06 19:41:51 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd != -1)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

/*#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	c[] = "Aguante Argentina pa";

	fd = open("prueba_txt.txt", O_RDWR);
	if (fd != -1)
	{
		ft_putstr_fd(c, fd);
		printf("El fd es: %i", fd);
		close(fd);
	}
	else
		printf("Fallo la apertura");
	return (0);
}*/
//En open utilizo el flag 'O_RDWR' para tener acceso de lectura y escritura