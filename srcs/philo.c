/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 14:28:59 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(t_philo *ph)
{
    (void)ph;
    pthread_mutex_lock(&ph->mutex);
    printf("hello\n");
    pthread_mutex_unlock(&ph->mutex);
    return (NULL);
}

int main(int ac, char **av)
{
    t_param p;
    t_philo **ph;
    
    ph = NULL;
    if (ac == 6 && check_input(av))
        return(printf("error\n"), 0);
    else
    
    set_param(&p, av + 1);
    set_philo(ph, &p);    
    // ph = malloc(sizeof(t_philo *) * p.nb_philo);

    // if (!ph)
    //     return (0);
    
 
    // pthread_mutex_init(&ph.mutex, 0);
    // pthread_create(&ph.th, NULL, (void *)&routine, &ph);
    // pthread_join(ph.th, 0);
    // pthread_mutex_destroy()

    printf("NB PHILO      : %d\n", p.nb_philo);
    printf("TIME TO DIE   : %d\n", p.time_to_die);
    printf("TIME TO EAT   : %d\n", p.time_to_eat);
    printf("TIME TO SLEEP : %d\n", p.time_to_sleep);
    printf("EAT N TIMES   : %d\n", p.eat_n_times);

    return (0);
}