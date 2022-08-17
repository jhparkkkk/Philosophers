/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/17 18:28:38 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void    eat(t_philo *p)
{
    if (p->id % 2 == 0)
    {
        if (p->id == p->nb_philo)
            pthread_mutex_lock(&p->mutex->chopsticks[0]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id]);
        printf("%d %d %s\n", p->time_to_eat, p->id, EAT);
        opti_sleep(p->time_to_eat);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id]);
        p->mutex->tmp_even--;
    }
    else if (p->id % 2 != 0)
    {
        if (p->id == 1)
            pthread_mutex_lock(&p->mutex->chopsticks[p->nb_philo]);
        else if (p->id == p->nb_philo)
            pthread_mutex_lock(&p->mutex->chopsticks[0]);
        else
            pthread_mutex_lock(&p->mutex->chopsticks[p->id + 1]);
        pthread_mutex_lock(&p->mutex->chopsticks[p->id]);
        printf("%d %d %s\n", p->time_to_eat, p->id, EAT);
        opti_sleep(p->time_to_eat);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id + 1]);
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id]);
        p->mutex->tmp_odd--;

    }  
}

void *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *)arg;
    
    if ((p->id % 2 == 0 && p->mutex->tmp_even > 0) || (p->id % 2 != 0 && p->mutex->tmp_odd > 0))
    {
        eat(p);
    }
    else
    {
        printf("%d %d %s\n", p->time_to_eat, p->id, THINK);
        opti_sleep(p->time_to_sleep);
    }
    
   
    // while (p->mutex->someone_is_dead != 1)
    // {
    //     if (p->id % 2 != 0)
    //     {
    //         pthread_mutex_lock(&p->mutex->chopsticks[p->id]);
    //         pthread_mutex_lock(&p->mutex->chopsticks[p->]);
            
            
    //     }
        
    // }
    
    // pthread_mutex_lock(&p->mutex->chopsticks[p->id]);
    // printf("%d %s\n", p->id, EAT);
    // printf("My index is: %d\n", p->id);
    // opti_sleep(500);
    // pthread_mutex_unlock(&p->mutex->chopsticks[p->id]);
    
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
    t_philo *tmp;

    p = NULL;
    tmp = NULL;
    if (check_input(ac, av))
        return(printf("error\n"), EXIT_FAILURE);
    p = init(av);
    set_mutex(p);


    run_thread(p);
    // if (!p)
    //     return (printf("sad philo\n"), 0);
    // tmp = *p;
    // int i = 0;
    // while(i < 2)
    // {
    //     if (tmp->nb_philo)
    //         printf("%d\n", tmp->nb_philo);
    //     tmp = tmp->next;
    //     i++;
    // }
    // destroy_philo(p);
    return (0);
}

// TODO : tableau de mutex
// TODO : liste chainee en boucle (je vais au dernier node etje pointe sur le premier)