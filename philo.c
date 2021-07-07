#include "includes/philo.h"

int	start_philosophers(t_main *main)
{
	int	i;
	t_philo			*philo;

	i = -1;
	while (++i < main->philo_count)
	{
		philo = main->philosophers[i];
		philo->main = main;
		if (pthread_create(philo->thread, NULL, philosopher_routine, philo))
			ft_crash("Pthread_create error");
		usleep(100);
	}
	return (1);
}

void	*init_forks(const unsigned int count)
{
	unsigned int	i;
	unsigned int	j;
	pthread_mutex_t			*ret;

	ret = malloc(sizeof(pthread_mutex_t) * count);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(ret + i, NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(ret + j);
			return (NULL);
		}
	}
	return (ret);
}

void	wait_for_philosophers_end(const t_main *main)
{
	int	i;

	i = -1;
	if (main->philosophers)
		while (++i < main->philo_count)
			if (pthread_join(*(pthread_t *)main->philosophers[i]->thread, NULL))
				ft_crash("Pthread join error");
}

void	free_philosophers(t_philo **philosophers, const unsigned int count)
{
	unsigned int	i;
	t_philo					*philo;

	if (!philosophers)
		return ;
	i = -1;
	while (++i < count)
	{
		philo = philosophers[i];
		pthread_mutex_destroy(&philo->state_mutex);
		free(philo->thread);
		free(philo->forks);
		free(philo);
	}
	free(philosophers);
}

int	free_all(t_main *main)
{
	int	i;

	i = -1;
	if (main->forks)
		while (++i < main->philo_count)
			pthread_mutex_destroy((pthread_mutex_t *)main->forks + i);
	free(main->forks);
	free(main->write_state);
	free_philosophers(main->philosophers, main->philo_count);
	free(main);
	return (1);
}