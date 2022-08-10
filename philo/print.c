/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:14:08 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 17:13:14 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	timestamp(void)
{
	static long		start_time = 0;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start_time == 0)
	{
		start_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	start;
	long	step;
	int		sleep;

	if (philo->num_philos < 10)
		sleep = 200;
	else if (philo->num_philos < 50)
		sleep = 500;
	else if (philo->num_philos < 100)
		sleep = 1000;
	else if (philo->num_philos < 201)
		sleep = 2000;
	start = timestamp();
	while (!philo->shared->dead)
	{
		step = timestamp();
		if ((step - start) * 10000 >= time * 10000)
			break ;
		usleep(sleep);
	}
}

int	death_in_action(t_philo *philo, int action)
{
	if (action == EATS || action == SLEEPS)
		pthread_mutex_unlock(&philo->protection);
	pthread_mutex_unlock(&philo->shared->write);
	return (1);
}

char	*take_message(int action)
{
	if (action == TAKES_FORK)
		return ("has taken a fork");
	if (action == EATS)
		return ("is eating");
	if (action == SLEEPS)
		return ("is sleeping");
	if (action == THINKS)
		return ("is thinking");
	if (action == DEATH)
		return ("died");
	return ("(unknown action)");
}

void	print_action(int position, int action)
{
	char	*s;
	char	message[BUFFER_SIZE];

	message[0] = '\0';
	s = ft_itoa((int)timestamp());
	ft_strlcat(message, s, BUFFER_SIZE);
	free(s);
	ft_strlcat(message, " ", BUFFER_SIZE);
	s = ft_itoa(position);
	ft_strlcat(message, s, BUFFER_SIZE);
	free(s);
	ft_strlcat(message, " ", BUFFER_SIZE);
	s = take_message(action);
	ft_strlcat(message, s, BUFFER_SIZE);
	ft_strlcat(message, "\n", BUFFER_SIZE);
	ft_putstr_fd(message, 1);
}
