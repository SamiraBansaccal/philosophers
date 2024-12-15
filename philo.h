/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:15:18 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/14 21:12:33 by sbansacc         ###   ########.fr       */
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
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_required;
	int				someone_died;
	int				finish_eating;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_table;
//#---------------main.c------------------#

void		clean_table(t_table *table);

//#---------------init.c------------------#

long long	ft_atoll(char *num);
long long	get_time(void);
int			parse_input(t_table *table, int ac, char **av);
int			init_table(t_table *table, int ac, char **av);

//#--------philo_routine.c---------------#

void		*philo_routine(void *arg);
void		print_status(t_philo *philo, char *status);


//#--------check_death.c---------------#

void		check_death(t_table *table);

#endif