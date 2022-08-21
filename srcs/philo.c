/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/20 17:13:39 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void    eat(t_philo *p)
{
    (*p).mutex->last_soup = get_time();

    if (p->id % 2 == 0)
    {
        if (p->id == p->nb_philo)
            pthread_mutex_lock(&p->mutex->chopsticks[0]);                 // DROITE
        else
            pthread_mutex_lock(&p->mutex->chopsticks[p->id]);             // DROITE
        printf("%d   %d %s\n", 0, p->id, CHOP);
                
        pthread_mutex_lock(&p->mutex->chopsticks[p->id - 1]);             // GAUCHE
        
        printf("%d   %d %s\n", 0, p->id, CHOP);

        printf("%d %d %s\n", p->time_to_eat, p->id, EAT);
        opti_sleep(p->time_to_eat, p);
        
        pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 1]);           // GAUCHE 
            
        if (p->id == p->nb_philo)
            pthread_mutex_unlock(&p->mutex->chopsticks[0]);               // DROITE
        else
            pthread_mutex_unlock(&p->mutex->chopsticks[p->id]);           // DROITE 
            
        return ;
    }
    
    if (p->id % 2 != 0)
    {
        if (p->id == 1)
            pthread_mutex_lock(&p->mutex->chopsticks[p->nb_philo - 1]);   // GAUCHE
        else
            pthread_mutex_lock(&p->mutex->chopsticks[p->id - 2]);         // GAUCHE
        printf("%d   %d %s\n", 0, p->id, CHOP);
        
        if (p->id == p->nb_philo)
            pthread_mutex_lock(&p->mutex->chopsticks[0]);                 // DROITE
        else    
            pthread_mutex_lock(&p->mutex->chopsticks[p->id]);             // DROITE
        printf("%d   %d %s\n", 0, p->id, CHOP);
        
        printf("%d %d %s\n", p->time_to_eat, p->id, EAT);
        opti_sleep(p->time_to_eat, p);
        
        
        if (p->id == p->nb_philo)
            pthread_mutex_unlock(&p->mutex->chopsticks[0]);               // DROITE
        else
            pthread_mutex_unlock(&p->mutex->chopsticks[p->id]);           // DROITE
        if (p->id == 1)
            pthread_mutex_unlock(&p->mutex->chopsticks[p->nb_philo - 1]); // GAUCHE
        else
            pthread_mutex_unlock(&p->mutex->chopsticks[p->id - 2]);       // GAUCHE

    } 
}

int    dead_philo(t_philo *p)
{
    pthread_mutex_lock(&p->mutex->check_death);
    if (get_time() - p->mutex->start_time
        - p->mutex->last_soup >= p->time_to_die)
    {
        printf("DEAD\n");
        pthread_mutex_lock(&p->mutex->signal_death);
        // thread->is_alive = 0;
        p->mutex->dead_philo = 1;
        pthread_mutex_unlock(&p->mutex->signal_death);
        pthread_mutex_lock(&p->mutex->check_death);
        return (1);
    }
    pthread_mutex_lock(&p->mutex->check_death);

    return (0);
}

void *routine(void *arg)
{
    t_philo *p;
    p = (t_philo *)arg;
    // pthread_mutex_t m;
    
    // if (pthread_mutex_init(&m, 0) != 0)
    //     return (NULL);    
    // pthread_mutex_lock(&m);
    while (!p->mutex->dead_philo)
    {
        if (p->id % 2 != 0)
            opti_sleep(p->time_to_eat, p);
        eat(p);
        // (*p).mutex->last_soup = get_time();
        printf("last_soup : %ld\n", (*p).mutex->last_soup);
        // printf("%d %d %s\n", p-, p->id, THINK);
        // opti_sleep(200, p);

        printf("%d %d %s\n", p->time_to_sleep, p->id, SLEEP);
        opti_sleep(p->time_to_sleep, p);
        // pthread_mutex_unlock(&m);

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
    // t_philo *tmp;

    p = NULL;
    // tmp = NULL;
    if (check_input(ac, av))
        return(printf("error\n"), EXIT_FAILURE);
    p = init(av);
    set_mutex(p);
    printf("START TIME : %ld\n", (*p)->mutex->start_time);
    printf("START nb odd  : %d\n", (*p)->mutex->tmp_odd);
    printf("NOW : %ld\n", get_time() - (*p)->mutex->start_time);
    run_thread(p);
    
    // printf("END nb even : %d\n", (*p)->mutex->tmp_even);
    // printf("END nb odd  : %d\n", (*p)->mutex->tmp_odd);


    

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
// TO DO : check someone is dead 
// TO DO : measure time after soup
