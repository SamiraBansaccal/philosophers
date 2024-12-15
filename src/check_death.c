/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:53:09 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/15 01:37:27 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	philo_is_starving(t_philo *philo)
{
	long long now;

	now = get_time();
	pthread_mutex_lock(&philo->table->death_mutex);
	if ((now - philo->last_meal) < (philo->table->time_to_die))
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (1);
}

int	finish_eating(t_table *table)
{
	int	i;

	if (table->meals_required < 1)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (table->philos[i].meal_count < table->meals_required)
			pthread_mutex_unlock(&table->death_mutex);
			return (0);
		pthread_mutex_unlock(&table->death_mutex);
		i++;
	}
	return (1);
}

void	check_death(t_table *table)
{
	int	i;
	int	death;
	int	finito;

	while (1)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			death = philo_is_starving(&table->philos[i]);
			finito = finish_eating(table);
			if (death)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->someone_died = 1;
				pthread_mutex_unlock(&table->death_mutex);
				print_status(&table->philos[i], "died");
				return ;
			}
			if (finito)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->finish_eating = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return ;
			}
		}
		usleep(500);
	}
}
