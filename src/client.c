/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:54 by nabil             #+#    #+#             */
/*   Updated: 2024/04/28 19:05:07 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>


void    send_pid(int server_pid)
{
    pid_t pid_client;
    int i;
    char *msg;
    
    pid_client = getpid();
    msg = ft_itoa(pid_client);
    printf("%d\n", pid_client);
    while(*msg)
    {
        i = 0;
        while(i < 8)
        {
            if (*msg & (1 << i))
                kill(server_pid, SIGUSR1);
            else kill(server_pid, SIGUSR2);
            ++i;
            usleep(500);
        }
        msg++;
    }
}

void    write_message(char *message, int server_pid)
{
    int i;
    while(*message)
    {
        i = 0;
        while(i < 8)
        {
            if (*message & (1 << i))
                kill(server_pid, SIGUSR1);
            else kill(server_pid, SIGUSR2);
            ++i;
        }
        message++;
    }
    i = 0;
    while (i < 8)
    {
        kill(server_pid, SIGUSR2);
        ++i;   
    }
}

static void sig_handler(int sig) 
{
    if (sig == SIGUSR1)
    {
        printf("tu comprend\n");
    }
}

int main(int argc, char **argv)
{
    int server_pid;
    
    if (argc != 3)
        return (ft_dprintf(2, "Erreur : Nombre d'argument\n"));
    server_pid = ft_atoi(argv[1]);
    send_pid(server_pid);
    
    if (signal(server_pid, sig_handler) == SIG_ERR)
    {
        write_message(argv[2], server_pid);
    }
    
    while (1)
        pause();  
}
