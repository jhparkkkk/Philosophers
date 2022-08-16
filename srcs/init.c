/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 14:30:30 by jeepark          ###   ########.fr       */
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

void    destroy_philo(t_philo **ph)
{
    while (ph && *ph)
        free(ph++);
    free(ph);
}

int set_philo(t_philo **ph, t_param *p)
{
    int i;
    
    ph = malloc(sizeof(t_philo *) * p->nb_philo);
    if (!ph)
        return (1);
    i = 0;
    while(i < p->nb_philo)
    {
        ph[i] = malloc(sizeof(t_philo));
        if (!ph)
            return (destroy_philo(ph),0);
        ph[i]->p = malloc(sizeof(t_param));
        ph[i]->p = p;
        i++;
    }
    return(0);
}