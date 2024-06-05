/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/05 23:45:52 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int dollar(char *str, char *new_str, int i, int j)
{
        char *variable_env;
        int k;
        char *name;

        k = 0;
        
        if (str[i + j] != '$')
                return 0;
        // if (str[i + j] == '$' && str[i + j - 1] == 39)
        //         return 0;
        variable_env = malloc(sizeof(char) * PATH_MAX + 1);
        if (variable_env == NULL)
                return 0;
        // printf("TEST i = %d j = %d\n", i, j);
        if (str[i + j] == '$')
        {
                j++;
                while (str[i + j] >= 'A' && str[i + j] <= 'Z'
                        && str[i + j] != '\0')
                {
                        // printf("%s k = %d j = %d\n", "TEST DANS BOUCLE", k, j);
                        variable_env[k] = str[i + j];
                        ++k;
                        ++j;
                }
                // printf("%s\n", variable_env);
                name = getenv(variable_env);
                k = 0;
                while(name[k])
                {
                        new_str[i] = name[k];
                        // printf("new_str[i] = %c", new_str[i]);
                        ++i;
                        ++k;
                }
                
                
                return (ft_strlen(name));
        }
        return (0);
}


void echo_take_of_simple_quote(char *str, t_echo *eko, int n)
{
	int flag;
        flag = 0;
        while(eko->i <= n)
        {
                if (str[eko->i] == 39 && str[eko->i + 1] == 39)
                {
                        eko->i += 2;
                        return;
                }
                if (str[eko->i] == 39)
                {
                        ++flag;
                        if (flag == 1)
                                ++eko->i;
                        else{
                                ++eko->i;
                                eko->line[eko->j] = '\0';
                                return;
                        }
                }
                eko->line[eko->j] = str[eko->i];
                ++eko->i;
                ++eko->j;
        }
}