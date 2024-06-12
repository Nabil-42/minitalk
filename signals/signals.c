/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:37:06 by nabil             #+#    #+#             */
/*   Updated: 2024/06/12 15:12:35 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <libft.h>
#include "../lib/libft/includes/libft.h"
#include <signal.h>

volatile sig_atomic_t flag = 0;
#define PATH_MAX 4096

// static char	*ft_get_prompt(void)
// {
// 	char	path[PATH_MAX];
// 	char	*prompt;
// 	char	*tmp;

// 	tmp = ft_strjoin("-> ", getcwd(path, PATH_MAX));
// 	prompt = ft_strjoin(tmp, " ");
// 	free(tmp);
// 	return (prompt);
// }

void sig_handler(int sig)
{
        // char *prompt;
        if (sig == SIGINT)
        {       
                if (flag == 1)
                {
                        flag = 0;
                        exit(1);
                }
                if (flag == 2)
                {
                        // printf("\n");
                        // rl_on_new_line();
                        // rl_replace_line("", 0);
                        // prompt = ft_get_prompt();
                        // readline(prompt);
                        // flag = 0;
                }
                else 
                {
                printf("\n");
                rl_on_new_line();
                rl_replace_line("", 0);
                rl_redisplay();
                }
        }
}

void main_signal()
{
        struct sigaction sa;
        
        sa.sa_handler = &sig_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if ((sigaction(SIGINT, &sa, NULL) == -1)
                || (sigaction(SIGQUIT, &sa, NULL) == -1))
        {
                perror("sigaction\n");
                exit(EXIT_FAILURE);
        }
}

