#include "philo.h"

static void	cleanup_error_case(t_data *data, int i);
static int	start(t_data *data);
static void	stop(t_data *data);

/* main:
 *  Entry point of the philosopher simulation.
 *   - Expects 4 or 5 arguments:
 *       1) number_of_philosophers
 *       2) time_to_die
 *       3) time_to_eat
 *       4) time_to_sleep
 *       5) [optional] meals_required
 *
 *  Steps:
 *   1. Validate argument count
 *   2. Parse and validate input values
 *   3. Initialize data structures and mutexes
 *   4. Start the simulation
 *   5. Stop simulation and clean up resources
 *
 *  Returns EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_print_error(ERR_USAGE), EXIT_FAILURE);
	if (!parse_input(ac, av))
		return (EXIT_FAILURE);
	if (!init_all(&data, ac, av))
		return (EXIT_FAILURE);
	if (!start(&data))
		return (destroy_mutexes(&data), free_data(&data), EXIT_FAILURE);
	stop(&data);
	return (EXIT_SUCCESS);
}

/* cleanup_error_case:
*	Stop the simulation of the threads which successfuly created
*	then join them $ cleanup program's resources allocated
*/
static void	cleanup_error_case(t_data *data, int i)
{
	if (!data)
		return ;
	set_stop_flag(data, 1);
	while (i--)
		pthread_join(data->philos[i].thread, NULL);
	destroy_mutexes(data);
	free_data(data);
}

/* start:
*	Start the simulation by creating one thread for each philosopher
*	as well as a thread for the monitor.
*	Returns 1 if the simulation was successfully started, 0 if error.
*/
static int	start(t_data *data)
{
	int	i;

	if (!data || !data->philos)
		return (0);
	data->start_time = get_time_ms() + (data->num_philos * 20);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
		{
			cleanup_error_case(data, i);
			return (ft_print_error(ERR_THREAD), 0);
		}
		i++;
	}
	if (data->num_philos > 1)
	{
		if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
		{
			cleanup_error_case(data, i);
			return (ft_print_error(ERR_THREAD), 0);
		}
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

	if (!data || !data->philos)
		return ;
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
