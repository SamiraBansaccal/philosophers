/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:45:01 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/27 23:42:51 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->philos)
	{
		while (i < table->num_philos && &table->philos[i])
		{
			pthread_mutex_destroy(&table->philos[i].philo_mutex);
			i++;
		}
	}
	free(table->philos);
	if (table->forks)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->table_mutex);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_philos == 1)
	{
		table->start_time = get_time();
		pthread_mutex_lock(table->philos[0].first_fork);
		print_status(&table->philos[i], "has taken a fork");
		smart_sleep(table->time_to_die, table);
		print_status(&table->philos[i], "died");
		pthread_mutex_unlock(table->philos[0].first_fork);
		return (1);
	}
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]))
			return (clean_table(table), 0);
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL, check_death, table))
		return (clean_table(table), 0);
	return (1);
}

void	wait_philos_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	finish_dinner(t_table *table)
{
	wait_philos_threads(table);
	pthread_mutex_lock(&table->table_mutex);
	table->dinner_end = 1;
	pthread_mutex_unlock(&table->table_mutex);
	pthread_join(table->monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error: wrong number of arguments\n", 31);
		return (1);
	}
	if (!init_table(&table, ac, av))
	{
		write(2, "Error: initialization failed\n", 28);
		return (1);
	}
	if (!create_threads(&table))
	{
		write(2, "Error: thread creation failed\n", 29);
		return (1);
	}
	start_dinner(&table);
	finish_dinner(&table);
	clean_table(&table);
	return (0);
}
