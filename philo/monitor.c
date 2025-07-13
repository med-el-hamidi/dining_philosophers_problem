#include "philo.h"

void *monitor_routine(void *arg)
{
	t_data	*data;
	int		full_philos;
	int		*philos_done;
	int		i;

	data = (t_data *)arg;
	philos_done = malloc(data->num_philos * sizeof(int)); // 0 = not done
	while (1)
	{
		full_philos = 0;
		for (i = 0; i < data->num_philos; i++)
		{
			pthread_mutex_lock(&data->death_mutex);
			long long now = get_time_ms();

			if ((now - data->philos[i].last_meal) > data->time_to_die)
			{
				data->stop = 1;
				pthread_mutex_lock(&data->print_mutex);
				printf("%lld %d died\n", now - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->death_mutex);
				free(philos_done);
				return NULL;
			}

			if (data->meals_required > 0 &&
				data->philos[i].meals_eaten >= data->meals_required &&
				!philos_done[i])
			{
				philos_done[i] = 1;
			}
			pthread_mutex_unlock(&data->death_mutex);
		}

		for (i = 0; i < data->num_philos; i++)
			full_philos += philos_done[i];

		if (full_philos == data->num_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_mutex);
			free(philos_done);
			return (NULL);
		}

		usleep(500);
	}
	return (NULL);
}
