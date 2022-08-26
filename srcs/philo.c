/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 23:14:51 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <pthread.h>

int main(int ac, char **av)
{
    t_set   s;
    t_philo **p;
    
    if (check_input(ac, av))
        return(printf("error\n"), EXIT_FAILURE);
    init_s(&s, av + 1, ac);
    init_mutex(&s, s.nb_philo);
    p = init_philo(&s);    
    run_thread(p);

    destroy_philo(p, (*p)->s->nb_philo);
    // int i = 0;
    // while (i < (*p)->nb_philo)
    // {
    //     pthread_mutex_destroy(&(*p)->mutex->chopsticks[i]);
    //     i++;
    // }
    // pthread_mutex_destroy(&(*p)->mutex->print);
    
    return (0);
}

// 4 500 200 2147483647
// un philo meurt au bout de 500 ms mais le prg ne s'arrete pas car les philos sont coinces dans leur sommeil
// Q : dois je attendr la fin de sommeil ou interrompre le sommeil ? 