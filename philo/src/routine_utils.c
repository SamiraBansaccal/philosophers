/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:37:07 by sabansac          #+#    #+#             */
/*   Updated: 2024/12/27 16:46:13 by sbansacc         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->table->table_mutex);
	print = !philo->table->dinner_end;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (print || !ft_strncmp(status, "died", 4))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%d %d %s\n", time, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	/*else
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%d %d dinner END OUPSII %s\n", time, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}*/
}

void	smart_sleep(long long time_to_wait, t_table *table)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = get_time();
	elapsed = get_time() - start;
	while (elapsed < time_to_wait)
	{
		if (finish(table))
			break ;
		elapsed = get_time() - start;
		remaining = time_to_wait - elapsed;
		if (remaining > 1)
			usleep((remaining * 700));
		else
			while (get_time() - start < time_to_wait)
				;
	}
}

int	finish(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	if (table->dinner_end == 1)
	{
		pthread_mutex_unlock(&table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->table_mutex);
	return (0);
}
