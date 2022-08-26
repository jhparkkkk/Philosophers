/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:16:57 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:17:32 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int who_dead(t_philo *p)
{
    if (p->s->dead)
        return (1);
    return (0);
}

int is_dead(t_philo *p)
{
    long int time;

    if (who_dead(p))
        return (0);
    time = get_time() - p->s->t.start ;
    if ((time - p->last_soup) > p->s->t.to_die)
    {
        pthread_mutex_lock(&p->s->m.sig_death);
        p->s->dead = p->id;
        pthread_mutex_lock(&p->s->m.print);
        printf("%ld %d died\n", get_time() - p->s->t.start, p->id);
        pthread_mutex_unlock(&p->s->m.print);
        pthread_mutex_unlock(&p->s->m.sig_death);
        return (0);
    }

    return (1);
}

void    *watch_death(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;
    while (1)
    {
        if (!is_dead(p))
            break;
        
    }
    return (NULL);
}