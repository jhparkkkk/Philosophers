/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:16:57 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 22:04:18 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int time_left(t_philo *p)
{
    long int time;

    pthread_mutex_lock(&p->s->m.update_soup);
    time = get_time() - p->s->t.start - p->last_soup;
    pthread_mutex_unlock(&p->s->m.update_soup);
    
    return (time);
}

int is_dead(t_philo *p)
{
    long int    time;

    time= 0;
    pthread_mutex_lock(&p->s->m.sig_death);
    if (p->s->dead == 1)
    {
        pthread_mutex_unlock(&p->s->m.sig_death);
        
        return (0);
    }
    pthread_mutex_unlock(&p->s->m.sig_death);

    time = time_left(p);
    if (time > p->s->t.to_die)
    {
        pthread_mutex_lock(&p->s->m.sig_death);
        p->s->dead = 1;
        printf("%ld %d died\n", get_time() - p->s->t.start, p->id);
        // if (p->s->nb_philo == 1)
        //     drop_chopsticks(p);
        pthread_mutex_unlock(&p->s->m.sig_death);
        // if (p->s->nb_philo == 1)
        //     drop_chopsticks(p);
        return (0);
    }
    
    pthread_mutex_lock(&p->s->m.update_soup);

    if (p->s->full == p->s->nb_philo)
    {
        pthread_mutex_lock(&p->s->m.sig_death);
        p->s->dead = 1;
        pthread_mutex_unlock(&p->s->m.sig_death);
        pthread_mutex_unlock(&p->s->m.update_soup);

        return (0);
    }
    pthread_mutex_unlock(&p->s->m.update_soup);


    return (1);
}

// int is_full(t_philo *p)
// {
//     int         dead;       

//     dead = p->s->dead;
//     if (dead == 1)
//         return (0);

//     // if (p->s->full == -1)
//     //     return (1);
//     if (p->s->full == p->s->nb_philo)
//     {
//         pthread_mutex_lock(&p->s->m.watch);
        
//         p->s->dead = 1;
//         pthread_mutex_unlock(&p->s->m.watch);

//         return (0);
//     }
//     return (1);
// }

void    *watch_death(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;
    while (1)
    {
        if (!is_dead(p))
            break;
        usleep(80);
    }
    return (NULL);
}