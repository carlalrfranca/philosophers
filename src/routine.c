/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:47:06 by cleticia          #+#    #+#             */
/*   Updated: 2022/06/16 00:30:36 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_ph *philo)
{
	pthread_mutex_lock(&philo->ret_principal->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->ret_principal->forks[philo->right_fork]);
	lock_and_print(philo->ret_principal, "has taken a fork", philo);
	lock_and_print(philo->ret_principal, "has taken a fork", philo);
	pthread_mutex_lock(&philo->ret_principal->meal_check);
	print_message(get_time(), philo, "is eating");
	pthread_mutex_lock(&philo->ret_principal->all_ate_checker);
	philo->meal++;
	pthread_mutex_unlock(&philo->ret_principal->all_ate_checker);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->ret_principal->meal_check);
	usleep(philo->ret_principal->tm_to_eat * 1000);
	pthread_mutex_unlock(&philo->ret_principal->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->ret_principal->forks[philo->right_fork]);
}

static int	is_checker_true(t_ph *philo)
{
	pthread_mutex_lock(&philo->ret_principal->meal_check);
	if (philo->ret_principal->checker != 1)
	{
		pthread_mutex_unlock(&philo->ret_principal->meal_check);
		return (0);
	}
	pthread_mutex_unlock(&philo->ret_principal->meal_check);
	return (1);
}

static void	think_sleep(t_ph *philo)
{
	lock_and_print(philo->ret_principal, "is sleeping", philo);
	usleep(philo->ret_principal->tm_to_sleep * 1000);
	lock_and_print(philo->ret_principal, "is thinking", philo);
}

void	*start_routine(void *param)
{
	t_ph		*philo;

	philo = param;
	if (philo->ret_principal->nb_ph == 1)
		return (one_philo(philo));
	if (philo->philo % 2 == 0)
		usleep(1200);
	while (!is_checker_true(philo))
	{
		eat(philo);
		pthread_mutex_lock(&philo->ret_principal->all_ate_checker);
		if (philo->ret_principal->full_philos == 1)
		{
			pthread_mutex_unlock(&philo->ret_principal->all_ate_checker);
			break ;
		}
		pthread_mutex_unlock(&philo->ret_principal->all_ate_checker);
		think_sleep(philo);
	}
	return (NULL);
}

int	management_threads(t_principal *input)
{
	int	index;

	index = 0;
	pthread_create(&input->monitor, NULL, &has_died, input);
	while (index < input->nb_ph)
	{
		pthread_join(input->ph[index].thread, NULL);
		index++;
	}
	pthread_join(input->monitor, NULL);
	return (0);
}
