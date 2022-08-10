/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:24 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 10:29:51 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define BUFFER_SIZE	1024

# define ERROR -1
# define TAKES_FORK 4
# define EATS 5
# define THINKS 6
# define SLEEPS 7
# define DEATH 8

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

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
	sem_t			*write;
	sem_t			*forks;
	sem_t			*main;
	long			start;
	long			start_time;
	sem_t			*num_eats;
	pthread_t		checker_eats;
}				t_shared;

typedef struct s_philo
{
	t_shared		*shared;
	int				number;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			last_meal;
	sem_t			*protect;
	sem_t			*forks;
	int				pid;
	pthread_t		monitor;
	int				num_of_eats;
	int				actual_eats;
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
int			get_index(int tmp, int index);
int			init_protect_sem(t_philo *philo, char *name);
int			get_protect(t_philo *philo);

//			help_init.c
int			init_shared_sems(t_all *all);
void		init_const(t_all *all, int i);

//			init.c
int			parse_args(t_args *args, int argc, char **argv);
int			init_shared(t_all *all);
int			init_philosophers(t_all *all);
void		*check_eats(void *data);
int			start_processes(t_all *all);

//			routine.c
void		*check_death(void *data);
void		action(t_philo *philo, int action);
void		*routine(void *data);

//			time_and_print.c
long		current_time(void);
long		timestamp(long start_time);
void		ft_usleep(long time);
char		*take_message(int action);
void		print_action(int position, int action, long start_time);

//			itoa.c
char		*ft_itoa(int n);

//			lib_utils.c
int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_putstr_fd(char *s, int fd);

#endif