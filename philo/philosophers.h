/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:29:59 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 09:29:08 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define _DEFAULT_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED_BOLD "\033[1;31m"
# define RED "\33[31m"
# define GREEN "\33[32m"
# define YELLOW "\33[33m"
# define BLUE "\33[36m"
# define END_COLOR "\033[0m"

# define PHILO_MAX 150

typedef struct s_common
{
	int		number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_times_must_eat;
}	t_common;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	int				*dead;
	t_common		common;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

# define INT_MIN -2147483648
# define INT_MAX 2147483647

// libft.c
int		ft_isdigit(int c);
int		ft_is_only_number(char *str);
int		ft_atoi(const char *nptr);

// monitor.c
void	*ft_monitor(void *args);

// core.c
int		ft_thread_create(t_table *table, pthread_mutex_t *forks);

// utils_init.c
int		ft_init_mutex(t_common **common);
void	ft_init_common(int argc, char *argv[], t_common *common);
void	ft_init_philos(t_common *common, t_philo *philos, \
	t_table *table, pthread_mutex_t *forks);
void	ft_init_table(t_table *table, t_philo *philos);
void	ft_init_forks(pthread_mutex_t *forks, int philo_num);

// utils.c
long	ft_get_time_ms(void);
int		ft_usleep(size_t milliseconds);
void	ft_print_message(char *str, t_philo *philo, int id);
void	ft_destory_all(t_table *table, pthread_mutex_t *forks);
int		ft_check_if_any_death(t_philo *philo);

#endif