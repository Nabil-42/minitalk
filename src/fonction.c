/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:40:27 by nabboud           #+#    #+#             */
/*   Updated: 2024/05/04 21:27:34 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

void	init_s(t_sighandler *s)
{
	s->str_f = NULL;
	s->byte_bis = 1;
	s->uni.k = 0;
	s->uni.i = 0;
	s->uni.j = 0;
}
