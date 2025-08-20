#include "philo.h"

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", 0);
	print_status(philo, "is eating", 0);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	philo_sleep(philo->data, philo->data->time_to_eat);
	if (!has_simulation_stopped(philo->data))
	{
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_time_mutex);
	}
	print_status(philo, "is sleeping", 0);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo_sleep(philo->data, philo->data->time_to_sleep);
}

/* think_routine:
*	Once a philosopher is done sleeping, he will think for a certain
*	amount of time before starting to eat again.
*	The time_to_think is calculated depending on how long it has been
*	since the philosopher's last meal, the time_to_eat and the time_to_die
*	to determine when the philosopher will be hungry again.
*	This helps stagger philosopher's eating routines to avoid forks being
*	needlessly monopolized by one philosopher to the detriment of others.
*/
static void	think_routine(t_philo *philo, int print)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_mutex);
	time_to_think = (philo->data->time_to_die
			- (get_time_ms() - philo->last_meal)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && !print)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (print)
		print_status(philo, "is thinking", 0);
	philo_sleep(philo->data, time_to_think);
}

/* lone_philo_routine:
*	This routine is invoked only when there is a single philosopher.
*	A single philosopher has only one fork, so cannot eat. The
*	philosopher will pick up that fork, wait as long as time_to_die then die.
*/
static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	philo_sleep(philo->data, philo->data->time_to_die);
	print_status(philo, "died", 0);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!philo || !philo->data->meals_required || !philo->data->time_to_die)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	start_delay(philo->data->start_time);
	if (philo->data->num_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, 0);
	while (!has_simulation_stopped(philo->data))
	{
		eat_sleep_routine(philo);
		think_routine(philo, 1);
	}
    return (NULL);
}
