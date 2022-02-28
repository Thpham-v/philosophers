/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:57:28 by thpham-v          #+#    #+#             */
/*   Updated: 2022/02/28 13:58:30 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_info
{
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	t_start;
	int				nb_philo;
	int				nb_meals;
	int				stop;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_msg;
	pthread_mutex_t	m_last_eat;
}				t_info;

typedef struct s_p
{
	t_info			*info;
	
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_last_eat;
	int				nb_meals;
	int				id;
	int				n;
	int				count;
	int				stop;
	pthread_t		faucheuse;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_p;

void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
int				ft_strlen(char *str);
int				ft_strcmp(const char *s1, const char *s2);
long			long_atoi(char *str);
unsigned int	get_time(void);
void			print_msg(t_p *p, char *msg);
int				init_info(int ac, char **av, t_info *info);
void			init_philos(t_p *philos, t_info *info);
void			distribute_forks(t_p *p, pthread_mutex_t *forks, int n);
void			ft_usleep(unsigned int time_in_ms);
int				launching_threading(t_p *philos, t_info *info, pthread_t *th);
void			activity(t_p *p);
void			destroy_mutex(t_info *info, pthread_mutex_t *forks);
int				malloc_error(void);
void			free_vars(t_p *philos, pthread_t *th, pthread_mutex_t *forks);
int				parsing_error(int ac, char **av);

#endif