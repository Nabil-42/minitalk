/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:54 by nabil             #+#    #+#             */
/*   Updated: 2024/04/09 17:29:11 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

int main(int argc, char **argv)
{
    int server_pid;
    char *message;
    int i;
    
    if (argc != 3)
        return (ft_dprintf(2, "Erreur : Nombre d'argument\n"));
    server_pid = ft_atoi(argv[1]);
    message = argv[2];
    i = 0;
    while(*message)
    {
        while(i < 8)
        {
            if (*message & (1 << i))
                kill(server_pid, SIGUSR1);
            else kill(server_pid, SIGUSR2);
            ++i;
            usleep(50);
        }
        message++;
    }

    i = 0;
    while (i < 8)
    {
        kill(server_pid, SIGUSR2);
        usleep(50);
        ++i;   
    }
}