/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:08 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 10:29:44 by lholdo           ###   ########.fr       */
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
		ft_putstr_fd("Invalid parameters\n", 2);
		free(args);
		return (ERROR);
	}
	if (args->num_of_eats == 0)
		args->num_of_eats = -1;
	return (0);
}

int	init_shared(t_all *all)
{
	int	i;

	all->shared.dead = 0;
	all->shared.t_last_meal = (long *) malloc(sizeof(long)
			* all->args->num_philos);
	if (!all->shared.t_last_meal)
	{
		free(all->args);
		return (ERROR);
	}
	i = 0;
	while (i < all->args->num_philos)
	{
		all->shared.t_last_meal[i] = 0;
		i++;
	}
	if (init_shared_sems(all))
		return (ERROR);
	return (0);
}

int	init_philosophers(t_all *all)
{
	int	i;

	all->philos = (t_philo *) malloc(sizeof(t_philo) * all->args->num_philos);
	if (!all->philos)
	{
		free(all->args);
		free(all->shared.t_last_meal);
		return (ERROR);
	}
	i = 0;
	while (i < all->args->num_philos)
	{
		if (get_protect(&all->philos[i]))
		{
			free(all->philos);
			free(all->shared.t_last_meal);
			free(all->args);
			return (ERROR);
		}
		init_const(all, i);
		i++;
	}
	return (0);
}

void	*check_eats(void *data)
{
	t_all	*all;
	int		i;

	all = data;
	i = 0;
	while (i < all->args->num_philos)
	{
		sem_wait(all->shared.num_eats);
		i++;
	}
	sem_wait(all->shared.write);
	sem_post(all->shared.main);
	return (NULL);
}

int	start_processes(t_all *all)
{
	int	i;

	if (pthread_create(&all->shared.checker_eats, NULL,
			check_eats, (void *)all))
		return (ERROR);
	if (pthread_detach(all->shared.checker_eats))
		return (ERROR);
	all->shared.start_time = current_time();
	all->shared.start = timestamp(all->shared.start_time);
	i = -1;
	while (++i < all->args->num_philos)
	{
		all->philos[i].pid = fork();
		if (all->philos[i].pid == ERROR)
			return (ERROR);
		if (all->philos[i].pid == 0)
			routine(&all->philos[i]);
	}
	sem_wait(all->shared.main);
	sem_close(all->shared.write);
	return (0);
}
