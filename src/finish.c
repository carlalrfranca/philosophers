/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:45:11 by cleticia          #+#    #+#             */
/*   Updated: 2022/06/16 00:29:00 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	verify_six_arg(t_principal *input)
{
	int	index;

	index = 0;
	while (input->nb_eat > 0 && index < input->nb_ph)
	{
		pthread_mutex_lock(&input->meal_check);
		if (get_time() - input->ph[index].last_meal > input->tm_to_die)
		{
			check_dead(index, input);
			return (1);
		}
		pthread_mutex_unlock(&input->meal_check);
		pthread_mutex_lock(&input->all_ate_checker);
		if (input->ph[index].meal >= input->nb_eat)
			index++;
		pthread_mutex_unlock(&input->all_ate_checker);
	}
	if (index == input->nb_ph)
	{
		pthread_mutex_lock(&input->all_ate_checker);
		input->full_philos = 1;
		pthread_mutex_unlock(&input->all_ate_checker);
		return (1);
	}
	return (0);
}

static void	until_die(t_principal *input)
{
	int	index;

	index = -1;
	while (++index < input->nb_ph)
	{
		pthread_mutex_lock(&input->meal_check);
		if (get_time() - input->ph[index].last_meal > input->tm_to_die)
		{
			check_dead(index, input);
			return ;
		}
		else
			pthread_mutex_unlock(&input->meal_check);
		smart_sleep(1);
		if (index + 1 == input->nb_ph)
		index = -1;
	}
}

void	*has_died(void *param)
{
	t_principal	*input;

	input = param;
	if (input->nb_eat == 0 || (input->nb_eat > 0 && input->nb_ph == 1))
	{
		until_die(input);
		return (NULL);
	}
	else
	{
		pthread_mutex_lock(&input->all_ate_checker);
		while (input->full_philos != 1)
		{
			pthread_mutex_unlock(&input->all_ate_checker);
			if (verify_six_arg(input) == 1)
				return (NULL);
			smart_sleep(1);
			pthread_mutex_lock(&input->all_ate_checker);
		}
	}
	return (NULL);
}

void	*one_philo(t_ph *philo)
{
	pthread_mutex_t	*fork;

	fork = philo->ret_principal->forks;
	pthread_mutex_lock(&fork[philo->right_fork]);
	lock_and_print(philo->ret_principal, "has taken a fork", philo);
	pthread_mutex_unlock(&fork[philo->right_fork]);
	lock_and_print(philo->ret_principal, "dead", philo);
	pthread_mutex_lock(&philo->ret_principal->meal_check);
	philo->last_meal = get_time();
	philo->ret_principal->checker = 1;
	pthread_mutex_unlock(&philo->ret_principal->meal_check);
	return (NULL);
}
