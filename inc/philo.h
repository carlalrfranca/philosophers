/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:43:45 by cleticia          #+#    #+#             */
/*   Updated: 2022/06/16 00:29:08 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define FT_ERROR 1
# define FT_SUCCESS 0

typedef struct s_principal	t_principal;

typedef struct s_ph
{
	long long	last_meal;
	int			philo;
	int			meal;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;
	t_principal	*ret_principal;
}	t_ph;

struct s_principal
{
	int				nb_ph;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				nb_eat;
	long long		start_meal;
	int				checker;
	int				full_philos;
	t_ph			*ph;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	all_ate_checker;	
	pthread_mutex_t	meal_check;
};

int			verify_digit(char **argv);
int			ft_isdigit(int c);
int			ft_exit(char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_message(long long time, t_ph *philo, char *message);
void		lock_and_print(t_principal *input, char *msg, t_ph *ph);
void		smart_sleep(int ms);
int			check_dead(int index, t_principal *input);
int			management_threads(t_principal *input);
void		*has_died(void *param);
void		eat(t_ph *philo);
void		*one_philo(t_ph *philo);
void		*start_routine(void *param);
int			create_philos(t_principal *input);

#endif
