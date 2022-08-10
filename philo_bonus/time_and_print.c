/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:27 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 17:18:40 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	timestamp(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

void	ft_usleep(long time)
{
	long	start;
	long	step;

	start = current_time();
	while (42)
	{
		step = current_time();
		if ((step - start) >= time)
			break ;
		usleep(500);
	}
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

void	print_action(int position, int action, long start_time)
{
	char	*s;
	char	message[BUFFER_SIZE];

	message[0] = '\0';
	s = ft_itoa((int)timestamp(start_time));
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
