#include "philo.h"

#include "philo.h"

/* get_time_ms:
*	Gets the current time in miliseconds since the Epoch (1970-01-01 00:00:00).
*	Returns the time value (time_t).
*/
time_t	get_time_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* philo_sleep:
*	Pauses the philosopher thread for a certain amount of time in (ms).
*	Periodically checks to see if the simulation has ended during the sleep
*	time and cuts the sleep process if it has.
*/
void	philo_sleep(t_data *data, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_ms() + sleep_time;
	while (get_time_ms() < wake_up)
	{
		if (has_simulation_stopped(data))
			break ;
		usleep(100);
	}
}

/* start_delay:
*	Waits for a small delay at the beginning of each threads execution
*	so that all threads start at the same time with the same start time
*	reference. This ensures the grim reaper thread is synchronized with
*	the philosopher threads.
*/
void	start_delay(time_t start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

/* print_status:
*	Prints the status of a philosopher as long as the simulation is
*	still active. Locks the print mutex to avoid intertwined messages
*	from different threads.
*/
void print_status(t_philo *philo, char *status, int monitored)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!monitored && has_simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d %s ---->%d\n", (get_time_ms() - philo->data->start_time), philo->id + 1, status, philo->meals_eaten);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
