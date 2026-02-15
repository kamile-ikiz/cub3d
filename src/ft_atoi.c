/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:39 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 00:20:20 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check(unsigned long long result, const char *str, int sign,
			int i)
{
	if (result > 922337203685477580 || (result == 922337203685477580 && (str[i]
				- '0') > 7))
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	else
		return (1);
}

static int	ft_white_space(int i, const char *str)
{
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

static long long	process_digits(const char *str, int *i, int sign)
{
	long long	result;
	int			re;

	result = 0;
	while (str[*i] >= 48 && str[*i] <= 57)
	{
		re = ft_check(result, str, sign, *i);
		if (re == -1 || re == 0)
			return ((long long)re);
		result = ((result * 10) + (str[(*i)++] - 48));
		if (result > 2147483647)
			return (-1);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	sign = 1;
	i += ft_white_space(i, str);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	result = process_digits(str, &i, sign);
	if (result == -1 || result == 0)
		return ((int)result);
	return ((int)(result * sign));
}
