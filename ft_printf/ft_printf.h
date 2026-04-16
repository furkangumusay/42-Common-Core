/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:59:12 by fgumusay          #+#    #+#             */
/*   Updated: 2024/01/31 12:42:45 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putstr(const char *str);
int	ft_decimaltohex(unsigned long int x, char c);
int	ft_putnbr(int nbr);
int	ft_putunbr(unsigned int x);
int	ft_putpoint(unsigned long x, int flag);

#endif