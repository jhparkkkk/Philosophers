/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:30 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/17 17:40:50 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_odd_even(t_philo **p, int nb_philo)
{
    int i;

    i = 0;
    
    (*p)->mutex->odd = 0;
    (*p)->mutex->even = 0;
    while (++i <= nb_philo)
    {
        if (i % 2 == 0)
            (*p)->mutex->even++;
        else
            (*p)->mutex->odd++;
    }
    (*p)->mutex->tmp_even = (*p)->mutex->even;
    (*p)->mutex->tmp_odd = (*p)->mutex->odd;
}

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
    new_p->next = NULL;
    new_p->mutex = malloc(sizeof(t_mutex) * new_p->nb_philo);
    if (!new_p->mutex)
		return (NULL);
    new_p->mutex->someone_is_dead = 0;
    // set_odd_even(&new_p, new_p->nb_philo);
    
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