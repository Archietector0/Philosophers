/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarth <tbarth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:44:38 by tbarth            #+#    #+#             */
/*   Updated: 2021/08/29 18:55:57 by tbarth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philosophers.h"

void	ft_init_ev_philo(t_global *global, int index, pthread_t *threads)
{
	global->philosoph_mass[index].die_time = global->die_time;
	global->philosoph_mass[index].eat_time = global->eat_time;
	global->philosoph_mass[index].sleep_time = global->sleep_time;
	global->philosoph_mass[index].start_time = global->start_time;
	global->philosoph_mass[index].index = index;
	global->philosoph_mass[index].is_dead = 0;
	global->philosoph_mass[index].time_life = get_time(0);
	global->philosoph_mass[index].left_fork = \
		&global->forks_mass[index];
	global->philosoph_mass[index].right_fork = \
		&global->forks_mass[(index + 1) % global->philo_num];
	global->philosoph_mass[index].global = global;
	global->philosoph_mass[index].thread = threads[index];
	global->philosoph_mass[index].count_eat = 0;
}

void	ft_init_args(t_global *global, char **argv, int argc)
{
	global->philo_num = ft_atoi(argv[1]);
	global->die_time = ft_atoi(argv[2]);
	global->eat_time = ft_atoi(argv[3]);
	global->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		global->times_to_eat = ft_atoi(argv[5]);
	else
		global->times_to_eat = -1;
}

void	ft_dop(t_global *global, pthread_t *philo_ids_mass)
{
	pthread_t		check_death;

	pthread_create(&check_death, NULL, monitoring, global);
	pthread_join(check_death, NULL);
	pthread_detach(check_death);
	free(global->forks_mass);
	free(global->philosoph_mass);
	free(philo_ids_mass);
}
