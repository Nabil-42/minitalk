/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:52 by nabil             #+#    #+#             */
/*   Updated: 2024/05/13 18:02:48 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <signal.h>

typedef struct s_uni
{
	char	*new_str;
	char	code[6];
	int		i;
	int		j;
	int		k;
}			t_uni;

typedef struct s_sighandler
{
	char	byte;
	char	*str_f;
	char	*p_str;
	int		bit_count;
	int		byte_bis;
	t_uni	uni;
}			t_sighandler;

void		init_s(t_sighandler *s);

#endif