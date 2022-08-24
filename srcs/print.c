/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:03:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/24 23:45:18 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_msg(t_philo *p, int type)
{
    pthread_mutex_lock(&p->mutex->check_death);
    // if (p->nb_philo == 1)
    // {
    //     pthread_mutex_unlock(&p->mutex->chopsticks[p->id % p->nb_philo]);
    //     return;
    // }
    pthread_mutex_unlock(&p->mutex->check_death);
    
    pthread_mutex_lock(&p->mutex->print);
    if (!type)
        printf("%ld %d %s\n", get_time() - p->mutex->start_time , p->id, CHOP);
    else if (type == 1)
    {
        printf("%ld %d %s\n", get_time() - p->mutex->start_time , p->id, EAT);
        p->last_soup = get_time();
    }
    else if (type == 2)
        printf("%ld %d %s\n", get_time() - p->mutex->start_time , p->id, SLEEP);
    else if (type == 3)
        printf("%ld %d %s\n", get_time() - p->mutex->start_time , p->id, THINK);
    else if (type == 4)
    {
        printf("%ld %d %s\n", get_time() - p->mutex->start_time , p->id, "died");
    }
    pthread_mutex_unlock(&p->mutex->print);
}