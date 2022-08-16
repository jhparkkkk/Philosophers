/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 16:57:08 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_param(t_param *p, char **av)
{
    p->nb_philo = ft_atoi(*av++);
    p->time_to_die = ft_atoi(*av++);
    p->time_to_eat = ft_atoi(*av++);
    p->time_to_sleep = ft_atoi(*av++);
    p->eat_n_times = ft_atoi(*av);
}


t_philo **set_philo(t_param *p)
{
    t_philo **ph;
    int i;
    
    ph = malloc(sizeof(t_philo *) * p->nb_philo);
    if (!ph)
        return (NULL);
    i = 0;
    while(i < p->nb_philo)
    {
        ph[i] = malloc(sizeof(t_philo));
        if (!ph[i])
            return (NULL);
        ph[i]->p = malloc(sizeof(t_param));
        if (!ph[i]->p)
            return (NULL);
        ph[i]->p = p;
        i++;
    }
    return(ph);
}

int    init(t_philo **ph, t_param *p, char **av)
{
    set_param(p, av + 1);
    ph = set_philo(p);    
    if (!ph || set_mutex(ph))
        return (EXIT_FAILURE);
    return (0);
}