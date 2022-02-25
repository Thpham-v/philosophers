/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 04:14:59 by thpham-v          #+#    #+#             */
/*   Updated: 2022/02/25 04:19:33 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info			info;
	t_p				*philos;
	pthread_t		*th;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6 || init_info(ac, av, &info) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
	philos = malloc(sizeof(t_p) * info.n_philo);
	if (!philos)
		return (malloc_error());
	th = malloc(sizeof(pthread_t) * info.n_philo);
	if (!th)
		return (malloc_error());
	forks = malloc(sizeof(pthread_mutex_t) * info.n_philo);
	if (!forks)
		return (malloc_error());
	init_philos(philos, &info);
	distribute_forks(philos, forks, info.n_philo);
	launching_threading(philos, &info, th);
	destroy_mutex(&info, forks);
	free_vars(philos, th, forks);
	return (0);
}
