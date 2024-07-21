/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotini.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:42:01 by eismail           #+#    #+#             */
/*   Updated: 2024/07/21 10:15:04 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	write_status("has taken a fork\n", philo, false);
	pthread_mutex_lock(&philo->left_fork->fork);
	write_status("has taken a fork\n", philo, false);
	write_status("is eating\n", philo, false);
	i_sleep(philo->table->e_time, philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time());
	philo->meals_count++;
	if (philo->meals_count == philo->table->e_num)
		set_bool(&philo->philo_mtx, &philo->full, true);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*rotini(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *) data;
	while (get_bool(&philo->table->wait_mtx, &philo->table->all_ready) == false)
		;
	if (philo->index % 2 == 0)
	{
		write_status("is sleeping\n", philo, false);
		i_sleep(philo->table->s_time, philo->table);
	}
	while (get_bool(&philo->table->stop_mtx, &philo->table->end_siml) == false)
	{
		write_status("is thinking\n", philo, false);
		eat(philo);
		write_status("is sleeping\n", philo, false);
		i_sleep(philo->table->s_time, philo->table);
		if (get_bool(&philo->philo_mtx, &philo->full) == true)
			return (NULL);
	}
	return (NULL);
}

void	*one(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	printf("0 1 has taken a fork\n");
	i_sleep(philo->table->d_time, philo->table);
	write_status("died\n", philo, true);
	return (NULL);
}

bool	ft_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->p_num)
	{
		if (!get_bool(&table->philos[i].philo_mtx, &table->philos[i].full))
			return (false);
		i++;
	}
	return (true);
}

void	monitor(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < table->p_num) 
		{
			if (ft_full(table))
				return ;
			if (siml_finish(&table->philos[i]))
			{
				set_bool(&table->stop_mtx, &table->end_siml, true);
				write_status("died\n", &table->philos[i], true);
				return ;
			}
			i++;
		}
	}
}
