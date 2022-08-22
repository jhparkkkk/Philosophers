/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/22 18:05:57 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void    grab_chopstick(t_philo *p)
{
    if (p->id % 2 == 0)
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
    }
    else
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
    }
    print_msg(p, 0);

}

void    drop_chopstick(t_philo *p)
{
    if (p->id % 2 == 0)
    {
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
    }
    else
    {
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);
    }
}

int    dead_philo(t_philo *p)
{
    pthread_mutex_lock(&p->mutex->check_death);
    if (get_time() - p->last_soup + p->time_to_sleep >= p->time_to_die)
    {
        printf("DEAD\n");
        pthread_mutex_lock(&p->mutex->signal_death);
        p->mutex->dead_philo = 1;
        pthread_mutex_unlock(&p->mutex->signal_death);
        pthread_mutex_unlock(&p->mutex->check_death);
        return (1);
    }
    pthread_mutex_unlock(&p->mutex->check_death);

    return (0);
}


void *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *)arg;
    
    while (get_time() != p->mutex->start_time + 100 && !p->mutex->dead_philo)
    {
        grab_chopstick(p);
        print_msg(p, 1);
        
        opti_sleep(p->time_to_eat, p);
        drop_chopstick(p);
        
        print_msg(p, 2);
        opti_sleep(p->time_to_sleep, p);
        print_msg(p, 3);    
    }
    return (NULL);
}

int run_thread(t_philo **p)
{
    t_philo *node;
    int     i;

    i = 0;
    node = *p;
    while(i < (*p)->nb_philo)
    {
        node->id = i + 1;
        
        pthread_create(&node->th, NULL, &routine, node);
        node = node->next;
        i++;
    }    
    i = 0;
    node = NULL;
    node = *p;
    while( i < (*p)->nb_philo)
    {
        pthread_join(node->th, 0);
        node = node->next;
        i++;
    }
    return (0);
}

int main(int ac, char **av)
{
    t_philo **p;

    p = NULL;
    if (check_input(ac, av))
        return(printf("error\n"), EXIT_FAILURE);
    p = init(av);
    set_mutex(p);
    run_thread(p);


    int i = 0;
    while (i < (*p)->nb_philo)
    {
        pthread_mutex_destroy(&(*p)->mutex->chopsticks[i]);
        i++;
    }
    pthread_mutex_destroy(&(*p)->mutex->print);
    
    return (0);
}
