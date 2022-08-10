/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:13:36 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 10:29:21 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(t_args *args, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		free(args);
		return (ERROR);
	}
	args->num_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_of_eats = ft_atoi(argv[5]);
	else
		args->num_of_eats = 0;
	if (args->num_philos < 1 || args->num_philos > 200
		|| args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0 || args->num_of_eats < 0)
	{
		ft_putstr_fd("Invalid arguments\n", 2);
		free(args);
		return (ERROR);
	}
	return (0);
}

int	init_shared(t_all *all)
{
	int	i;

	all->shared.dead = 0;
	all->shared.t_last_meal = (long *) malloc(sizeof(long)
			* all->args->num_philos);
	all->shared.forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* all->args->num_philos);
	if (!all->shared.forks || !all->shared.t_last_meal)
	{
		free(all->shared.t_last_meal);
		free(all->args);
		return (ERROR);
	}
	i = -1;
	while (++i < all->args->num_philos)
		pthread_mutex_init(&all->shared.forks[i], NULL);
	pthread_mutex_init(&all->shared.write, NULL);
	all->shared.ate_enough = 0;
	return (0);
}

void	init_const(t_all *all, int i)
{
	all->philos[i].number_id = i + 1;
	all->philos[i].num_philos = all->args->num_philos;
	all->philos[i].time_to_die = all->args->time_to_die;
	all->philos[i].time_to_eat = all->args->time_to_eat;
	all->philos[i].time_to_sleep = all->args->time_to_sleep;
	all->philos[i].num_of_eats = all->args->num_of_eats;
	all->philos[i].actual_eats = 0;
	all->philos[i].shared = &all->shared;
}

int	init_philos(t_all *all)
{
	int	i;

	all->philos = (t_philo *) malloc(sizeof(t_philo) * all->args->num_philos);
	if (!all->philos)
	{
		free(all->args);
		free(all->shared.t_last_meal);
		pthread_mutex_destroy(&all->shared.write);
		return (ERROR);
	}
	i = -1;
	while (++i < all->args->num_philos)
	{
		pthread_mutex_init(&all->philos[i].protection, NULL);
		init_const(all, i);
		all->philos[i].fork_l = &all->shared.forks[i];
		if (i + 1 == all->args->num_philos)
			all->philos[i].fork_r = &all->shared.forks[0];
		else
			all->philos[i].fork_r = &all->shared.forks[i + 1];
	}
	return (0);
}

int	start_threads(t_all *all)
{
	int	i;

	all->shared.start = timestamp();
	i = -1;
	while (++i < all->args->num_philos)
	{
		all->shared.t_last_meal[i] = all->shared.start;
		if (pthread_create(&all->philos[i].thread, NULL,
				routine, (void *)&all->philos[i]) != 0)
			return (ERROR);
	}
	return (0);
}
