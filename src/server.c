/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:34 by nabil             #+#    #+#             */
/*   Updated: 2024/04/09 17:41:18 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

// static void sig_handler(int sig)
// {
//     static unsigned char byte;
//     static int bit_count;
//     char buf[1024];
//     static int buf_index;
    
//     byte = '0';
//     bit_count = 0;
//     buf_index = 0;
//     if (sig == SIGUSR1)
//         byte |= (1 << bit_count);
// }

// int main()
// {
//     struct sigaction sa;
    
//     sa.sa_handler = sig_handler;
    
// }

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

static void sig_handler(int sig)
{
    static unsigned char byte = 0;
    static int bit_count = 0;
    static char buf[BUF_SIZE];
    static int buf_index = 0;

    if (sig == SIGUSR1)
    {
        byte |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8)
    {
        buf[buf_index++] = byte;
        bit_count = 0;
        byte = 0;
    }

    if (byte == '\0')
    {
        printf("Message reçu : %s\n", buf);
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    struct sigaction ; // Déclaration d'une variable de type struct sigaction

    sigaction = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Serveur prêt à recevoir des messages...\n");

    while (1)
    {
        pause(); // Attendre les signaux
    }

    return 0;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}

