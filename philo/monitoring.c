/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarth <tbarth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 19:05:13 by tbarth            #+#    #+#             */
/*   Updated: 2021/08/29 19:52:48 by tbarth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philosophers.h"

int	ft_part_mon(t_global *global, int i)
{
	if (global->philosoph_mass[i].count_eat >= global->times_to_eat \
	&& global->times_to_eat != -1)
		++global->fin_time_eating;
	if (global->die_time < get_time(global->philosoph_mass[i].time_life))
	{
		global->philosoph_mass[i].is_dead = 1;
		print_status(&global->philosoph_mass[i], \
		get_time(global->start_time), "die");
		return (0);
	}
	return (1);
}

void	*monitoring(void *val)
{
	t_global	*global;
	int			i;

	global = (t_global *)val;
	while (1)
	{
		i = -1;
		global->fin_time_eating = 0;
		while (++i < global->philo_num)
			if (ft_part_mon(global, i) == 0)
				return (NULL);
		if (global->fin_time_eating == global->philo_num)
		{
			pthread_mutex_lock(&global->block_write_chat);
			return (NULL);
		}
	}
}
