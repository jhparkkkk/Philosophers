/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeepark <jeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:48:32 by jeepark           #+#    #+#             */
/*   Updated: 2022/08/17 14:40:13 by jeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo(t_philo **p)
{
    t_philo	*node;
    t_philo	*tmp;  
    
    node = NULL;
    tmp = NULL;
    if (!*p)
        return;
    node = *p;
    while (node)
    {
        // if (node->mutex)
        //     free(node->mutex);
    	tmp = node;
    	node = node->next;
    	free(tmp);
    }
    free(p);
}