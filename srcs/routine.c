/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:15:49 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 21:48:43 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo		*p;
	pthread_t	death;

	p = (t_philo *)arg;
    
    // pthread_mutex_lock(&p->s->m.watch);
    pthread_create(&death, NULL, watch_death, p);
    pthread_detach(death);
    // pthread_mutex_unlock(&p->s->m.watch);

	
    // if (p->id % 2 == 0)
    // opti_sleep(p->s->t.to_eat);
    
    while (1)
	{
        // eat
        grab_chopsticks(p);
        if (print_msg(p, EAT) == STOP) // drop chop
        {
            drop_chopsticks(p);
            return (NULL);
        }
        opti_sleep(p->s->t.to_eat);
        drop_chopsticks(p);

        // sleep
        if (print_msg(p, SLEEP) == STOP)
            return (NULL);
        opti_sleep(p->s->t.to_sleep);
        //think
        if (print_msg(p, THINK) == STOP)
            return (NULL);

    }

	return (NULL);
}