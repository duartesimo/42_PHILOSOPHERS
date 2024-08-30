#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_program	t_program;

typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork_mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	bool			is_dead;
	long			meals;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_program		*program;
	pthread_t		philo_id;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef struct s_program
{
	long			philo_num;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			max_meals;
	long			start_time;
	bool			threads_ready;
	bool			end;
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_t		is_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	program_mutex;
}			t_program;

/* Program */
void	parse_args(t_program *program, char **argv);
void	validate_args(t_program *program);
void	init_data(t_program *program);
void	run_program(t_program *program);
void	destroy_program(t_program *program);
void	print_message(t_philo *philo, char status);
void	error_exit(char *error);
void	*single_philo(void *arg);
void	wait_all_threads(t_program *program);

/* Set Get */
void	set_last_meal(pthread_mutex_t *mutex, long *val, long value);
long	get_last_meal(pthread_mutex_t *mutex, long *value);
void	set_bool(pthread_mutex_t *mutex, bool *val, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	increment_thread_count(pthread_mutex_t *mutex, long *value);

/* Actions */
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(long sleep_time, t_program *program);
long	get_time(char c);

#endif
