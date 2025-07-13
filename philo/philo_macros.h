#ifndef PHILO_MACROS_H
# define PHILO_MACROS_H

/*
Color	Code
Black	30
Red	31
Green	32
Yellow	33
Blue	34
Magenta	35
Cyan	36
White	37
*/
/* ANSI Escape codes*/
# define ESC_RED "\033[1;31m"
# define ESC_BLUE "\033[1;34m"
# define ESC_RESET "\033[0m"

/* USAGE related messages*/
# define ERR_USAGE "USAGE_ERROR: "
# define USAGE_MSG "./philo number_of_philosophers\
 time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]"

# define INFO_USAGE "USAGE_INFO: "
# define INF_NBR_PHILOS "number_of_philosophers -ge 1"
# define INF_TIME_TODIE "time_to_die (in milliseconds) -ge 60 ms"
# define INF_TIME_TOEAT "time_to_eat (in milliseconds) -ge 60 ms"
# define INF_TIME_TOSLEEP "time_to_sleep (in milliseconds) -ge 60 ms"
# define INF_NBR_TOEAT "number_of_times_each_philosopher_must_eat\
 (optional argument -ge 1 if specified)"

/* Input Type related message*/
# define ERR_INT "NOT_INT: Arguments must be integers & strictely positive!"

/* INIT related message*/
# define ERR_INIT "INIT_ERROR: Error occurs while initiating resources!"

#endif
