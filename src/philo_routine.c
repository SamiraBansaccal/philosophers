/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:22:07 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/10 23:52:11 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	time_diff;
	int			time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!philo->table->someone_died)
	{
		time_diff = get_time() - philo->table->start_time;
		time = (int)time_diff;
		ft_printf("%d %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	smart_sleep(long long time_to_wait, t_table *table)
{
	long long	start;

	start = get_time();
	while (!table->someone_died)
	{
		if (get_time() - start >= time_to_wait)
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->death_mutex);
	smart_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	dining(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->someone_died || table->finish_eating)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->death_mutex);
	philo_eat(philo);
	print_status(philo, "is sleeping");
	smart_sleep(table->time_to_sleep, table);
	print_status(philo, "is thinking");
	if (philo->id % 2 && table->time_to_eat > table->time_to_sleep)
		smart_sleep(table->time_to_eat - table->time_to_sleep, table);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
	{
		print_status(philo, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
		print_status(philo, "is thinking");
		if (table->time_to_eat > table->time_to_sleep)
			smart_sleep(table->time_to_eat - table->time_to_sleep, table);
	}
	while (dining(philo, table))
		;
	return (NULL);
}
