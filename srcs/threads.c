/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:17:54 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:18:27 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_philo **p, int i)
{
    while (i < (*p)->s->nb_philo)
    {
        pthread_create(&p[i]->th, NULL, (void *)&routine, p[i]);
        i++;
    }
    return (0);
}

int join_threads(t_philo **p, int i)
{
    while (i < (*p)->s->nb_philo)
    {
        pthread_join(p[i]->th, NULL);
        i++;
    }
    return(0);
}

int run_thread(t_philo **p)
{
    int i;

    i = 0;
    (*p)->s->t.start = get_time();
    create_threads(p, i);
    join_threads(p, i);
    return (0);    
}