#include "../philo.h"

static const char	*get_color(int id)
{
	const char	*colors[8];

	colors[0] = "\033[31m";
	colors[1] = "\033[32m";
	colors[2] = "\033[33m";
	colors[3] = "\033[34m";
	colors[4] = "\033[35m";
	colors[5] = "\033[36m";
	colors[6] = "\033[37m";
	colors[7] = "\033[90m";
	return (colors[(id - 1) % 8]);
}

void	print_message(t_philo *philo, char status)
{
	long		now;
	const char	*reset;
	const char	*color;

	reset = "\033[0m";
	color = get_color(philo->id);
	now = get_time('m') - philo->program->start_time;
	pthread_mutex_lock(&philo->program->print_mutex);
	if ((status == '1' || status == '2') && \
		!get_bool(&philo->program->program_mutex, &philo->program->end))
		printf("%-6ld %s%d has taken a fork%s\n", now, color, philo->id, reset);
	else if (status == 'e' && \
		!get_bool(&philo->program->program_mutex, &philo->program->end))
		printf("%-6ld \033[1m%s%d is eating%s\n", now, color, philo->id, reset);
	else if (status == 's' && \
		!get_bool(&philo->program->program_mutex, &philo->program->end))
		printf("%-6ld %s%d is sleeping%s\n", now, color, philo->id, reset);
	else if (status == 't' && \
		!get_bool(&philo->program->program_mutex, &philo->program->end))
		printf("%-6ld %s%d is thinking%s\n", now, color, philo->id, reset);
	pthread_mutex_unlock(&philo->program->print_mutex);
}
