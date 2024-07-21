/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:04:20 by eismail           #+#    #+#             */
/*   Updated: 2024/07/21 10:17:04 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
# define PH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef struct t_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct t_philo
{
	long			index;
	long			meals_count;
	bool			full;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	philo_mtx;
}					t_philo;

struct s_table
{
	long			p_num;
	long			g_meals_count;
	long			d_time;
	long			e_time;
	long			s_time;
	long			e_num;
	long			start_siml;
	bool			end_siml;
	bool			all_ready;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	wait_mtx;
	pthread_mutex_t	write_mtx;
	t_fork			*forks;
	t_philo			*philos;
};

/* init function */
bool	ft_init(t_table *table);
void	philo_init(t_table *table);
void	assing_forks(t_philo *philo, t_fork *forks, int pos);
bool	ft_input(t_table *table, char **av);
long	ft_atoi(char *str);
/* utils */
long	get_time(void);
void	i_sleep(long t, t_table *table);
void	write_status(char *message, t_philo *philo, bool end);
void	meal_count(t_philo *philo);
bool	siml_finish(t_philo *philo);
/* rotini lyawmi */
void	dinner(t_table *table);
void	monitor(t_table *table);
void	*one(void *data);
void	*rotini(void *data);
void	eat(t_philo *philo);
/* gettiers and setters */
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	siml_finish(t_philo *philo);
#endif