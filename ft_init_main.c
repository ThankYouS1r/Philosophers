#include "includes/philo.h"

int	check_values(t_main *main)
{
	int		errors;

	errors = 0;
	if (main->philo_count == ATOI_ERROR || main->philo_count < 1)
		errors += ft_crash("number of philosophers error!");
	if (main->time_to_sleep == ATOI_ERROR)
		errors += ft_crash("time to sleep error!");
	if (main->time_to_eat == ATOI_ERROR)
		errors += ft_crash("time to eat error!");
	if (main->time_to_die == ATOI_ERROR)
		errors += ft_crash("time to die error!");
	if (main->eat_times == ATOI_ERROR)
	{
		ft_crash("eat times error!");
		main->eat_times = -1;
	}
	if (main->write_state == NULL)
	{
		errors = 1;
		ft_crash("write state creation error!");
	}
	return (errors);
}

void	*create_write_state(void)
{
	pthread_mutex_t	*state;

	state = malloc(sizeof(pthread_mutex_t));
	if (!state)
		return (NULL);
	if (pthread_mutex_init(state, NULL))
		return (NULL);
	return (state);
}

t_main	*init_main(char *argv[])
{
	t_main	*main;

	main = ft_malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	main->eat_times = -1;
	main->philo_count = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		main->eat_times = ft_atoi(argv[5]);
	main->write_state = create_write_state();
	if (check_values(main) && free_all(main))
		return (NULL);
	main->forks = init_forks(main->philo_count);
	if (main->forks)
		main->philosophers = init_philosophers(main, main->philo_count);
	if (!main->philosophers || !main->forks)
	{
		free_all(main);
		return (NULL);
	}
	return (main);
}