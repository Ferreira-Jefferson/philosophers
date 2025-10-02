/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:29:59 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/02 10:16:46 by jtertuli         ###   ########.fr       */
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

typedef struct s_common {
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_must_eat;
	int				shutdown;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	shutdown_mutex;
	pthread_mutex_t	printf_mutex;
}	t_common;

typedef struct s_philo {
	int				id_philo;
	long			last_meal;
	long			number_time_eat;
	pthread_mutex_t	last_meal_mutex;
	t_common		*common;
}	t_philo;

# define INT_MIN -2147483648
# define INT_MAX 2147483647

// libft.c
int		ft_isdigit(int c);
int		ft_is_only_number(char *str);
int		ft_atoi(const char *nptr);

// phipholophers.c
int		ft_validation(int argc, char *argv[]);

// monitor.c
void	*ft_monitor(void *args);

// core.c
void	ft_start(t_common **common);
void	*ft_core(void *args);
int		ft_should_shutdown(t_philo *philo);
void	ft_eating(t_philo *philo);

// utils_core.c
void	ft_create(pthread_t	*thr_philos, pthread_t	*thr_monitor, \
	t_philo *philos, t_common *common);
void	ft_get_forks_id(t_philo *philo, int *left_fork, int *right_fork);

// utils.c
void	ft_print_message(t_philo *philo, char *message);
void	ft_join(int quantity, pthread_t *thr_philos, pthread_t	*thr_monitor);
void	ft_destroy_mutex(t_common *common);
void	ft_free_common(t_common **common);
long	ft_get_time_ms(void);

// utils_init.c
int		ft_init_mutex(t_common **common);
int		ft_init_common(int argc, char *argv[], t_common **common);

#endif