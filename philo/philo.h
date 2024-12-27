/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:15:18 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/27 23:44:56 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include "./lib/libft/libft.h"
# include "./lib/ft_printf/ft_printf.h"

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meal_count;
	int				full;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	philo_mutex;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_required;
	int				dinner_end;
	int				threads_ready;
	long long		start_time;
	pthread_t		monitor_thread;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;
//#---------------main.c------------------#

void		clean_table(t_table *table);

//#---------------init.c------------------#

long long	get_time(void);
int			parse_input(t_table *table, int ac, char **av);
int			init_table(t_table *table, int ac, char **av);

//#---------------init.c------------------#

long long	ft_atoll(char *num);
void		start_dinner(t_table *table);

//#--------philo_routine.c---------------#

void		*philo_routine(void *arg);
void		wait_to_begin(t_table *table);

//#--------routine_utils.c---------------#

void		print_status(t_philo *philo, char *status);
void		smart_sleep(long long time_to_wait, t_table *table);
int			finish(t_table *table);

//#--------check_death.c---------------#

void		*check_death(void *arg);

#endif