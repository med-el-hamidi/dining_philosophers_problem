#include "philo.h"

static int	is_philo_died(t_philo *philo);
static int	philos_died_or_ate_enough(t_data *data);

/* monitor_routine:
 *  Main loop for the monitor thread.
 *  Repeatedly checks if:
 *   - A philosopher has died.
 *   - All philosophers have eaten enough.
 *  Ends simulation if either condition is true.
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

/* set_stop_flag:
 *  Updates the stop flag (0 = running, 1 = stopped).
 *  Only the monitor thread should set this flag.
 */
void	set_stop_flag(t_data *data, int state)
{
	pthread_mutex_lock(&data->death_mutex);
		data->stop = state;
	pthread_mutex_unlock(&data->death_mutex);
}

/* has_simulation_stopped:
 *  Checks if the stop flag is set.
 *  Thread-safe with mutex protection.
 *  Returns 1 if stopped, 0 if running.
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
 *  Checks if the philosopher has exceeded time_to_die
 *  since their last meal.
 *  If so, stop the simulation and print death status.
 *  Returns 1 if dead, 0 otherwise.
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
 *  Loops through philosophers to check:
 *   - If any philosopher died.
 *   - If all philosophers ate required meals.
 *  Stops simulation if either condition is met.
 *  Returns 1 if simulation should end, 0 otherwise.
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
