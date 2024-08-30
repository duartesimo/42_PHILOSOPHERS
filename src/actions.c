#include "../philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	print_message(philo, '1');
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	print_message(philo, '2');
	set_last_meal(&philo->philo_mutex, &philo->last_meal, get_time('m'));
	philo->meals++;
	print_message(philo, 'e');
	sleeping(philo->program->time_to_eat, philo->program);
	if (philo->program->max_meals > 0 && \
		philo->meals == philo->program->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
}

void	sleeping(long sleep_time, t_program *program)
{
	long	start;

	start = get_time('u');
	while (get_time('u') - start < sleep_time)
	{
		if (get_bool(&program->program_mutex, &program->end))
			break ;
		usleep(100);
	}
}

void	thinking(t_philo *philo)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	print_message(philo, 't');
	if (philo->program->philo_num % 2 == 0)
		return ;
	time_eat = philo->program->time_to_eat;
	time_sleep = philo->program->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	sleeping(time_think * 0.4, philo->program);
}

long	get_time(char c)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit("Get Time Failed!");
	if (c == 'm')
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (c == 'u')
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		error_exit("Wrong param to gettime");
	return (0);
}
