#include "philo.h"

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->death_mutex);

	print_status(philo, "is eating");
	my_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->stop)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		print_status(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
    }
    return (NULL);
}
