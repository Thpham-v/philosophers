/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 04:20:57 by thpham-v          #+#    #+#             */
/*   Updated: 2022/04/11 07:32:02 by thpham-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_p *p, char *msg)
{
	pthread_mutex_lock(&p->info->m_stop);
	if (p->info->stop == 1)
	{
		pthread_mutex_unlock(&p->info->m_stop);
		return ;
	}
	if (!ft_strcmp(msg, "died"))
		p->info->stop = 1;
	pthread_mutex_unlock(&p->info->m_stop);
	printf("%7dms  %3d    %s\n", get_time() - p->info->t_start, p->id, msg);
}

void	right_handed(t_p *p)
{
	pthread_mutex_lock(p->r_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->r_fork);
		ft_usleep(p->t_die);
		return ;
	}
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "is eating");
	pthread_mutex_unlock(&p->info->m_msg);
	p->count++;
	pthread_mutex_lock(&p->info->m_last_eat);
	p->t_last_eat = get_time();
	pthread_mutex_unlock(&p->info->m_last_eat);
	ft_usleep(p->t_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

void	left_handed(t_p *p)
{
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->l_fork);
		ft_usleep(p->t_die);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "is eating");
	pthread_mutex_unlock(&p->info->m_msg);
	p->count++;
	pthread_mutex_lock(&p->info->m_last_eat);
	p->t_last_eat = get_time();
	pthread_mutex_unlock(&p->info->m_last_eat);
	ft_usleep(p->t_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	eat_activity(t_p *p)
{
	if (p->id % 2 == 0)
		right_handed(p);
	else
		left_handed(p);
}

void	activity(t_p *p)
{
	eat_activity(p);
	if (p->nb_meals != -1 && p->count == p->nb_meals)
	{
		pthread_mutex_lock(&p->info->m_stop);
		p->stop = 1;
		pthread_mutex_unlock(&p->info->m_stop);
		return ;
	}
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "is sleeping");
	pthread_mutex_unlock(&p->info->m_msg);
	ft_usleep(p->t_sleep);
	pthread_mutex_lock(&p->info->m_msg);
	print_msg(p, "is thinking");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n % 2 != 0)
		ft_usleep(100);
}
