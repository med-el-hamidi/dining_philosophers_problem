#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (ft_print_error(ERR_MALLOC), 0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&data->forks[i]);
			return (ft_print_error(ERR_MUTEX), 0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		while (i--)
			pthread_mutex_destroy(&data->forks[i]);
		return (ft_print_error(ERR_MUTEX), 0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		while (i--)
			pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->print_mutex);
		return (ft_print_error(ERR_MUTEX), 0);
	}
	return (1);
}

static int	init_philos(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (ft_print_error(ERR_MALLOC), 0);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (data->philos[i].id % 2)
		{
			data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
			data->philos[i].right_fork = &data->forks[i];
		}
		else
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		}
		if (pthread_mutex_init(&data->philos[i].meal_time_mutex, NULL) != 0)
			return (free(data->philos), ft_print_error(ERR_MUTEX), 0);
		i++;
	}
	return (1);
}

int	init_all(t_data *data, int ac, char **av)
{
	if (!data)
		return (0);
	data->num_philos = custom_atoi(av[1]);
	data->time_to_die = custom_atoi(av[2]);
	data->time_to_eat = custom_atoi(av[3]);
	data->time_to_sleep = custom_atoi(av[4]);
	if (ac == 6)
		data->meals_required = custom_atoi(av[5]);
	else
		data->meals_required = -1;
	data->stop = 0;
	if (!init_mutexes(data))
		return (0);
	if (!init_philos(data))
		return (destroy_mutexes(data), 0);
	return (1);
}
