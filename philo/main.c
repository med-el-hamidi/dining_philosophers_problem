#include "philo.h"

int	main(int ac, char *av[])
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (ac != 5 && ac != 6)
		exit_failure(ESC_RED ERR_USAGE ESC_RESET USAGE_MSG \
			"\n" ESC_BLUE INFO_USAGE ESC_RESET "\n" INF_NBR_PHILOS \
			"\n" INF_TIME_TODIE "\n" INF_TIME_TOEAT "\n" INF_TIME_TOSLEEP \
			"\n" INF_NBR_TOEAT);

	/* Parsing the input*/
	parse_input(ac, av);

	data.start_time = get_time_ms();

	if (init_all(&data, ac, av))
		exit_failure(ESC_RED ERR_INIT ESC_RESET);

	if (data.num_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		my_usleep(data.time_to_die);
		printf("%d 1 died\n", data.time_to_die);
		destroy_and_free(&data);
		return 0;
	}

	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
		i++;
	}

	pthread_create(&monitor, NULL, monitor_routine, &data);

	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);

	// Cleanup
	destroy_and_free(&data);
	return (0);
}
