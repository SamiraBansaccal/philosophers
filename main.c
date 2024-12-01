/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:45:01 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/29 02:45:07 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (write(2, "", ft_strlen()), 1);
	if (!init_data())
		return (write(2, "", ft_strlen()), 1);
	
	return (0);
}