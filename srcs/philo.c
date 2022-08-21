/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/21 17:49:43 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void    eat(t_philo *p)
{
    (*p).mutex->last_soup = get_time();
    if (p->id % 2 == 0)
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        opti_sleep(p->time_to_eat, p);
        pthread_mutex_lock(&p->mutex->print);
        printf("%ld %d %s\n", get_time() - p->mutex->start_time, p->id, EAT);
        pthread_mutex_unlock(&p->mutex->print);
        
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
    }
    else
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        
        opti_sleep(p->time_to_eat, p);
        pthread_mutex_lock(&p->mutex->print);
        printf("%ld %d %s\n", get_time() - p->mutex->start_time, p->id, EAT);
        pthread_mutex_unlock(&p->mutex->print);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);
    }
}

int    dead_philo(t_philo *p)
{
    pthread_mutex_lock(&p->mutex->check_death);
    if ( get_time() - p->mutex->last_soup + p->time_to_sleep > p->time_to_die)
    {
        pthread_mutex_lock(&p->mutex->signal_death);
        p->mutex->dead_philo = 1;
        pthread_mutex_unlock(&p->mutex->signal_death);
        pthread_mutex_unlock(&p->mutex->check_death);
        return (1);
    }
    pthread_mutex_unlock(&p->mutex->check_death);

    return (0);
}

void    change_status(t_philo *p)
{
    if (dead_philo(p))
    {
        
        pthread_mutex_lock(&p->mutex->print);
        opti_sleep(p->time_to_die - p->time_to_sleep, p);
        printf("%ld %d %s\n", get_time() - p->mutex->start_time, p->id, "died\n");
        pthread_mutex_unlock(&p->mutex->print);
        exit (0);
    }
    opti_sleep(p->time_to_sleep, p);
    print_status(p, 1);
    print_status(p, 2);

}
void *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *)arg;

    while (1)
    {
        if (p->mutex->dead_philo)
            break ;
        // if (p->id % 2 != 0)
        //     opti_sleep(p->time_to_eat, p);
        eat(p);
        change_status(p);

    }
    // printf("SAD PHILO\n");
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
    
    // printf("END nb even : %d\n", (*p)->mutex->tmp_even);
    // printf("END nb odd  : %d\n", (*p)->mutex->tmp_odd);


    int i = 0;
    while (i < (*p)->nb_philo)
    {
        pthread_mutex_destroy(&(*p)->mutex->chopsticks[i]);
        i++;
    }
    pthread_mutex_destroy(&(*p)->mutex->print);
    
    /*** DEBUGGER ***/
    // if (!p)
    //     return (printf("sad philo\n"), 0);
    // tmp = *p;
    // int i = 0;
    // while(i < tmp->nb_philo)
    // {
    //     if (tmp->mutex->tmp_odd)
    //         printf("odd  : %d\n", tmp->mutex->tmp_odd);
    //     if (tmp->mutex->tmp_even)
    //         printf("even : %d\n", tmp->mutex->tmp_even);
    //     tmp = tmp->next;
    //     i++;
    // }
    // destroy_philo(p);
    
    return (0);
}
