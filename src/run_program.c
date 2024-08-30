#include "../philo.h"

static bool	is_dead(t_philo *philo)
{
	long	time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	time = get_time('m') - \
		get_last_meal(&philo->philo_mutex, &philo->last_meal);
	if (time > philo->program->time_to_die / 1000)
	{
		printf("%-6ld %d died\n", time, philo->id);
		set_bool(&philo->philo_mutex, &philo->is_dead, true);
		return (true);
	}
	return (false);
}

static void	*monitor_deaths(void *data)
{
	t_program	*program;
	bool		all_full;
	int			i;

	usleep(100);
	program = (t_program *)data;
	while (!get_bool(&program->program_mutex, &program->end))
	{
		all_full = true;
		i = 0;
		while (i < program->philo_num)
		{
			if (is_dead(program->philosophers + i))
				return (set_bool(&program->program_mutex, \
					&program->end, true), NULL);
			if (!get_bool(&program->philosophers[i].philo_mutex, 
					&program->philosophers[i].full))
				all_full = false;
			i++;
		}
		if (all_full)
			set_bool(&program->program_mutex, &program->end, true);
	}
	return (NULL);
}

static void	philosopher_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		sleeping(30000, philo->program);
	while (!get_bool(&philo->program->program_mutex, &philo->program->end) \
		&& !get_bool(&philo->philo_mutex, &philo->is_dead))
	{
		eating(philo);
		print_message(philo, 's');
		sleeping(philo->program->time_to_sleep, philo->program);
		thinking(philo);
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
	}
}

static void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->program);
	set_last_meal(&philo->philo_mutex, &philo->last_meal, get_time('m'));
	philosopher_routine(philo);
	return (NULL);
}

void	run_program(t_program *program)
{
	int	i;

	i = -1;
	if (program->philo_num == 1)
		pthread_create(&program->philosophers[0].philo_id, NULL, \
			single_philo, &program->philosophers[0]);
	else
	{
		while (++i < program->philo_num)
			pthread_create(&program->philosophers[i].philo_id, NULL, \
				start_simulation, &program->philosophers[i]);
	}
	pthread_create(&program->is_dead, NULL, monitor_deaths, program);
	program->start_time = get_time('m');
	set_bool(&program->program_mutex, &program->threads_ready, true);
	i = -1;
	while (++i < program->philo_num)
		pthread_join(program->philosophers[i].philo_id, NULL);
	set_bool(&program->program_mutex, &program->end, true);
	pthread_join(program->is_dead, NULL);
}
