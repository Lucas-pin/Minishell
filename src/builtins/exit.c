/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:02:48 by lpin              #+#    #+#             */
/*   Updated: 2025/08/24 20:31:11 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <limits.h>

static int  get_last_status(t_env **_env)
{
	t_env *last_status;

	if (!_env || !*_env)
		return (0);
	last_status = find_key(_env, "?");
	if (!last_status || !last_status->value)
		return (0);
	return (ft_atoi(last_status->value));
}

static int  parse_sign(const char *s, int *i)
{
	int sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int  add_digit_ull(unsigned long long *acc,
					unsigned long long limit, unsigned int d)
{
	if (*acc > (limit - d) / 10ULL)
		return (0);
	*acc = *acc * 10ULL + d;
	return (1);
}

static int  parse_numeric_ll(const char *s, long long *out)
{
	int                     i;
	int                     sign;
	unsigned long long      acc;
	unsigned long long      limit;

	if (!s || !*s)
		return (0);
	i = 0;
	sign = parse_sign(s, &i);
	if (!ft_isdigit((unsigned char)s[i]))
		return (0);
	acc = 0;
	limit = (sign > 0) ? (unsigned long long)LLONG_MAX
		: (unsigned long long)LLONG_MAX + 1ULL;
	while (ft_isdigit((unsigned char)s[i]))
	{
		unsigned int d = (unsigned int)(s[i] - '0');
		if (!add_digit_ull(&acc, limit, d))
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*out = (sign > 0) ? (long long)acc : -(long long)acc;
	return (1);
}

int built_exit(char **args, t_env **_env)
{
	int         argc;
	long long   ll;
	int         status;

	printf("exit\n");
	if (!args || !*args)
		exit(0);
	argc = args_count(args);
	if (argc == 1)
		exit(get_last_status(_env));
	if (!parse_numeric_ll(args[1], &ll))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (argc > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	status = (int)((unsigned char)ll);
	exit(status);
	return (status);
}