#include "philosophers_bonus.h"

void ft_clear_semaphore(t_common *common)
{
	sem_close(common->sem_forks);
	sem_unlink(SEM_FORKS);
}

void ft_clear_semaphore_philo(t_philo *philo)
{
	sem_close(philo->sem_last_meal);
	sem_close(philo->sem_number_time_eat);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_NUMBER_TIME_EAT);
}

void ft_exit_all(pid_t *pids, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while (wait(NULL) > 0)
		;
}

void	ft_eating(t_philo *philo)
{
	sem_wait(philo->common->sem_forks);
	ft_print_message(philo, "has taken a fork");
	if (philo->common->number_of_philosophers > 1)
	{
		sem_wait(philo->common->sem_forks);
		ft_print_message(philo, "has taken a fork");
	}
	sem_wait(philo->sem_last_meal);
	philo->last_meal = ft_get_time_ms();
	sem_post(philo->sem_last_meal);
	sem_wait(philo->sem_number_time_eat);
	philo->number_time_eat++;
	sem_post(philo->sem_number_time_eat);
	ft_print_message(philo, "is eating");
	usleep(philo->common->time_to_eat * 1000);
	if (philo->common->number_of_philosophers > 1)
		sem_post(philo->common->sem_forks);
	sem_post(philo->common->sem_forks);	
}

void *ft_monitor(void *args)
{
	int		fed;
	t_philo	*philo;
	long	time_to_die;
	int		should_shutdown;
	long	times_eaten;

	philo = (t_philo *) args;
	while (1)
	{
		sem_wait(philo->sem_last_meal);
		time_to_die = philo->common->time_to_die;
		should_shutdown = ft_get_time_ms() > philo->last_meal + time_to_die;
		sem_post(philo->sem_last_meal);
		if (should_shutdown)
		{
			ft_clear_semaphore_philo(philo);
			exit(1);
		}
		fed = 0;
		sem_wait(philo->sem_number_time_eat);
		if (philo->common->number_of_times_must_eat != -1)
		{
			times_eaten = philo->number_time_eat;
			fed = times_eaten >= philo->common->number_of_times_must_eat;
		}
		sem_post(philo->sem_number_time_eat);
		if (fed)
		{
			ft_clear_semaphore_philo(philo);
			exit(0);
		}
		usleep(1000);
	}
	return (NULL);
}

void ft_children(t_common *common, int id)
{
	t_philo philo;
	pthread_t thr_monitor;

	philo = (t_philo) {id, ft_get_time_ms(), 0, NULL, NULL, common};
	ft_init_semaphore_philo(&philo);
	pthread_create(&thr_monitor, NULL, &ft_monitor, &philo);
	while (1)
	{
		ft_eating(&philo);
		ft_print_message(&philo, "is sleeping");
		usleep(philo.common->time_to_sleep * 1000);
		ft_print_message(&philo, "is thinking");
		usleep(100);
	}
	if (philo.common->shutdown)
		ft_print_message(&philo, "died");
	pthread_join(thr_monitor, NULL);
	exit(0);
}

int ft_wait_children(t_common *common)
{
	int	died;
	int	status;
	int	end_children;
	pid_t	pid_children;

	died = 0;
	end_children = 0;
	while (end_children < common->number_of_philosophers)
	{
		pid_children = waitpid(-1, &status, 0);
		if (pid_children <= 0)
			break ;
		end_children++;
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				died = 1;
		}
		else
			died = 1;
		if (died)
			break ;
	}
	return (died);
}

void ft_start(t_common *common)
{
	int i;
	pid_t *pids;

	pids = malloc(common->number_of_philosophers * sizeof(pid_t));
	if (!pids)
		return ;
	i = 0;
	while (i < common->number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			free(pids);
			break ;
		}
		if (pids[i] == 0)
			ft_children(common, i);
		i++;
		usleep(1000);
	}
	if (ft_wait_children(common))
		ft_exit_all(pids, common->number_of_philosophers);
	ft_clear_semaphore(common);
	free(pids);
}
