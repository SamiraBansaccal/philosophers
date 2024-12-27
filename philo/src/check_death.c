/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:53:09 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/27 16:46:16 by sbansacc         ###   ########.fr       */
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
	//print_status(table->philos, "DEBUG: MONITOR passed wait_to_begin");
	while (!finish(table))
	{
		
		i = -1;
		while (++i < table->num_philos && !finish(table))
		{
			usleep(1000);
			//print_status(&table->philos[i], "DEBUG: MONITOR start check");
			if (philo_is_starving(&table->philos[i]))
			{
				//print_status(&table->philos[i], "DEBUG: MONITOR deaaadphilo");
				pthread_mutex_lock(&table->table_mutex);
				table->dinner_end = 1;
				pthread_mutex_unlock(&table->table_mutex);
				print_status(&table->philos[i], "died");
			}
		}
	}
	return (NULL);
}
