#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc != 5 && argc != 6)
		error_exit("Invalid arguments\nTry ./philo 5 800 200 200 (max_meals)");
	parse_args(&program, argv);
	validate_args(&program);
	init_data(&program);
	run_program(&program);
	destroy_program(&program);
	return (0);
}
