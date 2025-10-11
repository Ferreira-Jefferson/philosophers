/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:55:04 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/11 17:20:30 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# define _DEFAULT_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define RED_BOLD "\033[1;31m"
# define RED "\33[31m"
# define GREEN "\33[32m"
# define YELLOW "\33[33m"
# define BLUE "\33[36m"
# define END_COLOR "\033[0m"

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_BUTLER "/philo_butler"
# define SEM_DATA_BASE "/philo_data_"
# define SEM_DEATH "/philo_death"
# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_BUTLER "/philo_butler"
# define SEM_DATA_BASE "/philo_data_"
# define SEM_DEATH "/philo_death"
# define SEM_FULL "/philo_full"

typedef struct s_common {
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_must_eat;
	long			start_time;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_butler;
	sem_t			*sem_death;
	sem_t			*sem_full;
}	t_common;

typedef struct s_philo {
	int				id_philo;
	long			last_meal;
	long			number_time_eat;
	pthread_t		monitor_thread;
	sem_t			*data_sem;
	char			data_sem_name[32];
	t_common		*common;
}	t_philo;

long	ft_get_time_ms(void);
int		ft_atoi(const char *nptr);
void	ft_start(t_common *common);
int		ft_is_only_number(char *str);
void	ft_close_all(t_common *common);
void	ft_print_message(t_philo *philo, char *message);
int		ft_init_common(int argc, char *argv[], t_common **common);
void	ft_generate_sem_name(const char *base, int id, char *buffer);
void	ft_exit_all(pid_t *pids, t_common *common);
int		ft_check_death(t_philo *philo);
int		ft_check_all_full(t_philo *philo);
void	ft_announce_death(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);

#endif