/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:01:02 by eismail           #+#    #+#             */
/*   Updated: 2024/07/21 10:16:21 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ft_clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->p_num)
		pthread_join(table->philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->p_num)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mtx);
		pthread_mutex_destroy(&table->forks->fork);
	}
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->wait_mtx);
	pthread_mutex_destroy(&table->stop_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	free(table->forks);
	free(table->philos);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	set_long(&table->table_mtx, &table->start_siml, get_time());
	if (table->p_num == 1)
	{
		pthread_create(&table->philos[0].thread_id, NULL, one,
			&table->philos[0]);
		return ;
	}
	while (++i < table->p_num)
		pthread_create(&table->philos[i].thread_id, NULL, rotini,
			&table->philos[i]);
	set_bool(&table->wait_mtx, &table->all_ready, true);
	monitor(table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (!ft_input(&table, av))
			return (1);
		if (!ft_init(&table))
			return (1);
		dinner(&table);
		ft_clean(&table);
	}
	else
	{
		printf("error input\n");
		return (1);
	}
	return (0);
}
