/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:54 by nabil             #+#    #+#             */
/*   Updated: 2024/05/03 09:20:53 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

static int flag;

void    write_message(char *message, int server_pid)
{
    int i;
    while(*message)
    {
        flag = 0;
        i = 0;
        while(i < 8)
        {
            if (*message & (1 << i))
                kill(server_pid, SIGUSR1);
            else kill(server_pid, SIGUSR2);
            ++i;
            usleep(500);
            while (flag == 0);
        }
        message++;
    }
    i = 0;
    while (i < 8)
    {
        flag = 0;
        kill(server_pid, SIGUSR2);
        ++i;
        usleep(500);
        while (flag == 0);
    }
}

static void sig_handler(int sig) 
{
    if (sig == SIGUSR1)
        flag = 1;
    if (sig == SIGUSR2)
    {
        ft_printf("Message bien envoyé\n");
    }
}

int main(int argc, char **argv)
{
    int server_pid;
    struct sigaction sa; 
    if (argc != 3)
        return (ft_dprintf(2, "Erreur : Nombre d'argument\n"));
    server_pid = ft_atoi(argv[1]);
    if (server_pid < 1)
        return (ft_dprintf(2, "Erreur : PID invalide\n"));
    sa.sa_handler = &sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_dprintf(2, "Error: PID");
        exit(EXIT_FAILURE);
    }
    write_message(argv[2], server_pid);
}
