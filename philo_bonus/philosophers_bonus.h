/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:29:59 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/06 14:18:38 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define _DEFAULT_SOURCE
# include <wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define RED_BOLD "\033[1;31m"
# define RED "\33[31m"
# define GREEN "\33[32m"
# define YELLOW "\33[33m"
# define BLUE "\33[36m"
# define END_COLOR "\033[0m"

typedef struct s_common {
	int		number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_times_must_eat;
	int		shutdown;
	long	start_time;
	sem_t	*sem_forks;
}	t_common;

typedef struct s_philo {
	int				id_philo;
	long			last_meal;
	long			number_time_eat;
	t_common		*common;
}	t_philo;

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# define SEM_FORKS "/FORKS"

// libft_bonus.c
int		ft_isdigit(int c);
int		ft_is_only_number(char *str);
int		ft_atoi(const char *nptr);

// phipholophers_bonus.c
int		ft_validation(int argc, char *argv[]);

// monitor_bonus.c
// void	*ft_monitor(void *args);

// core_bonus.c
void	ft_start(t_common *common);
// void	*ft_core(void *args);
// int		ft_should_shutdown(t_philo *philo);
// void	ft_eating(t_philo *philo);

// utils_bonus.c
void	ft_print_message(t_philo philo, char *message);
long	ft_get_time_ms(void);

// utils_init_bonus.c
int		ft_init_common(int argc, char *argv[], t_common **common);

#endif