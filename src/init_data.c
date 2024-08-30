#include "../philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->program);
	set_last_meal(&philo->philo_mutex, &philo->last_meal, get_time('m'));
	print_message(philo, '1');
	while (!get_bool(&philo->program->program_mutex, \
		&philo->program->end))
		usleep(200);
	return (NULL);
}

static void	distribute_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_num;

	philo_num = philo->program->philo_num;
	philo->first_fork = &forks[(philo_pos + 1) % philo_num];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_num];
	}
}

static void	create_philos(t_program *program)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < program->philo_num)
	{
		philo = program->philosophers + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->program = program;
		distribute_forks(philo, program->forks, i);
		pthread_mutex_init(&philo->philo_mutex, NULL);
		i++;
	}
}

void	init_data(t_program *program)
{
	int	i;

	i = 0;
	program->end = false;
	program->threads_ready = false;
	program->philosophers = malloc(sizeof(t_philo) * program->philo_num);
	if (!program->philosophers)
		error_exit("Malloc problem creating philosophers.");
	pthread_mutex_init(&program->program_mutex, NULL);
	pthread_mutex_init(&program->print_mutex, NULL);
	program->forks = malloc(sizeof(t_fork) * program->philo_num);
	if (!program->forks)
		error_exit("Malloc problem creating forks.");
	while (i < program->philo_num)
	{
		pthread_mutex_init(&program->forks[i].fork_mutex, NULL);
		program->forks[i].fork_id = i;
		i++;
	}
	create_philos(program); 
}
