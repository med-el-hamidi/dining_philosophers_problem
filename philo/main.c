#include "philo.h"

/* start:
*	Start the simulation by creating one thread for each philosopher
*	as well as a thread for the monitor.
*	Returns 1 if the simulation was successfully started, 0 if error.
*/
static int	start(t_data *data)
{
	int	i;

	data->start_time = get_time_ms() + (data->num_philos * 20);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (printf(ERR_THREAD), 0);
		i++;
	}
	if (data->num_philos > 1)
	{
		if (pthread_create(&data->monitor, NULL,
				&monitor_routine, data) != 0)
			return (printf(ERR_THREAD), 0);
	}
	return (1);
}

/* stop:
*	Waits for all threads to be joined then destroy mutexes and free
*	allocated memory.
*/
static void	stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	if (data->num_philos > 1)
		pthread_join(data->monitor, NULL);
	destroy_mutexes(data);
	free_data(data);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf(ERR_USAGE), EXIT_FAILURE);
	if (!parse_input(ac, av))
		return (EXIT_FAILURE);
	if (!init_all(&data, ac, av))
		return (EXIT_FAILURE);
	if (!start(&data))
		return (destroy_mutexes(&data), free_data(&data), EXIT_FAILURE);
	stop(&data);
	return (EXIT_SUCCESS);
}
