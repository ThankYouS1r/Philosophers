#include "includes/philo.h"

t_philo	**init_philosophers(t_main *main, const unsigned int count)
{
	t_philo			**ret;
	t_philo			*philo;
	int	i;

	ret = malloc(sizeof(t_philo *) * count);
	if (!ret)
		return (NULL);
	i = -1;
	while ((unsigned int)++i < count)
	{
		philo = create_philosopher(main, i);
		if (!philo)
		{
			free_philosophers(ret, i);
			return (NULL);
		}
		ret[i] = philo;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		return (!ft_crash("arguments count is have to be equal 4 or 5"));
	main = init_main(argv);
	if (!main)
		return (ft_crash("Can't create structure"));
	if (!start_philosophers(main))
	{
		free_all(main);
		return (ft_crash("Error: Philosophers does not start"));
	}
	wait_for_philosophers_end(main);
	free_all(main);
	return (EXIT_SUCCESS);
}
