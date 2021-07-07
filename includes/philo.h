#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define ATOI_ERROR (-2147483647)

typedef struct s_fork	t_fork;
typedef struct s_main	t_main;

typedef enum e_state
{
	THINKING = 0,
	EATING,
	SLEEPING,
	FORKED,
	DIED,
	ENDED
}					t_state;

struct s_fork
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat_times;
	long int		last_eat_time;
	void			*thread;
	t_fork			*forks;
	t_state			state;
	pthread_mutex_t	state_mutex;
	void			*write_state;
	t_main			*main;
}					t_philo;

struct s_main
{
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				eat_times;
	t_philo			**philosophers;
	void			*forks;
	void			*write_state;
};

size_t		ft_strlen(const char *str);
void		ft_bzero(void *s, size_t n);
char					*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
void	*ft_malloc(size_t size);
int	ft_crash(const char *str);
int	ft_free(void *data);
long int	get_current_time(void);
int	change_state(t_philo *philo, const t_state state, const int should_unlock);
int		check_death(const t_philo *philo, const t_main *main);
t_philo	*create_philosopher(t_main *main, const unsigned int id);
void	*philosopher_routine(void *arg);
t_main	*init_main(char *argv[]);
int		check_values(t_main *main);
void	free_philosophers(t_philo **philosophers, const unsigned int count);
void	wait_for_philosophers_end(const t_main *main);
void	*init_forks(const unsigned int count);
int		start_philosophers(t_main *main);
int		init_philosopher(t_philo *philo, t_main *main, unsigned int id);
void	log_event(const t_philo *philo, const int should_unlock);
void	*init_forks(const unsigned int count);
void	*create_write_state(void);
t_philo	**init_philosophers(t_main *main, const unsigned int count);
int	free_all(t_main *main);


#endif