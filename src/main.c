/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:45:01 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/14 21:12:27 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_table(t_table *table)
{
	int	i;
	if (table->philos)
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
	pthread_mutex_destroy(&table->death_mutex);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_philos == 1)
	{
		print_status(&table->philos[i], "has taken a fork");
		usleep(table->time_to_die * 1000);
		print_status(&table->philos[i], "died");
		return (1);
	}
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]))
			return (clean_table(table), 0);
		i++;
	}
	return (1);
}

void	wait_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	table;
	
	if (ac != 5 && ac != 6)
		return (write(2, "Error: wrong number of arguments\n", 31), 1);
	if (!init_table(&table, ac, av))
		return (write(2, "Error: initialization failed\n", 28), 1);
	if (!create_threads(&table))
		return (write(2, "Error: thread creation failed\n", 29), 1);
	check_death(&table);
	wait_threads(&table);
	clean_table(&table);
	return (0);
}
