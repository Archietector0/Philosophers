/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarth <tbarth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 19:39:34 by tbarth            #+#    #+#             */
/*   Updated: 2021/08/29 18:56:13 by tbarth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_global	t_global;

typedef struct s_philosoph
{
	int					index;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					is_dead;
	int					count_eat;
	t_global			*global;
	ssize_t				time_life;
	ssize_t				start_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

}						t_philosoph;

typedef struct s_global
{
	int					philo_num;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					times_to_eat;
	int					fin_time_eating;
	ssize_t				start_time;
	pthread_mutex_t		*forks_mass;
	pthread_mutex_t		block_write_chat;
	t_philosoph			*philosoph_mass;

}						t_global;

int			ft_atoi(const char *str);
size_t		ft_strlen(const	char *s);
ssize_t		get_time(ssize_t begin_time);
void		my_usleep(ssize_t time);
int			ft_myisdigit(char *str);
int			ft_error(char *str);
int			ft_checker(int argc, char **argv);
void		*monitoring(void *val);
void		print_status(t_philosoph *philo, size_t time, char *message);
void		philo_sleeping(t_philosoph *philo);
void		philo_eating(t_philosoph *philo);
void		philo_thinking(t_philosoph *philo);
void		ft_init_args(t_global *global, char **argv, int argc);
void		ft_init_ev_philo(t_global *global, int index, pthread_t *threads);
void		ft_dop(t_global *global, pthread_t *philo_ids_mass);

#endif
