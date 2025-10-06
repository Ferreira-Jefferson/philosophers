#include "philosophers_bonus.h"

void ft_clear_semaphore(t_common *common)
{
	sem_close(common->sem_forks);
	sem_unlink(SEM_FORKS);
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
}

int	ft_should_shutdown(t_philo *philo)
{
	int		fed;
	int		should_shutdown;
	long	times_eaten;
	long	time_to_die;

	time_to_die = philo->common->time_to_die;
	should_shutdown = ft_get_time_ms() > philo->last_meal + time_to_die;
	fed = 0;
	if (philo->common->number_of_times_must_eat != -1)
	{
		should_shutdown = 0;
		times_eaten = philo->number_time_eat;
		fed = times_eaten >= philo->common->number_of_times_must_eat;
	}
	philo->common->shutdown = should_shutdown;
	return (should_shutdown || fed);
}

void	ft_eating(t_philo *philo)
{
	sem_wait(philo->common->sem_forks);
	ft_print_message(*philo, "has taken a fork");
	if (philo->common->number_of_philosophers > 1)
	{
		sem_wait(philo->common->sem_forks);
		ft_print_message(*philo, "has taken a fork");
	}
	philo->last_meal = ft_get_time_ms();
	philo->number_time_eat++;
	ft_print_message(*philo, "is eating");
	usleep(philo->common->time_to_eat * 1000);
	if (philo->common->number_of_philosophers > 1)
		sem_post(philo->common->sem_forks);
	sem_post(philo->common->sem_forks);	
}

void ft_children(t_common *common, int id)
{
	t_philo philo;

	philo = (t_philo) {id, ft_get_time_ms(), 0, common};
	while (!ft_should_shutdown(&philo))
	{
		ft_eating(&philo);
		if (!ft_should_shutdown(&philo))
		{
			ft_print_message(philo, "is sleeping");
			usleep(philo.common->time_to_sleep * 1000);
		}
		if (!ft_should_shutdown(&philo))
			ft_print_message(philo, "is thinking");
	}
	if (philo.common->shutdown)
		ft_print_message(philo, "died");
	exit(0);
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
	wait(NULL);
	ft_exit_all(pids, i);
	free(pids);
	ft_clear_semaphore(common);
}
