#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define ERR_USAGE "usage: ./philo <number_of_philosophers>\
 <time_to_die> <time_to_eat> <time_to_sleep>\
 [number_of_times_each_philosopher_must_eat]"
# define ERR_INPUT_DIGIT "invalid input: %s: \
Not a valid unsigned integer!\n"
# define ERR_INPUT_PHILO	"invalid input: \
there must be at least 1 philosopher!\n"
# define ERR_MALLOC	"error: Could not allocate memory!\n"
# define ERR_THREAD	"error: Could not create a thread!\n"
# define ERR_MUTEX	"error: Could not create a mutex!\n"

typedef struct s_data t_data;

typedef struct s_philo
{
    int				id;
    int				meals_eaten;
    time_t			last_meal;
    pthread_t		thread;
	pthread_mutex_t	meal_time_mutex;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		monitor;
	t_philo			*philos;
}	t_data;

// error.c
//void		error_msg(char *msg, char *msg_arg);

//free.c
void		destroy_mutexes(t_data *data);
void		free_data(t_data *data);

// input_utils.c
void		ft_putstr_fd(char *str, int fd);

// input.c
int			custom_atoi(const char *str);
int			parse_input(int ac, char **av);

// utils.c
time_t		get_time_ms(void);
void		philo_sleep(t_data *data, time_t sleep_time);
void		start_delay(time_t start_time);
void		print_status(t_philo *philo, char *status, int momitored);

// init.c
int			init_all(t_data *data, int argc, char **argv);

// philo.c
void		*philo_routine(void *arg);

// monitor.c
int			has_simulation_stopped(t_data *data);
void		*monitor_routine(void *arg);

#endif
