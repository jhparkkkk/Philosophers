/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 18:51:21 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

void *routine(void *arg)
{
    t_philo *ph;
    ph = (t_philo *)arg;
    
    //write(1, "test\n", 5);
    //while (ph->mutexes... != 1)
    //{
        
    //}
    pthread_mutex_lock(&ph->mutex);
    printf("My index is: %d\n", ph->idx);
    //write(1, "test2\n", 5);
    pthread_mutex_unlock(&ph->mutex);
    
    return (NULL);
}

int set_mutex(t_philo **ph)
{
    int i;

    i = 0;
    while (i < (*ph)->p->nb_philo)
    {
        if (pthread_mutex_init(&ph[i]->mutex, 0) != 0)
        {
            destroy_philo(ph);
            return (1);
        }
        i++;
    }

    return (0);
}

int run_thread(t_philo **ph, t_param *p)
{
    int i;

    i = 0;
    while(i < p->nb_philo)
    {
        ph[i]->idx = i;
        pthread_create(&ph[i]->th, NULL, &routine, ph[i]);
        i++;
        printf("?\n");
    }    
    i = 0;
    while(i < p->nb_philo)
    {
        printf("wait\n");
        pthread_join(ph[i]->th, 0);
        i++;
        // printf("wait\n");
    }
    // sleep(1);
    return (0);
}

int main(int ac, char **av)
{
    t_param p;
    t_philo **ph;


    ph = NULL;
    if (ac == 6 && check_input(av))
        return(printf("error\n"), EXIT_FAILURE);
    set_param(&p, av + 1);
    ph = set_philo(&p);
    init(ph, &p, av);
    set_mutex(ph);
    run_thread(ph, &p);    

    printf("NB PHILO      : %d\n", p.nb_philo);
    printf("TIME TO DIE   : %d\n", p.time_to_die);
    printf("TIME TO EAT   : %d\n", p.time_to_eat);
    printf("TIME TO SLEEP : %d\n", p.time_to_sleep);
    printf("EAT N TIMES   : %d\n", p.eat_n_times);
    
    // destroy_philo(ph);
    return (0);
}

// TODO : tableau de mutex
// TODO : liste chainee en boucle (je vais au dernier node etje pointe sur le premier)