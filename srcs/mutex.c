/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:42:18 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:07:25 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init_mutex(t_set *s, int total)
{
    int i;

    s->m.chop = malloc(sizeof(pthread_mutex_t) * total);
    if (!s->m.chop)
        return (EXIT_FAILURE);
    i = 0;
    while (i < total)
    {
        if (pthread_mutex_init(&s->m.chop[i], 0) != 0)
            return (free(s->m.chop), EXIT_FAILURE);
        i++;
    }
    if (pthread_mutex_init(&s->m.print, 0) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&s->m.sig_death, 0) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}