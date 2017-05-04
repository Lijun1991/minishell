/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:26:57 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 10:26:59 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_fprintf(int fd, char *format, ...)
{
	va_list	args;
	char	*str;
	t_info	conver_info;

	conver_info.flag_info = (t_flag*)malloc(sizeof(t_flag) * 1);
	conver_info.count = 0;
	conver_info.fd = fd;
	va_start(args, format);
	str = (char*)format;
	while (*str != '\0')
	{
		while ((*str != '%') && (*str != '\0'))
		{
			conver_info.count += pputchar(*str, conver_info.fd);
			str++;
		}
		if (*str == '%')
			str++;
		if (*str != '\0')
			str = print_convert_result(str, args, &conver_info);
	}
	va_end(args);
	free(conver_info.flag_info);
	return (conver_info.count);
}
