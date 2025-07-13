#ifndef PHILO_H
# define PHILO_H
# include "philo_macros.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo {
    int				id;
    int				meals_eaten;
    long long		last_meal;
    pthread_t		thread;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    t_data			*data;
}	t_philo;

typedef struct s_data {
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

// error.c
void	exit_failure(char *msg);

// input_utils.c
void		ft_putstr_fd(char *str, int fd);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// input.c
void		parse_input(int ac, char **av);

// utils.c
long long	get_time_ms(void);
void		my_usleep(long long time_in_ms);
void		print_status(t_philo *philo, char *status);

// init.c
int			init_all(t_data *data, int argc, char **argv);

// philo.c
void		*philo_routine(void *arg);

// monitor.c
void		*monitor_routine(void *arg);

// Cleanup
void		destroy_and_free(t_data *data);
#endif
