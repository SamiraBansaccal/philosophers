/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:53:09 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/27 23:36:23 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	philo_is_starving(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (0);
	}
	if ((get_time() - philo->last_meal) > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

void	*check_death(void *arg)
{
	int			i;
	t_table		*table;

	table = (t_table *)arg;
	wait_to_begin(table);
	while (!finish(table))
	{
		i = -1;
		while (++i < table->num_philos && !finish(table))
		{
			usleep(1000);
			if (philo_is_starving(&table->philos[i]))
			{
				pthread_mutex_lock(&table->table_mutex);
				table->dinner_end = 1;
				pthread_mutex_unlock(&table->table_mutex);
				print_status(&table->philos[i], "died");
			}
		}
	}
	return (NULL);
}
