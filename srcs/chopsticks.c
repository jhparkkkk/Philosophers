/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:22:56 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:23:25 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    grab_chopsticks(t_philo *p)
{
    if (p->id % 2 != 0)
    {
        pthread_mutex_lock(&p->s->m.chop[p->id - 1]);
        print_msg(p, CHOP);

        pthread_mutex_lock(&p->s->m.chop[p->id % p->s->nb_philo]);
        print_msg(p, CHOP);

    }
    else
    {
        pthread_mutex_lock(&p->s->m.chop[p->id % p->s->nb_philo]);
        print_msg(p, CHOP);
        pthread_mutex_lock(&p->s->m.chop[p->id - 1]);
        print_msg(p, CHOP);

    }

}

void    drop_chopsticks(t_philo *p)
{
    if (p->id % 2 != 0)
    {
        pthread_mutex_unlock(&p->s->m.chop[p->id - 1]);
        pthread_mutex_unlock(&p->s->m.chop[p->id % p->s->nb_philo]);
    }
    else
    {
        pthread_mutex_unlock(&p->s->m.chop[p->id % p->s->nb_philo]);
        pthread_mutex_unlock(&p->s->m.chop[p->id - 1]);
    }
}