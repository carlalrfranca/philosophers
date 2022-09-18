/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:44:50 by cleticia          #+#    #+#             */
/*   Updated: 2022/06/16 00:56:24 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_philos(t_principal *input)
{
	int	index;

	index = -1;
	while (++index < input->nb_ph)
	{
		pthread_create(&input->ph[index].thread,
			NULL, &start_routine, &input->ph[index]);
	}
	return (1);
}

static void	init_args_struct(t_principal *input)
{
	int	index;

	index = -1;
	while (++index < input->nb_ph)
	{
		pthread_mutex_init(&input->forks[index], NULL);
		input->ph[index].philo = index + 1;
		input->ph[index].left_fork = index;
		input->ph[index].right_fork = index + 1;
		input->ph[index].ret_principal = input;
		input->ph[index].last_meal = get_time();
		input->ph[index].meal = 0;
		if (index + 1 == input->nb_ph)
			input->ph[index].right_fork = 0;
	}
}

static void	check_args(int argc, t_principal *input)
{
	if (argc == 6 && input->nb_eat < 1)
		ft_exit("Wrong must eat number\n");
	if (input->nb_ph < 0)
		ft_exit("Wrong philosopher number\n");
	if (input->tm_to_die < 0)
		ft_exit("Wrong time to die number\n");
	if (input->tm_to_eat < 0)
		ft_exit("Wrong time to eat number\n");
	if (input->tm_to_sleep < 0)
		ft_exit("Wrong time to sleep number\n");
}

static int	parse_args(int argc, char **argv, t_principal *input)
{
	if (argc != 5 && argc != 6)
		ft_exit("Wrong arguments\n");
	if (verify_digit(argv) == 0)
		return (1);
	input->nb_ph = ft_atoi(argv[1]);
	input->tm_to_die = ft_atoi(argv[2]);
	input->tm_to_eat = ft_atoi(argv[3]);
	input->tm_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->nb_eat = ft_atoi(argv[5]);
	else
		input->nb_eat = 0;
	input->checker = 0;
	input->full_philos = 0;
	input->ph = malloc(sizeof(t_ph) * input->nb_ph);
	input->forks = malloc(sizeof(pthread_mutex_t) * input->nb_ph);
	if (pthread_mutex_init(&input->all_ate_checker, NULL))
		return (1);
	if (pthread_mutex_init(&input->meal_check, NULL))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_principal	input;
	int			index;

	index = -1;
	if (parse_args(argc, argv, &input) == 1)
		ft_exit("Error arguments. Try again.\n");
	check_args(argc, &input);
	pthread_mutex_init(&input.print, NULL);
	init_args_struct(&input);
	input.start_meal = get_time();
	create_philos(&input);
	management_threads(&input);
	while (++index < input.nb_ph)
		pthread_mutex_destroy(&input.forks[index]);
	pthread_mutex_destroy(&input.print);
	pthread_mutex_destroy(&input.meal_check);
	pthread_mutex_destroy(&input.all_ate_checker);
	free(input.forks);
	free(input.ph);
	return (0);
}
