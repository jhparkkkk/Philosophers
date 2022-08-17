/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:42:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/17 17:47:12 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int set_mutex(t_philo **p)
{
    pthread_mutex_t *mutex;
    t_philo         *tmp;
    int i;
    
    i = 0;
    mutex = NULL;
    tmp = NULL;
    mutex = malloc(sizeof(pthread_mutex_t) * (*p)->nb_philo);
    if (!mutex)
        return (EXIT_FAILURE);
    while (i < (*p)->nb_philo)
    {
        if (pthread_mutex_init(&mutex[i], 0) != 0)
            return (free(mutex), EXIT_FAILURE);
        i++;
    }
    set_odd_even(p, (*p)->nb_philo);
    tmp = *p;
    i = 0;
    while(i < (*p)->nb_philo)
    {
        tmp->mutex->chopsticks = mutex;
        tmp->mutex->odd = (*p)->mutex->odd;
        tmp->mutex->even = (*p)->mutex->even;
        tmp->mutex->tmp_odd = (*p)->mutex->tmp_odd;
        tmp->mutex->tmp_even = (*p)->mutex->tmp_even;
        tmp = tmp->next;
        i++;
    }
    // free(mutex);
    return (0);
}