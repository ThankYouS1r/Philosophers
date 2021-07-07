#include "includes/philo.h"

static void	eating(t_philo *philo, const t_main *main)
{
	pthread_mutex_lock(philo->forks->left_fork);
	change_state(philo, FORKED, 1);
	pthread_mutex_lock(philo->forks->right_fork);
	change_state(philo, FORKED, 1);
	change_state(philo, EATING, 1);
	usleep(main->time_to_eat * 1000);
	++philo->eat_times;
	pthread_mutex_unlock(philo->forks->right_fork);
	pthread_mutex_unlock(philo->forks->left_fork);
	if (main->eat_times != -1 && philo->eat_times >= main->eat_times)
		change_state(philo, ENDED, 1);
}

static void	*killing_routine(void *arg)
{
	t_philo		*philo;
	t_main		*main;
	long int	time_to_death;

	philo = arg;
	main = philo->main;
	while (1)
	{
		time_to_death = philo->last_eat_time + main->time_to_die
						- get_current_time();
		if (time_to_death > 0)
			usleep(time_to_death);
		if (time_to_death < 0 || check_death(philo, main))
		{
			change_state(philo, DIED, 0);
			time_to_death = -1;
			while (++time_to_death < main->philo_count)
				main->philosophers[time_to_death]->state = ENDED;
			pthread_mutex_unlock(philo->write_state);
			return (NULL);
		}
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_main		*main;
	pthread_t	killer;

	philo = arg;
	main = philo->main;
	philo->last_eat_time = get_current_time();
	pthread_create(&killer, NULL, killing_routine, arg);
	pthread_detach(killer);
	while (philo->state != DIED && philo->state != ENDED)
	{
		eating(philo, main);
		change_state(philo, SLEEPING, 1);
		usleep(main->time_to_sleep * 1000);
		change_state(philo, THINKING, 1);
	}
	return (NULL);
}

int	init_philosopher(t_philo *philo, t_main *main, unsigned int id)
{
	t_fork	*forks;

	forks = malloc(sizeof(t_fork));
	if (!forks)
		return (0);
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread && ft_free(forks))
		return (0);
	philo->id = id + 1;
	philo->forks = forks;
	philo->forks->left_fork = (pthread_mutex_t *)main->forks + id;
	if (++id == main->philo_count)
		id = 0;
	philo->forks->right_fork = (pthread_mutex_t *)main->forks + id;
	philo->eat_times = 0;
	philo->state = THINKING;
	philo->write_state = main->write_state;
	if (pthread_mutex_init(&philo->state_mutex, NULL) && ft_free(forks))
		return (0);
	return (1);
}

t_philo	*create_philosopher(t_main *main, const unsigned int id)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	if (!init_philosopher(ret, main, id))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}