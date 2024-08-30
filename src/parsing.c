#include "../philo.h"

static const char	*valid_str(const char *str)
{
	long		len;
	const char	*number;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Number can't be negative");
	if (!(*str >= '0' && *str <= '9'))
		error_exit("Input must be digits");
	number = str;
	while (*str >= '0' && *str <= '9')
	{
		++str;
		++len;
	}
	if (len > 10)
		error_exit("Number is too big");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_str(str);
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		error_exit("Number is too big");
	return (num);
}

void	parse_args(t_program *program, char **argv)
{
	program->philo_num = ft_atol(argv[1]);
	program->time_to_die = ft_atol(argv[2]) * 1000;
	program->time_to_eat = ft_atol(argv[3]) * 1000;
	program->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		program->max_meals = ft_atol(argv[5]);
	else
		program->max_meals = -1;
}

void	validate_args(t_program *program)
{
	if (program->philo_num == 0)
		error_exit("Add at least one philosopher");
	if (program->time_to_die < 60000 || program->time_to_eat < 60000 || \
		program->time_to_sleep < 60000)
		error_exit("Time must be more than 60ms");
	if (program->max_meals == 0)
		error_exit("Add at least one meal");
}
