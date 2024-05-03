/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:34 by nabil             #+#    #+#             */
/*   Updated: 2024/05/03 09:54:11 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

int     uni_bis(char *code)
{
        int code_retour;
        code_retour = 0;
         int k;
         k = 0;
            while (k < 4) 
            {
                if (code[k] >= '0' && code[k] <= '9') {
                    code_retour = code_retour * 16 + (code[k] - '0');
                } else if (code[k] >= 'a' && code[k] <= 'f') {
                    code_retour = code_retour * 16 + (code[k] - 'a' + 10);
                } else if (code[k] >= 'A' && code[k] <= 'F') {
                    code_retour = code_retour * 16 + (code[k] - 'A' + 10);
                } else {
                    ft_dprintf(2, "Caractère hexadécimal invalide : %c\n", code[k]);
                    return(-1);
                }
                k++;
            }
            return (code_retour);
}

char    *unicode(char *str, int size)
{
    int i;
    char    *new_str;
    char    code[5];
    int j;
    int k;
    
    new_str = malloc(sizeof(char) * (size + 1));
    if (!new_str)
        return(free(str), exit(1), NULL);
    k = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1] == 'u')
        {
            j = 0;
            while (j < 4)
                code[j] = str[i + 2 + j], j++;
            code[j] = '\0';
            new_str[k] = uni_bis(code), ++k, i += 6;
        }
        else (new_str[k] = str[i], i++, k++);
    }
    new_str[k] = '\0';
    return (new_str);
}

static void sig_handler(int sig, siginfo_t *info, void *context)
{
    static char byte = 0;
    static int bit_count = 0;
    static char    *porte_str = NULL;
    int     byte_bis = 1;
    char    *str_final;
    (void)context;
    
    if (sig == SIGUSR1)
        byte |= (1 << bit_count);
    if (++bit_count == 8)
    {
        if (porte_str == NULL)
            str_final = ft_strjoin("", &byte);
        else (str_final = ft_strjoin(porte_str, &byte), free(porte_str));
        porte_str = str_final;
        bit_count = 0;
        if (byte == '\0')
            byte_bis = '\0';
        byte = 0;
    }
    if (byte_bis == '\0')
    {
        str_final = unicode(porte_str, ft_strlen(porte_str));
        (ft_printf("%s\n", str_final), byte_bis = 1);
        (free(porte_str), free(str_final), porte_str = NULL);
        (byte = 0, kill(info->si_pid, SIGUSR2));
    }
    kill(info->si_pid, SIGUSR1);
}

int main(void)
{
    struct sigaction sa; 

    pid_t server_pid = getpid();
    ft_printf("PID du serveur : %d\n", server_pid);
    
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &sig_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_dprintf(2, "Error: PID");
        exit(EXIT_FAILURE);
    }

    ft_dprintf(2, "Serveur prêt à recevoir des messages...\n");

    while (1)
        pause();    
}


