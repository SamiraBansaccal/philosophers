/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:18:19 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/26 07:23:28 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_atoll(char *str)
{
	size_t		i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	parse_input(t_table *table, int ac, char **av)
{
	table->num_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoll(av[2]);
	table->time_to_eat = ft_atoll(av[3]);
	table->time_to_sleep = ft_atoll(av[4]);
	table->meals_required = -1;
	if (ac == 6)
		table->meals_required = ft_atoi(av[5]);
	if (table->num_philos < 1 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60
		|| (table->meals_required < 1 && table->meals_required != -1))
		return (0);
	return (1);
}

void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (!(i % 2))
		{
			table->philos[i].first_fork = &table->forks[i];
			table->philos[i].second_fork
				= &table->forks[(i + 1) % table->num_philos];
		}
		else
		{
			table->philos[i].first_fork
				= &table->forks[(i + 1) % table->num_philos];
			table->philos[i].second_fork = &table->forks[i];
		}
		i++;
	}
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = NULL;
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meal_count = 0;
		table->philos[i].full = 0;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].philo_mutex, NULL);
		i++;
	}
	assign_forks(table);
	return (1);
}

int	init_table(t_table *table, int ac, char **av)
{
	int	i;

	if (!parse_input(table, ac, av))
		return (0);
	i = 0;
	table->dinner_end = 0;
	table->threads_ready = 0;
	table->forks = NULL;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (0);
	if (!init_philos(table))
	{
		free(table->forks);
		return (0);
	}
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->table_mutex, NULL);
	return (1);
}
