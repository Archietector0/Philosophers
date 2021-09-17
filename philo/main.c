/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarth <tbarth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:28:04 by tbarth            #+#    #+#             */
/*   Updated: 2021/08/29 18:57:40 by tbarth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philosophers.h"

void	print_status(t_philosoph *philo, size_t time, char *message)
{
	pthread_mutex_lock(&philo->global->block_write_chat);
	printf("%zu Philo %d: %s\n", time, philo->index, message);
	if (!philo->is_dead)
		pthread_mutex_unlock(&philo->global->block_write_chat);
}

void	take_fork(t_philosoph *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, get_time(philo->start_time), "take LEFT fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, get_time(philo->start_time), "take RIGHT fork");
}

void	*ft_philo_process(void *philo)
{
	t_philosoph	*philosoph;

	philosoph = (t_philosoph *)philo;
	if (philosoph->index % 2 == 0)
		my_usleep(philosoph->eat_time / 2);
	while (1)
	{
		take_fork(philosoph);
		philo_eating(philosoph);
		philo_sleeping(philosoph);
		philo_thinking(philosoph);
	}
}

void	ft_start_sim(t_global *global)
{
	pthread_t		*philo_ids_mass;
	int				i;

	global->forks_mass = malloc(sizeof(pthread_mutex_t) * global->philo_num);
	global->philosoph_mass = malloc(sizeof(t_philosoph) * global->philo_num);
	philo_ids_mass = malloc(sizeof(pthread_t) * global->philo_num);
	i = 0;
	while (i < global->philo_num)
	{
		pthread_mutex_init(&global->forks_mass[i], NULL);
		++i;
	}
	i = 0;
	pthread_mutex_init(&global->block_write_chat, NULL);
	while (i < global->philo_num)
	{
		ft_init_ev_philo(global, i, philo_ids_mass);
		global->philosoph_mass[i].index = i;
		pthread_create(&philo_ids_mass[i], NULL, \
		ft_philo_process, (void *)&global->philosoph_mass[i]);
		++i;
	}
	ft_dop(global, philo_ids_mass);
}

int	main(int argc, char **argv)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	global->start_time = get_time(0);
	if (argc > 6 || argc < 5)
		return (ft_error("ERROR: Incorrect number of arguments."));
	if (ft_checker(argc, argv) == -1)
		return (ft_error("ERROR: Invalid arguments."));
	ft_init_args(global, argv, argc);
	ft_start_sim(global);
	free(global);
	return (0);
}
