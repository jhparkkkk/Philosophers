/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:09:01 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 22:17:20 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void    destroy_mutex(t_mutex m, int total)
{
    while (total--)
    {
        pthread_mutex_destroy(&m.chop[total]);
    }
    pthread_mutex_destroy(&m.sig_death);
    pthread_mutex_destroy(&m.update_soup);



    // pthread_mutex_destroy(&(*p)->mutex->print);
    
}

void    destroy_philo(t_philo **p, int idx)
{
    (void)idx;
    int i;
    int total;
    
    if (!p)
        return ;
    i = 0;
    total = (*p)->s->nb_philo;

    free((*p)->s->m.chop);
    while (i < total && p[i])
    {
        // free((*p)->s->m.chop);
        // free((*p)->s);
        if (p[i])
            free(p[i]);
        i++;
    }
    free(p);


}