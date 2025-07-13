#include "philo.h"

/*Length of a string*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

/*Why using another function to print strings ?
** 1 - For Errors (printing in stderr)
** 2 - printf is the only printing function allowed in this project which prints in stdout
** ft_putstr_fd is used to print in stderr (fd -eq 2)*/
void	ft_putstr_fd(char *str, int fd)
{
	if (fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
}

/*is an ASCI digit*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*compare s1 with s2 at size n*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*ASCI to integer (numeric string into int)*/
int	ft_atoi(const char *str)
{
	long	nbr;
	long	tmp;
	int		sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = nbr;
		nbr = (nbr * 10) + (*str++ - '0');
		if ((nbr / 10) != tmp && sign == 1)
			return (-1);
		else if ((nbr / 10) != tmp && sign == -1)
			return (0);
	}
	return (nbr * sign);
}

