/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:14:04 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 15:12:47 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define BUFFER_SIZE	1024

# define ERROR -1
# define TAKES_FORK 104
# define EATS 100
# define THINKS 101
# define SLEEPS 102
# define DEATH 103

# define TOOK_ONE 204
# define TOOK_TWO 205

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eats;
}				t_args;

typedef struct s_shared
{
	int				dead;
	long			*t_last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	int				ate_enough;
	long			start;
}				t_shared;

typedef struct s_philo
{
	t_shared		*shared;
	int				number_id;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	int				actual_eats;
	pthread_mutex_t	protection;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_t		monitor;
	pthread_t		thread;
}				t_philo;

typedef struct s_all
{
	t_args			*args;
	t_philo			*philos;
	t_shared		shared;
}				t_all;

//			check_args.c
int			check_overflow(const char *str, int *nb);
int			check_args(int argc, char **argv);

//			init.c
int			parse_args(t_args *args, int argc, char **argv);
int			init_shared(t_all *all);
void		init_const(t_all *all, int i);
int			init_philos(t_all *all);
int			start_threads(t_all *all);

//			print.c
long		timestamp(void);
void		ft_usleep(t_philo *philo, long time);
int			death_in_action(t_philo *philo, int action);
char		*take_message(int action);
void		print_action(int position, int action);

//			routine_utils.c
int			death_conditions(t_philo *philo, long time);
int			unlock_if_locked(t_philo *philo, int amount);

//			routine.c
void		*check_death(void *data);
int			action(t_philo *philo, int action);
int			sequence(t_philo *philo);
void		*routine(void *data);

//			itoa.c
char		*ft_itoa(int n);

//			utils.c
int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_putstr_fd(char *s, int fd);

#endif