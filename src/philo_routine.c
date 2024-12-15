/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:22:07 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/15 01:37:41 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	time_diff;
	int			time;
	int			print;
	
	time_diff = get_time() - philo->table->start_time;
	time = (int)time_diff;
	pthread_mutex_lock(&philo->table->death_mutex);
	print = !philo->table->someone_died && !philo->table->finish_eating;
	pthread_mutex_unlock(&philo->table->death_mutex);
	if (print || !ft_strncmp(status, "died", 4))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		ft_printf("%d %d %s\n", time, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	smart_sleep(long long time_to_wait, t_table *table)
{
	long long	start;
	int			stop;

	print_status(table->philos, "smartslepping");
	start = get_time();
	while ((get_time() - start) < time_to_wait)
	{
		pthread_mutex_lock(&table->death_mutex);
		stop = table->someone_died || table->finish_eating;
		pthread_mutex_unlock(&table->death_mutex);
		if (stop)
			return ;
		usleep(100);
	}
}

void philo_eat(t_philo *philo)
{
    // Log pour debug : Philosophe veut prendre les fourchettes
    print_status(philo, "WANTS forks");

    // Prendre les fourchettes gauche et droite
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "HAS left fork");

    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "HAS right fork");

    // Philosophe commence à manger
    pthread_mutex_lock(&philo->table->death_mutex);
    philo->last_meal = get_time();
    philo->meal_count++;
    pthread_mutex_unlock(&philo->table->death_mutex);

    print_status(philo, "is eating");
    smart_sleep(philo->table->time_to_eat, philo->table);

    // Relâcher les fourchettes
    pthread_mutex_unlock(philo->right_fork);
    print_status(philo, "DROPS right fork");

    pthread_mutex_unlock(philo->left_fork);
    print_status(philo, "DROPS left fork");
}
/*
void	philo_eat(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (philo->id % 2)
	{
		print_status(philo, "WANT a right fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a right fork (left of x+1)");
		print_status(philo, "WANT a left fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a left fork (right of x+1)");
	}
	else
	{
		print_status(philo, "WANT a left fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a left fork (right of x+1)");
		print_status(philo, "WANT a right fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a right fork (left of x+1)");
	}
	print_status(philo, "Want to update meal");
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal = time;
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->death_mutex);
	print_status(philo, "is eating");
	smart_sleep(philo->table->time_to_eat, philo->table);
	print_status(philo, "finishh eating");
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "has DROP a right fork");
		pthread_mutex_unlock(philo->left_fork);
		print_status(philo, "has DROP left a fork");
	}
	else
	{
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "has DROP a right fork");
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo, "has DROP left a fork");
}
*/
void	philo_think(t_philo *philo)
{
	if (philo->table->time_to_eat > philo->table->time_to_sleep)
	{
		print_status(philo, "is thinking");
		smart_sleep(philo->table->time_to_eat - philo->table->time_to_sleep, philo->table);
	}
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
	if (philo->id < (philo->id + 1) % philo->table->num_philos)
	{
		philo_eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
	}
	else
	{
		philo_think(philo);
		print_status(philo, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
		philo_eat(philo);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (dining(philo, table))
		;
	return (NULL);
}
