/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:52 by nabil             #+#    #+#             */
/*   Updated: 2024/04/28 12:16:24 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
#include "../libft/libft.h"
#include <signal.h>

typedef struct s_minitalk
{
        char *msg;
        int  server_pid;
}t_minitalk;
 
#endif