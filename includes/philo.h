/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:47 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/19 18:17:52 by jeepark          ###   ########.fr       */
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
#include <sys/time.h>

# define CHOP "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_mutex
{
    pthread_mutex_t *chopsticks;
    int             someone_is_dead;
    int             odd;
    int             even;
    int             tmp_odd;
    int             tmp_even;
    long int        start_time;
    long int        last_soup;

}                   t_mutex;

typedef struct s_philo
{
    int        		     	id;
    pthread_t   		    th; 
    t_mutex             *mutex;
    int             		nb_philo;
    int             		time_to_die;
    int             		time_to_eat;
    int             		time_to_sleep;
    int             		eat_n_times;
	struct s_philo			*next;  
}                   t_philo;


/**** UTILS ****/

int     ft_atoi(const char	*str);
int     check_input(int ac, char **av);
void	opti_sleep(long int time_in_ms);
void    set_odd_even(t_philo **p, int nb_philo);
long int		get_time(void);

/**** INIT *****/
t_philo			*set_data(char **av);
t_philo         **init(char **av);
int				set_mutex(t_philo **p);

/**** PHILO ****/
int run_thread(t_philo **p);




/**** DESTROY ****/
void    destroy_philo(t_philo **p);



#endif