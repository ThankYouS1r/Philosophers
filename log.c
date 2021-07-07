#include "includes/philo.h"

static const char	*state_info(const t_state state)
{
	if (state == THINKING)
		return ("is thinking");
	if (state == EATING)
		return ("is eating");
	if (state == SLEEPING)
		return ("is sleeping");
	if (state == DIED)
		return ("died");
	if (state == FORKED)
		return ("has taken a fork");
	return (NULL);
}

void	log_event(const t_philo *philo, const int should_unlock)
{
	pthread_mutex_lock(philo->write_state);
	if (philo->state == ENDED)
		return ;
	printf("%lu %u %s", get_current_time(), philo->id,
		   state_info(philo->state));
	if (philo->state == EATING)
		printf(" [%d]", philo->eat_times + 1);
	printf("\n");
	if (should_unlock)
		pthread_mutex_unlock(philo->write_state);
}