/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:32:09 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 16:32:12 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	d;
	long	nbr;

	nbr = (long)n;
	if (nbr == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	d = nbr % 10 + '0';
	write(fd, &d, 1);
}
