/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 23:41:18 by sabansac          #+#    #+#             */
/*   Updated: 2024/12/27 23:42:58 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_atoll(char *str)
{
	size_t		i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

void	start_dinner(t_table *table)
{
	table->start_time = get_time();
	pthread_mutex_lock(&table->table_mutex);
	table->threads_ready = 1;
	pthread_mutex_unlock(&table->table_mutex);
}
