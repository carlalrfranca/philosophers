/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:45:11 by cleticia          #+#    #+#             */
/*   Updated: 2022/06/16 00:28:51 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval	tm_value;
	long long		milliseconds;

	gettimeofday(&tm_value, NULL);
	milliseconds = (tm_value.tv_sec * 1000) + (tm_value.tv_usec / 1000);
	return (milliseconds);
}

void	print_message(long long time, t_ph *philo, char *message)
{
	pthread_mutex_lock(&philo->ret_principal->print);
	if (philo->ret_principal->checker != 1)
		printf("%5lld %3d %s\n",
			time - philo->ret_principal->start_meal, philo->philo, message);
	pthread_mutex_unlock(&philo->ret_principal->print);
}

void	lock_and_print(t_principal *input, char *msg, t_ph *ph)
{
	pthread_mutex_lock(&input->meal_check);
	print_message(get_time(), ph, msg);
	pthread_mutex_unlock(&input->meal_check);
}

void	smart_sleep(int ms)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < (long long)ms)
		usleep(10);
}

int	check_dead(int index, t_principal *input)
{
	print_message(get_time(), &input->ph[index], "died");
	input->checker = 1;
	pthread_mutex_unlock(&input->meal_check);
	return (1);
}
