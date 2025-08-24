#include "philo.h"

static int	ft_isdigit(int c);
static int	_is_unsignd_digit(char *str);

/* custom_atoi:
 *  Converts a numeric string to int.
 *   - Skips leading whitespace
 *   - Accepts optional '+'
 *   - Detects overflow and returns -1 if out of INT_MAX range
 *
 *  Returns the integer value, or -1 on overflow.
 */
int	custom_atoi(const char *str)
{
	unsigned long long	nbr;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str++ - '0');
		if (nbr > INT_MAX)
			return (-1);
	}
	return (nbr);
}

/* parse_input:
 *  Validates and parses command-line arguments.
 *   - Ensures all inputs are unsigned integers
 *   - Ensures number of philosophers > 0
 *   - Detects invalid or overflowing values
 *
 *  Returns 1 if input is valid, 0 otherwise.
 */
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
			return (ft_print_error(ERR_INPUT_PHILO), 0);
		else if (i != 1 && nbr == -1)
			return (printf(ERR_INPUT_DIGIT, av[i]), 0);
	}
	return (1);
}

/* ft_isdigit:
 *  Checks if a character is a digit ('0'–'9').
 *  Returns 1 if true, 0 otherwise.
 */
static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* _is_unsignd_digit:
 *  Checks if a string represents a valid unsigned integer.
 *   - Skips whitespace
 *   - Rejects negative sign
 *   - Allows optional '+'
 *   - Ensures all remaining characters are digits
 *
 *  Returns 1 if valid, 0 otherwise.
 */
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
