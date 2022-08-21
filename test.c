/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:26:44 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/21 17:29:42 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
long int		get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		exit (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

void	opti_sleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms) // !is_dead
		usleep(time_in_ms / 10);
}

// /*
// ** Returns the timestamp in milliseconds
// */

// long    get_time(void)
// {
//     struct timeval  tp;
//     long            milliseconds;

//     gettimeofday(&tp, NULL);
//     milliseconds = tp.tv_sec * 1000;
//     milliseconds += tp.tv_usec / 1000;
//     return (milliseconds);
// }

/*
** Prints time, sleeps 200ms, repeats!
*/

int main(void)
{
    long int start_time;
		
		// Remember when we started
    start_time = get_time();

    while (1)
    {
				// Print time from start, in ms
        printf("%ld\n", get_time() - start_time);

				// Sleep 200 times 1000 microseconds (1 millisecond)
        opti_sleep(200);
    }
}

 // if (p->nb_soup < p->eat_n_times)
        //     p->nb_soup++;
        // if (p->nb_soup == p->eat_n_times)
        //     p->mutex->finished_soup++;