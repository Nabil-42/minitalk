/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:34 by nabil             #+#    #+#             */
/*   Updated: 2024/04/28 19:07:40 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

#define BUF_SIZE 1024

static int client_pid;

void    reception_check(int pid)
{
    static int counter = 0;
    
    counter++;
    if (counter == 48)
    {
        client_pid = pid;
    } 
    if (counter >= 48)
    {
        ft_printf("%d\n", client_pid);
        usleep(500); 
        if (kill(client_pid, SIGUSR1) == -1)
            {
                ft_printf("Error: PID");
                exit(EXIT_FAILURE);
            }
    }
}

static void sig_handler(int sig)
{
    static unsigned char byte = 0;
    static int bit_count = 0;
    static char buf[BUF_SIZE];
    static int buf_index = 0;
    int     byte_bis = 1;

    if (sig == SIGUSR1)
    {
        byte |= (1 << bit_count);
    }
    
    bit_count++;

    if (bit_count == 8)
    {
        buf[buf_index++] = byte;
        bit_count = 0;
        if (byte == 0)
            byte_bis = 0;
        byte = 0;
    }
    reception_check(ft_atoi(buf));
    if (byte_bis == '\0')
    {
        printf("Message reçu : %s\n", buf);
        byte_bis = 1;
        ft_bzero(buf, buf_index);
        buf_index = 0;
        kill(client_pid, SIGUSR1);
    }
}

int main(void)
{
    struct sigaction sa; 

    pid_t server_pid = getpid();
    printf("PID du serveur : %d\n", server_pid);
    
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_dprintf(2, "Error: PID");
        exit(EXIT_FAILURE);
    }

    printf("Serveur prêt à recevoir des messages...\n");

    while (1)
        pause();    
}

