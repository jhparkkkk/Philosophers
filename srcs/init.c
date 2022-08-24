/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/24 23:34:58 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*last_elem(t_philo *philo)
{
   if (philo)
	{
        while (philo->next)
		    philo = philo->next;
	    return (philo);
    }
    return (NULL);
}

static void data_add_back(t_philo **philo, t_philo *new_p)
{   
  	if (!new_p)
		return ;
	if (!*philo)
		*philo = new_p;
	else
		last_elem(*philo)->next = new_p;
}

t_philo *set_data(char **av)
{
    t_philo *new_p;
    new_p = NULL;
    new_p = malloc(sizeof(t_philo));
    if (!new_p)
		return (NULL);
    new_p->nb_philo = ft_atoi(*av++);
    new_p->time_to_die = ft_atoi(*av++);
    new_p->time_to_eat = ft_atoi(*av++);
    new_p->time_to_sleep = ft_atoi(*av++);
    new_p->eat_n_times = ft_atoi(*av);
    new_p->nb_soup = 0;
    new_p->last_soup = 0;
    new_p->alive = 1;
    new_p->next = NULL;
    new_p->mutex = malloc(sizeof(t_mutex ) * 1);
    if (!new_p->mutex)
		return (NULL);
    return (new_p);
}

void close_ll(t_philo **p)
{
    t_philo *first;

    first = *p;
    last_elem(*p)->next = first;
}

t_philo **init(char **av)
{
    t_philo **p;
    t_philo *new_p;
    int     nb_philo;

    p = malloc(sizeof(t_philo **));
    if (!p)
        return(NULL);
    nb_philo = ft_atoi(av[1]);
    new_p = NULL;
    while (nb_philo--)
    {
        new_p = set_data(av + 1);
        if (!new_p)
            return (destroy_philo(p), NULL);
        data_add_back(p, new_p);
    }
    close_ll(p);
    return (p);
}