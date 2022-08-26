/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 19:33:04 by jeepark          ###   ########.fr       */
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


    // int i = 0;
    // while (i < (*p)->nb_philo)
    // {
    //     pthread_mutex_destroy(&(*p)->mutex->chopsticks[i]);
    //     i++;
    // }
    // pthread_mutex_destroy(&(*p)->mutex->print);
    
    return (0);
}