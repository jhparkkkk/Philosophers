/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:24 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 21:39:46 by jeepark          ###   ########.fr       */
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

// void	free_t_proc_tab(t_proc **proc_tab)
// {
// 	int	i;
// 	int	forks;

// 	if (!proc_tab)
// 		return ;
// 	i = 0;
// 	forks = proc_tab[i]->nb_forks;
// 	while (i < forks && proc_tab[i])
// 	{
// 		if (proc_tab[i]->cmd)
// 		{
// 			if (proc_tab[i]->cmd->s)
// 			{
// 				free(proc_tab[i]->cmd->s);
// 				proc_tab[i]->cmd->s = NULL;
// 			}
// 			free(proc_tab[i]->cmd);
// 		}
// 		if (proc_tab[i]->opt)
// 			free_attr(proc_tab[i]->opt, proc_tab[i]->nb_opt);
// 		free(proc_tab[i]);
// 		i++;
// 	}
// 	free(proc_tab);
// }