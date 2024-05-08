/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:34 by nabil             #+#    #+#             */
/*   Updated: 2024/05/08 23:44:27 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

int	uni_bis(char *code)
{
	int	code_retour;
	int	k;

	code_retour = 0;
	k = 0;
	while (k < 4)
	{
		if (code[k] >= '0' && code[k] <= '9')
			code_retour = code_retour * 16 + (code[k] - '0');
		else if (code[k] >= 'a' && code[k] <= 'f')
			code_retour = code_retour * 16 + (code[k] - 'a' + 10);
		else if (code[k] >= 'A' && code[k] <= 'F')
			code_retour = code_retour * 16 + (code[k] - 'A' + 10);
		else
		{
			ft_dprintf(2, "Caractère hexadécimal invalide : %c\n", code[k]);
			exit(1);
		}
		k++;
	}
	return (code_retour);
}

char	*unicode(char *str, int size, t_sighandler *s)
{
	s->uni.new_str = malloc(sizeof(char) * (size + 1));
	if (!s->uni.new_str)
		return (free(str), exit(1), NULL);
	while (str[s->uni.i])
	{
		if (str[s->uni.i] == '\\' && str[s->uni.i + 1] == 'u')
		{
			s->uni.j = -1;
			while (s->uni.j++ < 4)
				s->uni.code[s->uni.j] = str[s->uni.i + 2 + s->uni.j];
			s->uni.code[s->uni.j] = '\0';
			s->uni.new_str[s->uni.k] = uni_bis(s->uni.code);
			s->uni.k++;
			s->uni.i += 6;
		}
		else
		{
			s->uni.new_str[s->uni.k] = str[s->uni.i];
			(s->uni.i++);
			(s->uni.k++);
		}
	}

	return (s->uni.new_str[s->uni.k] = '\0', s->uni.new_str);
}

void start_sig(t_sighandler *s, char **p_str, char *byte, int *bit_count)
{
    if (++(*bit_count) == 8)
    {
        if (*p_str == NULL)
            s->str_f = ft_strjoin("", byte);
        else
        {
            s->str_f = ft_strjoin(*p_str, byte);
            free(*p_str);
        }
        *p_str = s->str_f;
        *bit_count = 0;
        if (*byte == '\0')
            s->byte_bis = '\0';
        *byte = 0;
    }
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	t_sighandler	s;
	static char		*p_str = NULL;
	static char		byte = 0;
	static int		bit_count = 0;

	(void)context;
	init_s(&s);
	if (sig == SIGUSR1)
		byte |= (1 << bit_count);
	start_sig(&s, &p_str, &byte, &bit_count);
	if (s.byte_bis == '\0' && p_str != NULL)
	{
		ft_printf("%s\n", unicode(p_str, ft_strlen(p_str), &s));
		s.byte_bis = 1;
		(free(p_str), free(s.uni.new_str), p_str = NULL);
		s.byte = 0;
        kill(info->si_pid, SIGUSR2);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				server_pid;

	server_pid = getpid();
	ft_printf("PID du serveur : %d\n", server_pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sig_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_dprintf(2, "Error: PID");
		exit(EXIT_FAILURE);
	}
	ft_dprintf(2, "Serveur prêt à recevoir des messages...\n");
	while (1)
		pause();
}
