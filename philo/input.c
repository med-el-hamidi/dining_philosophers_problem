#include "philo.h"

/*is an ASCI digit*/
static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	_is_unsignd_digit(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		return (0);
	else if (*str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*ASCI to integer (numeric string into int)*/
int	custom_atoi(const char *str)
{
	unsigned long long	nbr;
	long				tmp;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		tmp = nbr;
		nbr = (nbr * 10) + (*str++ - '0');
		if (nbr > INT_MAX || (nbr / 10) != tmp)
			return (-1);
	}
	return (nbr);
}

int	parse_input(int ac, char **av)
{
	int	i;
	int	nbr;

	i = 0;
	while (++i < ac)
	{
		if (!_is_unsignd_digit(av[i]))
			return (printf(ERR_INPUT_DIGIT, av[i]), 0);
		nbr = custom_atoi(av[i]);
		if (i == 1 && nbr <= 0)
			return (printf(ERR_INPUT_PHILO), 0);
		else if (i != 1 && nbr == -1)
			return (printf(ERR_INPUT_DIGIT, av[i]), 0);
	}
	return (1);
}
