/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 20:05:34 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 20:05:35 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		print_no_precision(t_info *conver_info, char *str, int len)
{
	if (conver_info->precision == -1)
	{
		if (len + conver_info->sign >= conver_info->field_width)
		{
			conver_info->count += pputstr(conver_info->pre_sign, \
				conver_info->fd);
			print_str(str, conver_info);
		}
		else
			norm_print_no_precision(conver_info, str, len);
	}
}

static void	norm1_print_str(t_info *conver_info)
{
	if (conver_info->iszero == 1 && conver_info->is_nopre == 1 && \
		conver_info->is_dot == 1 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 0)
	{
		if (ft_strchr("xXdou", conver_info->conversion_specifier))
			conver_info->count += pputchar('0', conver_info->fd);
	}
	if (conver_info->iszero == 1 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 1 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 0)
	{
		if (conver_info->conversion_specifier == 'o' && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
		if (ft_strchr("dox", conver_info->conversion_specifier) && \
			conver_info->field_width != -1)
			conver_info->count += pputchar(' ', conver_info->fd);
	}
	if (conver_info->iszero == 1 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 0 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 1)
	{
		if (ft_strchr("xXod", conver_info->conversion_specifier))
			conver_info->count += pputchar('0', conver_info->fd);
	}
}

static void	norm2_print_str(t_info *conver_info)
{
	if (conver_info->iszero == 1 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 0 && conver_info->is_dot_zero == 1 && \
		conver_info->is_dot_pre == 0)
	{
		if (conver_info->conversion_specifier == 'o' && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
		if (ft_strchr("dox", conver_info->conversion_specifier) && \
			conver_info->field_width != -1)
			conver_info->count += pputchar(' ', conver_info->fd);
	}
	if (conver_info->iszero == 0 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 0 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 1)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
	}
}

static void	norm3_print_str(t_info *conver_info)
{
	if (conver_info->iszero == 0 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 0 && conver_info->is_dot_zero == 1 && \
		conver_info->is_dot_pre == 0)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
	}
	if (conver_info->iszero == 0 && conver_info->is_nopre == 1 && \
		conver_info->is_dot == 1 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 0)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
	}
	if (conver_info->iszero == 0 && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 1 && conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 0)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) && \
			conver_info->flag_info->hash == '#')
			conver_info->count += pputchar('0', conver_info->fd);
	}
}

void		print_str(char *str, t_info *conver_info)
{
	norm1_print_str(conver_info);
	norm2_print_str(conver_info);
	norm3_print_str(conver_info);
	while (*str != '\0' && *str == '*')
		str++;
	while (*str != '\0' && *str != '*')
	{
		conver_info->count += pputchar(*str, conver_info->fd);
		str++;
	}
}
