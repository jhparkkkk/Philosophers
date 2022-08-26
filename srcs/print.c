/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:03:06 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 20:45:11 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int update_soup(t_philo *p, char *msg)
{
    if (!ft_strcmp("is eating", msg))
    {
        pthread_mutex_lock(&p->s->m.update_soup);
        
        p->last_soup = get_time()  - p->s->t.start;
        // pthread_mutex_unlock(&p->s->m.update_soup);

        if (p->nb_soup < p->s->t.eat_n_times)
            p->nb_soup++;
        if (p->nb_soup == p->s->t.eat_n_times && p->s->full < p->s->nb_philo)
            p->s->full++;
        pthread_mutex_unlock(&p->s->m.update_soup);
          
        // printf("id no. %d | nb_soup : %d / %d\n", p->id, p->nb_soup, p->s->t.eat_n_times);
        
    }
    return (0);
}

void    print(t_philo *p, char *msg)
{
    printf("%ld %d %s\n", get_time() - p->s->t.start, p->id, msg);

}

int    print_msg(t_philo *p, char *msg)
{
	int	ret;

    
	pthread_mutex_lock(&p->s->m.sig_death);
	ret = p->s->dead; 	
    if (!ret)
		print(p, msg);
	pthread_mutex_unlock(&p->s->m.sig_death);
    // pthread_mutex_unlock(&p->s->m.print);
        
    update_soup(p, msg);

    return (ret);
}