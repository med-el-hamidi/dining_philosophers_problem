#include "philo.h"

static void	eat_sleep_routine(t_philo *philo);
static void	think_routine(t_philo *philo);
static void	*lone_philo_routine(t_philo *philo);

/* philo_routine:
 *  Main routine for each philosopher thread.
 *  - Initializes last_meal time.
 *  - Handles special case if only one philosopher exists.
 *  - Otherwise loops: eat → sleep → think, until simulation stops.
 */
void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!philo || !philo->data || !philo->data->meals_required || !philo->data->time_to_die)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	start_delay(philo->data->start_time);
	if (philo->data->num_philos == 1)
		return (lone_philo_routine(philo));
	while (!has_simulation_stopped(philo->data))
	{
		eat_sleep_routine(philo);
		think_routine(philo);
	}
    return (NULL);
}

/* eat_sleep_routine:
 *  Philosopher picks up both forks, eats, then sleeps.
 *  - Updates last_meal time and meals_eaten count.
 *  - Forks are unlocked after eating.
 */
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
 *  Philosopher thinks for a calculated time before eating again.
 *  - Thinking time depends on last meal, time_to_eat, and time_to_die.
 *  - Helps stagger eating so forks are shared fairly.
 */
static void	think_routine(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_mutex);
	time_to_think = (philo->data->time_to_die
			- (get_time_ms() - philo->last_meal)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	print_status(philo, "is thinking", 0);
	philo_sleep(philo->data, time_to_think);
}

/* lone_philo_routine:
 *  Special case when only one philosopher exists.
 *  - Takes one fork, waits until time_to_die, then dies.
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
