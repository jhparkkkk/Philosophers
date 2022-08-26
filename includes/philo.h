/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:47 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/26 16:25:45 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

# define CHOP "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

# define STOP 1

typedef struct t_mutex
{
	pthread_mutex_t *chop;
	pthread_mutex_t print;
	pthread_mutex_t sig_death;
}					t_mutex;

typedef struct s_time
{
    long int    start;
    int			to_die;
    int			to_eat;
    int			to_sleep;
    int			eat_n_times;
}       		t_time;

typedef struct s_set
{
    int		nb_philo;
    int		dead;
	t_time	t;
	t_mutex m;
}       t_set;

typedef struct s_philo
{
    int        		     	id;
    pthread_t   		    th; 
    long int                last_soup;
    int                     nb_soup;
    int                     alive;
	t_set					*s;  
}                   		t_philo;

int		check_input(int ac, char **av);
void	init_s(t_set *s, char **av);
int    init_mutex(t_set *s, int total);
t_philo **init_philo(t_set *s);
int run_thread(t_philo **p);
void	opti_sleep(long int time_in_ms);
long int		get_time(void);
int   print_msg(t_philo *p, char *msg);
void    grab_chopsticks(t_philo *p);
void    drop_chopsticks(t_philo *p);
int who_dead(t_philo *p);
void    *watch_death(void *arg);
void	*routine(void *arg);
int	ft_strcmp(char *s1, char *s2);











int	ft_atoi(const char	*str);






#endif