/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_buisness.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 19:57:56 by tbarth            #+#    #+#             */
/*   Updated: 2021/08/29 19:58:07 by tbarth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philosophers.h"

void	philo_eating(t_philosoph *philo)
{
	print_status(philo, get_time(philo->start_time), "eating");
	++philo->count_eat;
	philo->time_life = get_time(0);
	my_usleep(philo->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleeping(t_philosoph *philo)
{
	print_status(philo, get_time(philo->start_time), "sleeping");
	my_usleep(philo->sleep_time);
}

void	philo_thinking(t_philosoph *philo)
{
	print_status(philo, get_time(philo->start_time), "thinking");
}
