/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:36:08 by eismail           #+#    #+#             */
/*   Updated: 2024/07/20 10:39:01 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

long	get_time(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	i_sleep(long t, t_table *table)
{
	long	time1;

	time1 = get_time();
	while ((get_time() - time1) < t)
	{
		if (get_bool(&table->stop_mtx, &table->end_siml) == true)
			break ;
		usleep(100);
	}
}

void	write_status(char *message, t_philo *philo, bool end)
{
	long	start;

	pthread_mutex_lock(&philo->table->write_mtx);
	start = get_long(&philo->table->table_mtx, &philo->table->start_siml);
	if (get_bool(&philo->table->stop_mtx, &philo->table->end_siml) == false
		|| end == true)
		printf("%ld %ld %s", get_time() - start, philo->index, message);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mtx);
	philo->table->g_meals_count++;
	pthread_mutex_unlock(&philo->philo_mtx);
}

bool	siml_finish(t_philo *philo)
{
	long	last_meal;

	last_meal = get_long(&philo->philo_mtx, &philo->last_meal_time);
	if ((get_time() - last_meal) >= philo->table->d_time)
		return (true);
	return (false);
}
