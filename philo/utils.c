#include "philo.h"

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void my_usleep(long long time_in_ms)
{
	long long start;

	start = get_time_ms();

	while (get_time_ms() - start < time_in_ms)
		usleep(500);
}

void print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->stop)
		printf("%lld %d %s\n", get_time_ms() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
