#include "philo.h"

/* destroy_mutexes:
*	Destroy mutexes.
*/
void	destroy_mutexes(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

/* free_data:
*	Frees all the memory allocated.
*/
void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->forks);
	free(data->philos);
}
