/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 21:25:47 by jeepark          ###   ########.fr       */
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
        if (!p[i])
            return(destroy_philo(p, i), NULL);
        p[i]->id = i + 1;
        p[i]->s = s;
        i++;
    }
    return (p);
}

void    init_s(t_set *s, char **av, int ac)
{
    s->nb_philo = ft_atoi(*av++);
    s->dead = 0;
    s->t.start = 0;
    s->t.to_die = ft_atoi(*av++);
    s->t.to_eat = ft_atoi(*av++);
    s->t.to_sleep = ft_atoi(*av++);
    if (ac == 6)
    {
        s->t.eat_n_times = ft_atoi(*av);
        s->full = 0;
    }
    else
        s->full =-1;
}