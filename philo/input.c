#include "philo.h"

static int	_parse(char *str, char *arg, int *len)
{
	int	flag;

	flag = 0;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		arg[(*len)++] = *str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		if (!flag && *str != '0')
			flag = 1;
		if (flag)
		{
			arg[(*len)++] = *str;
			if ((*len) > 11)
				break ;
		}
		str++;
	}
	if (!flag && *(str - 1) == '0')
		arg[(*len)] = '0';
	return (*len);
}

static int	_is_strict_positive_int(char *arg, int len)
{
	int	ans;

	if (len <= 2 && (arg[0] == '0' || arg[1] == '0'))
		ans = 0;
	else if (len == 1 && (arg[0] == '+'))
		ans = 0;
	else if (len > 11)
		ans = 0;
	else if (len == 11 && (ft_isdigit(arg[0])
			|| (arg[0] == '+' && ft_strncmp(arg, "+2147483647", len) > 0)))
		ans = 0;
	else if (len == 10 && ft_strncmp(arg, "2147483647", len) > 0)
		ans = 0;
	else
		ans = 1;
	return (ans);
}

static void	_handle_input(char *nbr)
{
	int		len;
	char	arg[12];

	memset(arg, 0, sizeof(arg));
	len = 0;
	len = _parse(nbr, arg, &len);
	if (len == -1 || !_is_strict_positive_int(arg, len))
		exit_failure(ESC_RED ERR_INT ESC_RESET "\n" \
			ESC_BLUE INFO_USAGE ESC_RESET "\n" INF_NBR_PHILOS \
			"\n" INF_TIME_TODIE "\n" INF_TIME_TOEAT "\n" INF_TIME_TOSLEEP \
			"\n" INF_NBR_TOEAT);
}

void	parse_input(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
		_handle_input(av[i]);
}
