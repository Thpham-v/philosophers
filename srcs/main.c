/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 04:14:59 by thpham-v          #+#    #+#             */
/*   Updated: 2022/02/28 14:20:04 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	unsigned int	ret;
	struct timeval	time;

	ret = 0;
	if (gettimeofday(&time, NULL) == -1)
	{
		perror("gettimeofday() failled");
		return (0);
	}
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	ft_usleep(unsigned int time_in_ms)
{
	unsigned int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

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
	philos = malloc(sizeof(t_p) * info.nb_philo);
	if (!philos)
		return (malloc_error());
	th = malloc(sizeof(pthread_t) * info.nb_philo);
	if (!th)
		return (malloc_error());
	forks = malloc(sizeof(pthread_mutex_t) * info.nb_philo);
	if (!forks)
		return (malloc_error());
	init_philos(philos, &info);
	distribute_forks(philos, forks, info.nb_philo);
	launching_threading(philos, &info, th);
	destroy_mutex(&info, forks);
	free_vars(philos, th, forks);
	return (0);
}
