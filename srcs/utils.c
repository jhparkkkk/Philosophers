/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:35 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 16:26:26 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char	*str)
{
	int	nb;
	int	neg;

	nb = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		neg *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str) == 1)
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	return (neg * nb);
}

int check_input(char **av)
{
    av++;
    while(av && *av)
        if (ft_atoi(*av++) <= 0)
            return (1);
    return (0);
}