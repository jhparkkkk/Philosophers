/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:11:35 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo **init_philo(t_set *s)
{
    t_philo **p;
    int     i;

    i = 0;
    p = malloc(sizeof(t_philo *) * s->nb_philo);
    if (!p)
        return (NULL);
    while (i < s->nb_philo)
    {
        p[i] = malloc(sizeof(t_philo));
        p[i]->id = i + 1;
        p[i]->s = s;
        i++;
    }
    return (p);
}

void    init_s(t_set *s, char **av)
{
    s->nb_philo = ft_atoi(*av++);
    s->dead = 0;
    s->t.start = 0;
    s->t.to_die = ft_atoi(*av++);
    s->t.to_eat = ft_atoi(*av++);
    s->t.to_sleep = ft_atoi(*av++);
    s->t.eat_n_times = ft_atoi(*av);
}