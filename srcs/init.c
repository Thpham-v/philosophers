/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 04:20:57 by thpham-v          #+#    #+#             */
/*   Updated: 2022/02/28 14:20:48 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int ac, char **av, t_info *info)
{
	if (parsing_error(ac, av) == -1)
		return (-1);
	info->nb_philo = (int)long_atoi(av[1]);
	info->t_to_die = (unsigned int)long_atoi(av[2]);
	info->t_to_eat = (unsigned int)long_atoi(av[3]);
	info->t_to_sleep = (unsigned int)long_atoi(av[4]);
	if (ac == 6)
		info->n_meals = (int)long_atoi(av[5]);
	else
		info->n_meals = -1;
	info->stop = 0;
	pthread_mutex_init(&info->m_stop, NULL);
	pthread_mutex_init(&info->m_msg, NULL);
	pthread_mutex_init(&info->m_last_eat, NULL);
	return (0);
}

void	init_philos(t_p *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		philos[i].info = info;
		philos[i].id = i + 1;
		philos[i].n = info->nb_philo;
		philos[i].count = 0;
		philos[i].stop = 0;
		philos[i].t_die = info->t_to_die;
		philos[i].t_eat = info->t_to_eat;
		philos[i].t_sleep = info->t_to_sleep;
		philos[i].n_meals = info->n_meals;
		i++;
	}
}

void	distribute_forks(t_p *p, pthread_mutex_t *forks, int n)
{
	int	i;

	pthread_mutex_init(&forks[0], NULL);
	p[0].l_fork = &forks[0];
	p[0].r_fork = NULL;
	p[0].r_fork = &forks[n - 1];
	i = 1;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		p[i].l_fork = &forks[i];
		p[i].r_fork = &forks[i - 1];
		i++;
	}
}
