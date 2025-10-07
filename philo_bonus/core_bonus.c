#include "philosophers_bonus.h"

static void	ft_exit_all(pid_t *pids, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
}

static void	ft_eating(t_philo *philo)
{
	sem_wait(philo->common->sem_butler);
	sem_wait(philo->common->sem_forks);
	ft_print_message(philo, "has taken a fork");
	sem_wait(philo->common->sem_forks);
	ft_print_message(philo, "has taken a fork");
	sem_post(philo->common->sem_butler);
	ft_print_message(philo, "is eating");
	sem_wait(philo->data_sem);
	philo->last_meal = ft_get_time_ms();
	philo->number_time_eat++;
	sem_post(philo->data_sem);
	usleep(philo->common->time_to_eat * 1000);
	sem_post(philo->common->sem_forks);
	sem_post(philo->common->sem_forks);
}

static void	*ft_monitor(void *args)
{
	t_philo	*philo;
	int		is_satiated;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->data_sem);
		is_satiated = 0;
		if (philo->common->number_of_times_must_eat != -1)
		{
			if (philo->number_time_eat >= philo->common->number_of_times_must_eat)
				is_satiated = 1;
		}
		else if (ft_get_time_ms() - philo->last_meal > philo->common->time_to_die)
		{
			sem_wait(philo->common->sem_print);
			if (philo->common->number_of_times_must_eat == -1)
			{
				printf("%ld %d died\n", ft_get_time_ms() - philo->common->start_time,
					philo->id_philo + 1);
				exit(1);
			}
			sem_post(philo->common->sem_print);
		}
		sem_post(philo->data_sem);
		if (is_satiated)
			exit(0);
		usleep(1000);
	}
	exit(0);
	return (NULL);
}

static void	ft_children(t_common *common, int id)
{
	t_philo	philo;

	philo = (t_philo){0};
	philo.id_philo = id;
	philo.common = common;
	philo.last_meal = ft_get_time_ms();
	ft_generate_sem_name(SEM_DATA_BASE, id, philo.data_sem_name, 0, 0);
	sem_unlink(philo.data_sem_name);
	philo.data_sem = sem_open(philo.data_sem_name, O_CREAT, 0644, 1);
	pthread_create(&philo.monitor_thread, NULL, &ft_monitor, &philo);
	if (philo.id_philo % 2)
		usleep(philo.common->time_to_eat / 2);
	while (1)
	{
		ft_eating(&philo);
		ft_print_message(&philo, "is sleeping");
		usleep(philo.common->time_to_sleep * 1000);
		ft_print_message(&philo, "is thinking");
	}
}

static void	ft_finish(t_common *common, pid_t *pids)
{
	int		finished_count;
	int		death_occured;
	int		status;

	finished_count = 0;
	death_occured = 0;
	while (finished_count < common->number_of_philosophers)
	{
		if (waitpid(-1, &status, 0) <= 0)
			continue ;
		finished_count++;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			death_occured = 1;
			break ;
		}
	}
	if (death_occured)
		ft_exit_all(pids, common->number_of_philosophers);
	while (wait(NULL) > 0)
		;
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_BUTLER);
}

void	ft_start(t_common *common)
{
	int		i;
	pid_t	*pids;

	pids = malloc(common->number_of_philosophers * sizeof(pid_t));
	if (!pids)
		return ;
	i = 0;
	while (i < common->number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			ft_children(common, i);
		if (pids[i] < 0)
			break ;
		i++;
	}
	ft_finish(common, pids);
	free(pids);
}

