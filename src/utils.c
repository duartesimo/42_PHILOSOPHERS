#include "../philo.h"

void	wait_all_threads(t_program *program)
{
	while (!get_bool(&program->program_mutex, &program->threads_ready))
		;
}

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	destroy_program(t_program *program)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < program->philo_num)
	{
		philo = program->philosophers + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&program->print_mutex);
	pthread_mutex_destroy(&program->program_mutex);
	free(program->forks);
	free(program->philosophers);
}
