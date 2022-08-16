/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:47 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/16 18:43:21 by jeepark          ###   ########.fr       */
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

typedef struct s_mutex
{
    pthread_mutex_t *chopsticks;
    int someone_is_dead;
}   t_mutex;

typedef struct s_philo
{
    int             idx;
    pthread_t       th; 
    pthread_mutex_t mutex;
    // *mutex
    t_param         *p;
}                   t_philo;


/**** UTILS ****/

int	ft_atoi(const char	*str);
int check_input(char **av);

/**** INIT *****/
int     init(t_philo **ph, t_param *p, char **av);
void    set_param(t_param *p, char **av);
t_philo **set_philo(t_param *p);
int     set_mutex(t_philo **ph);

/**** PHILO ****/
int run_thread(t_philo **ph, t_param *p);



/**** DESTROY ****/
void    destroy_philo(t_philo **ph);



#endif