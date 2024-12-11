/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:53:09 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/10 23:51:01 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	philo_is_starving(t_philo *philo)
{
	long long now;

	now = get_time();
	if ((now - philo->last_meal) < (philo->table->time_to_die))
		return (0);
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
		if (table->philos[i].meal_count < table->meals_required)
			return (0);
		i++;
	}
	return (1);
}

void	check_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			pthread_mutex_lock(&table->death_mutex);
			if (philo_is_starving(&table->philos[i]))
			{
				print_status(&table->philos[i], "died");
				table->someone_died = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return ;
			}
			if (finish_eating(table))
			{
				table->finish_eating = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return ;
			}
			pthread_mutex_unlock(&table->death_mutex);
		}
		usleep(100);
	}
}
