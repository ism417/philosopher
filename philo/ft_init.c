/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:35:35 by eismail           #+#    #+#             */
/*   Updated: 2024/07/19 11:42:23 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] == ' ') || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (!((str[i] >= '0') && (str[i] <= '9')))
	{
		printf("only positive numbers\n");
		return (-1);
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] && !((str[i] >= '0') && (str[i] <= '9')))
	{
		printf("only positive numbers\n");
		return (-1);
	}
	return (res);
}

bool	ft_input(t_table *table, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (false);
	table->p_num = ft_atoi(av[1]);
	table->d_time = ft_atoi(av[2]);
	table->e_time = ft_atoi(av[3]);
	table->s_time = ft_atoi(av[4]);
	if (av[5])
	{
		if (ft_atoi(av[5]) <= 0)
			return (false);
		table->e_num = ft_atoi(av[5]);
	}
	else
		table->e_num = -1;
	return (true);
}

void	assing_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_n;

	philo_n = philo->table->p_num;
	philo->right_fork = &forks[(pos + 1) % philo_n];
	philo->left_fork = &forks[pos];
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->p_num)
	{
		philo = table->philos + i;
		philo->index = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->last_meal_time = get_time();
		philo->table = table;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		assing_forks(philo, table->forks, i);
	}
}

bool	ft_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_siml = false;
	table->all_ready = false;
	table->g_meals_count = 0;
	table->philos = malloc(sizeof(t_philo) * table->p_num);
	if (!table->philos)
		return (false);
	table->forks = malloc(sizeof(t_fork) * table->p_num);
	if (!table->forks)
		return (false);
	pthread_mutex_init(&table->table_mtx, NULL);
	pthread_mutex_init(&table->wait_mtx, NULL);
	pthread_mutex_init(&table->stop_mtx, NULL);
	pthread_mutex_init(&table->write_mtx, NULL);
	while (++i < table->p_num)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (true);
}
