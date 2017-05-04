/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fprintf_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:14:43 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 11:14:46 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	number_to_print_unsigned(t_info *conver_info, va_list args)
{
	if (ft_strlen(conver_info->len_mod) != 0)
	{
		if (ft_strncmp(conver_info->len_mod, "hh", 2) == 0)
			return ((unsigned char)va_arg(args, unsigned int));
		if (ft_strncmp(conver_info->len_mod, "h", 1) == 0)
			return ((unsigned short)va_arg(args, unsigned int));
		if (ft_strncmp(conver_info->len_mod, "l", 1) == 0)
			return (va_arg(args, unsigned long));
		if (ft_strncmp(conver_info->len_mod, "ll", 2) == 0)
			return (va_arg(args, unsigned long long));
		if (ft_strncmp(conver_info->len_mod, "j", 1) == 0)
			return (va_arg(args, uintmax_t));
		if (ft_strncmp(conver_info->len_mod, "z", 1) == 0)
		{
			return (size_t)(va_arg(args, unsigned long long));
		}
	}
	return (va_arg(args, unsigned int));
}

long long			number_to_print_signed(t_info *conver_info, va_list args)
{
	if (ft_strlen(conver_info->len_mod) != 0)
	{
		if (ft_strncmp(conver_info->len_mod, "hh", 2) == 0)
			return ((char)va_arg(args, int));
		if (ft_strncmp(conver_info->len_mod, "h", 1) == 0)
			return ((short)va_arg(args, int));
		if (ft_strncmp(conver_info->len_mod, "l", 1) == 0)
			return (va_arg(args, long int));
		if (ft_strncmp(conver_info->len_mod, "ll", 2) == 0)
			return (va_arg(args, long long int));
		if (ft_strncmp(conver_info->len_mod, "j", 1) == 0)
			return (va_arg(args, intmax_t));
		if (ft_strncmp(conver_info->len_mod, "z", 1) == 0)
			return (ssize_t)(va_arg(args, long long));
	}
	return (va_arg(args, int));
}

void				norm_print_no_precision(t_info *conver_info, \
	char *str, int len)
{
	int		i;

	i = conver_info->field_width - len - conver_info->sign;
	if (conver_info->flag_info->zero == 'y')
	{
		conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
		print_nbr_helper(conver_info, i, '0');
	}
	else
	{
		print_nbr_helper(conver_info, i, ' ');
		conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
	}
	print_str(str, conver_info);
}
