/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/24 23:47:18 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void    grab_chopstick(t_philo *p)
{
    
    if (p->id % 2 == 0)
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        print_msg(p, 0);

        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        print_msg(p, 0);

    }
    else
    {
        pthread_mutex_lock(&p->mutex->chopsticks[p->id % p->nb_philo]);
        print_msg(p, 0);
        if (p->nb_philo == 1)
        {
            pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
            return ;
        }
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        print_msg(p, 0);

    }

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
    long int time;

    time = get_time() - p->last_soup;
    printf("TIME : %ld\n", time);
    printf("TIME TO DIE : %d\n", p->time_to_sleep);
    if (time + p->time_to_sleep >= p->time_to_die)
    {
        p->alive = 0;
        print_msg(p, 4);
        pthread_mutex_lock(&p->mutex->signal_death);
        p->mutex->dead_philo = 1;
        pthread_mutex_unlock(&p->mutex->signal_death);
        return (1);
    }
    return (0);
}


void *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *)arg;
    // int dead = 0;
    // pthread_mutex_lock(&p->mutex->check_death);
    while (get_time() !=  p->mutex->start_time + 80)
    {
        if (p->id % 2 != 0)
            opti_sleep(p->time_to_eat / 10, p);
        grab_chopstick(p);
        if (p->nb_philo == 1)
            return (NULL);
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
    (*p)->mutex->start_time = get_time();

    while(i < (*p)->nb_philo)
    {
        node->id = i + 1;
        pthread_create(&node->th, NULL, &routine, node);
        node = node->next;
        i++;
    }
    // while (1)
    // {
    //     // pthread_mutex_lock(&(*p)->mutex->exit);
    //     if ((*p)->mutex->dead_philo == 1)
    //     {
    //         // print_msg(*p, 4);
    //         // pthread_mutex_unlock(&(*p)->mutex->exit);
    //         // printf("DEAD\n");
    //         // return (0);
    //         exit (0);
    //     }
    //     pthread_mutex_unlock(&(*p)->mutex->exit);
        
    // }  
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


    // int i = 0;
    // while (i < (*p)->nb_philo)
    // {
    //     pthread_mutex_destroy(&(*p)->mutex->chopsticks[i]);
    //     i++;
    // }
    // pthread_mutex_destroy(&(*p)->mutex->print);
    
    return (0);
}
