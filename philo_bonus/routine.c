/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:29 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/01 18:48:44 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *data)
{
	long	time;
	t_philo	*philo;
	int		sleep;

	philo = (t_philo *)data;
	sleep = philo->time_to_eat;
	while (42)
	{
		sem_wait(philo->protect);
		time = timestamp(philo->shared->start_time);
		if (time - philo->last_meal >= philo->time_to_die)
		{
			sem_wait(philo->shared->write);
			print_action(philo->number, DEATH, philo->shared->start_time);
			sem_post(philo->shared->main);
			return (NULL);
		}
		sem_post(philo->protect);
		if (philo->shared->dead)
			break ;
		ft_usleep(1);
	}
	return (NULL);
}

void	action(t_philo *philo, int action)
{
	sem_wait(philo->protect);
	sem_wait(philo->shared->write);
	if (action == EATS)
	{
		philo->last_meal = timestamp(philo->shared->start_time);
		print_action(philo->number, EATS, philo->shared->start_time);
		philo->actual_eats++;
	}
	else if (action == TAKES_FORK)
		print_action(philo->number, TAKES_FORK, philo->shared->start_time);
	else if (action == SLEEPS)
	{
		if (philo->actual_eats == philo->num_of_eats)
			sem_post(philo->shared->num_eats);
		print_action(philo->number, SLEEPS, philo->shared->start_time);
	}
	else if (action == THINKS)
		print_action(philo->number, THINKS, philo->shared->start_time);
	sem_post(philo->shared->write);
	sem_post(philo->protect);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (pthread_create(&philo->monitor, NULL, check_death, (void *)philo))
		return (NULL);
	philo->last_meal = philo->shared->start;
	if (philo->number % 2 == 0)
		ft_usleep(philo->time_to_eat * 0.9);
	while (philo->shared->dead == 0)
	{
		sem_wait(philo->forks);
		action(philo, TAKES_FORK);
		sem_wait(philo->forks);
		action(philo, TAKES_FORK);
		action(philo, EATS);
		ft_usleep(philo->time_to_eat);
		action(philo, SLEEPS);
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_usleep(philo->time_to_sleep);
		action(philo, THINKS);
	}
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
