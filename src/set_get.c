#include "../philo.h"

void	set_last_meal(pthread_mutex_t *mutex, long *val, long value)
{
	pthread_mutex_lock(mutex);
	*val = value;
	pthread_mutex_unlock(mutex);
}

long	get_last_meal(pthread_mutex_t *mutex, long *value)
{
	long	val;

	pthread_mutex_lock(mutex);
	val = *value;
	pthread_mutex_unlock(mutex);
	return (val);
}

void	set_bool(pthread_mutex_t *mutex, bool *val, bool value)
{
	pthread_mutex_lock(mutex);
	*val = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	val;

	pthread_mutex_lock(mutex);
	val = *value;
	pthread_mutex_unlock(mutex);
	return (val);
}

void	increment_thread_count(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
