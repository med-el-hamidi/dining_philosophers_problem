#include "philo.h"

/* set_stop_flag:
*	Sets the simulation stop flag to 1 or 0. Only the monitor
*	thread can set this flag. If the simulation stop flag is
*	set to 1, that means the simulation has met an end condition.
*/
static void	set_stop_flag(t_data *data, int state)
{
	pthread_mutex_lock(&data->death_mutex);
		data->stop = state;
	pthread_mutex_unlock(&data->death_mutex);
}

/* has_simulation_stopped:
*	Checks if the simulation is at an end. The stop flag
*	is protected by a mutex lock to allow any thread to check
*	the simulation status without data race.
*	Returns 1 if the simulation stop flag is set to 1,
*	false if the flag is set to 0.
*/
int	has_simulation_stopped(t_data *data)
{
	int	r;

	r = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->stop)
		r = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (r);
}

/* is_philo_died:
*	Checks if the philosopher must be die by comparing the
*	time since the philosopher's last meal and the time_to_die parameter.
*	If it is time for the philosopher to die, sets the simulation stop
*	flag and displays the death status.
*	Returns 1 if the philosopher has been killed, 0 if not.
*/
static int	is_philo_died(t_philo *philo)
{
	if ((get_time_ms() - philo->last_meal) >= philo->data->time_to_die)
	{
		set_stop_flag(philo->data, 1);
		print_status(philo, "died", 1);
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (1);
	}
	return (0);
}

/* philos_died_or_ate_enough:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be die, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/
static int	philos_died_or_ate_enough(t_data *data)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_time_mutex);
		if (is_philo_died(&data->philos[i]))
			return (1);
		if (data->meals_required != -1)
			if (data->philos[i].meals_eaten < data->meals_required)
				r = 0;
		pthread_mutex_unlock(&data->philos[i].meal_time_mutex);
		i++;
	}
	if (data->meals_required != -1 && r)
	{
		set_stop_flag(data, 1);
		return (1);
	}
	return (0);
}

/* monitor_routine:
*	The monitor thread's routine. Checks if a philosopher must
*	be die and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->meals_required == 0)
		return (NULL);
	set_stop_flag(data, 0);
	start_delay(data->start_time);
	while (1)
	{
		if (philos_died_or_ate_enough(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
