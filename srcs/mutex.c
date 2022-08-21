/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:42:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/21 16:58:42 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_status(t_philo *p, int status)
{
    // pthread_mutex_t msg;
    
    
    pthread_mutex_lock(&p->mutex->print);
    // pthread_mutex_lock(&msg);
    if (!status)
        printf("%d   %d %s\n", 0, p->id, CHOP);
    // pthread_mutex_unlock(&msg);
    else if (status == 1)
        printf("%ld %d %s\n", get_time() - p->mutex->start_time, p->id, SLEEP);
    else if (status == 2)
        printf("%ld %d %s\n", get_time() - p->mutex->start_time, p->id, THINK);
        
    pthread_mutex_unlock(&p->mutex->print);

    
    

    
}

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
    if (pthread_mutex_init(&(*p)->mutex->check_death, 0) != 0)
            return (EXIT_FAILURE);
    if (pthread_mutex_init(&(*p)->mutex->signal_death, 0) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&(*p)->mutex->print, 0) != 0)
        return (EXIT_FAILURE);
    (*p)->mutex->start_time = get_time();
    (*p)->mutex->last_soup = 0;
    (*p)->mutex->dead_philo = 0;
    (*p)->mutex->finished_soup = 0;

    // set_odd_even(p, (*p)->nb_philo);
    tmp = *p;
    i = 0;
    while(i < (*p)->nb_philo)
    {
        tmp->mutex->chopsticks = mutex;
        tmp->mutex->start_time = (*p)->mutex->start_time;
        tmp->mutex->last_soup =(*p)->mutex->last_soup;
        tmp->mutex->check_death = (*p)->mutex->check_death;
        tmp->mutex->signal_death = (*p)->mutex->signal_death;
        tmp->mutex->dead_philo = (*p)->mutex->dead_philo = 0;
        tmp->mutex->finished_soup = (*p)->mutex->finished_soup;
        
        tmp = tmp->next;
        i++;
    }
    // free(mutex);
    return (0);
}