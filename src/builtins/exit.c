/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:02:48 by lpin              #+#    #+#             */
/*   Updated: 2025/09/08 22:37:10 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/signals.h"
#include <limits.h>

static int	parse_sign(const char *s, int *i, unsigned long long *limit)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	if (limit)
	{
		if (sign > 0)
			*limit = (unsigned long long)LLONG_MAX;
		else
			*limit = (unsigned long long)LLONG_MAX + 1ULL;
	}
	return (sign);
}

static int	add_digit_ull(unsigned long long *acc,
					unsigned long long limit, unsigned int d)
{
	if (*acc > (limit - d) / 10ULL)
		return (0);
	*acc = *acc * 10ULL + d;
	return (1);
}

static int	parse_numeric_ll(const char *s, long long *out)
{
	int						i;
	int						sign;
	unsigned long long		acc;
	unsigned long long		limit;

	i = 0;
	acc = 0;
	if (!s || !*s)
		return (0);
	sign = parse_sign(s, &i, &limit);
	if (!ft_isdigit((unsigned char)s[i]))
		return (0);
	while (ft_isdigit((unsigned char)s[i]))
	{
		if (!add_digit_ull(&acc, limit, (unsigned int)(s[i] - '0')))
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	if (sign < 0)
		*out = -(long long)acc;
	else
		*out = (long long)acc;
	return (1);
}

int	built_exit(char **args, t_env **_env)
{
	int			argc;
	long long	ll;
	int			status;

	printf("exit\n");
	(void)_env;
	if (!args || !*args)
		exit(0);
	argc = args_count(args);
	if (argc == 1)
		exit(get_exit_status());
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
	return (exit(status), status);
}
