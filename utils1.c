#include "includes/philo.h"

int	ft_crash(const char *str)
{
	write(2, "\033[31m", 5);
	write(2, str, ft_strlen(str));
	write(2, "\033[0m\n", 5);
	return (1);
}

int	ft_free(void *data)
{
	free(data);
	return (1);
}

long int	get_current_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	change_state(t_philo *philo, const t_state state, const int should_unlock)
{
	if (!philo || philo->state == DIED || philo->state == ENDED)
		return (-1);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = state;
	if (state == EATING)
		philo->last_eat_time = get_current_time();
	if (state != ENDED)
		log_event(philo, should_unlock);
	pthread_mutex_unlock(&philo->state_mutex);
	return (1);
}

int	check_death(const t_philo *philo, const t_main *main)
{
	return (get_current_time() - philo->last_eat_time > main->time_to_die);
}