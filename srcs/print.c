/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:03:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:25:26 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print(t_philo *p, char *msg)
{
    printf("%ld %d %s\n", get_time() - p->s->t.start, p->id, msg);
    if (!ft_strcmp("is eating", msg))
        p->last_soup = get_time()  - p->s->t.start;
}

int    print_msg(t_philo *p, char *msg)
{

    if (who_dead(p))
    {
        //  if (!ft_strcmp("EAT", msg))
        //     drop_chopsticks(p);
        return (STOP);
    }
    pthread_mutex_lock(&p->s->m.print);
    print(p, msg);
    pthread_mutex_unlock(&p->s->m.print);
    return (0);
}