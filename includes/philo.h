/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:47 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 14:30:19 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                                                            */
/*                               LIBRARIES                                    */       
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_param 
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_n_times;    
}       t_param;

typedef struct s_philo
{
    pthread_t       th; 
    pthread_mutex_t mutex;
    t_param         *p;
}                   t_philo;


/**** UTILS ****/

int	ft_atoi(const char	*str);
int check_input(char **av);

/**** INIT *****/
void    set_param(t_param *p, char **av);
int     set_philo(t_philo **ph, t_param *p);



#endif