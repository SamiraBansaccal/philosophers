/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:22:07 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/27 16:48:24 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	//print_status(philo, "DEBUG WANT fork");
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	philo->meal_count++;
	//print_status(philo, "DEBUG: meal count ++"); 
	print_status(philo, "is eating");
	smart_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_required > 0
		&& philo->meal_count == philo->table->meals_required)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		philo->full = 1;
		pthread_mutex_unlock(&philo->philo_mutex);
		//print_status(philo, "DEBUG: is now FULL");
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_think(t_philo *philo, int first_call)
{
	long long	time_to_think;

	if (!(philo->table->num_philos % 2))
	{
		time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep;
		//print_status(philo, ft_itoa((int)time_to_think));
	}
	else
		time_to_think = 2 * philo->table->time_to_eat - philo->table->time_to_sleep;
	if (time_to_think > 0)
	{
		if (!first_call)
		{
			print_status(philo, "is thinking");
			//if (!philo->table->num_philos % 2)
			//	print_status(philo, "time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep");
		}
		smart_sleep(time_to_think * 0.42, philo->table);
	}
}
void	desync_philos(t_philo *philo)
{
	if (!(philo->table->num_philos % 2))
	{
		if (!(philo->id % 2))
			smart_sleep(30, philo->table);
	}
	else if (philo->table->num_philos % 2)
	{
		if (philo->id % 2)
			philo_think(philo, 1);
	}
}

void	dining(t_philo *philo, t_table *table)
{
	philo_eat(philo);
	print_status(philo, "is sleeping");
	smart_sleep(table->time_to_sleep, philo->table);
	//print_status(philo, "DEBUG woke up");
	philo_think(philo, 0);
}

void	wait_to_begin(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->threads_ready == 1)
		{
			pthread_mutex_unlock(&table->table_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->table_mutex);
	}
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	wait_to_begin(table);
	//print_status(philo, "DEBUG: passed wait_to_begin");
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = table->start_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	//print_status(philo, "DEBUG: ok letsgooo");
	desync_philos(philo);
	while (!finish(table) && !philo->full)
	{
	//	print_status(philo, "DEBUG: start DINNER");
		dining(philo, table);
	}
	//print_status(philo, "DEBUG: full ->exiting routine");
	return (NULL);
}
