/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/05 23:42:26 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

char *echo_verif_quote(char *str, t_echo *eko)
{
        int i;
        int flag;
        int flag_i;
        
        eko->i = 0;
        eko->j = 0;
        eko->line = malloc(sizeof(char) * (ft_strlen(str) + PATH_MAX + 1));
	if (!eko->line)
                return NULL;
        i = 0;
        flag_i = 0;
        flag = 0;
        while (str[i])
        {
                if (str[i] == '"')
                {
                        printf("trouvé une Double quote\n");
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == '"')
                                        {
                                                flag = 1;
                                                printf("trouvé LA PAIRE une Double quote\n");
                                                echo_take_of_double_quote(str, eko, i);
                                                ++i;
                                                flag_i = 1;
                                        }
                                if (flag == 1)
                                        break;
                        }
                        if (flag == 1)
                                continue;
                        
                        else {
                                return (printf("minishell: %s: command not found\n", str), NULL);        
                        }
                }
                flag = 0;
                if (str[i] == 39)
                {
                        printf("trouvé une simple quote\n");
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == 39)
                                        {
                                                flag = 1;
                                                ++i;
                                                printf("trouvé LA PAIRE une simple quote\n");
                                                echo_take_of_simple_quote(str, eko, i);
                                        }
                                if (flag == 1)
                                        break;
                        }
                        if (flag == 1)
                                continue;
                        return (printf("minishell: %s: command not found\n", str), NULL);
                }
                if (flag_i == 0)
                        ++i;
                flag_i = 0;
                flag = 0;
        }
        return (eko->line);
}

// void echo_args(char **tab, t_echo *eko)
// {
//         int i;
        
//         i = 2;
//         while (tab[i])
//                 {
//                         if (tab[i + 1] == NULL)
//                         {
//                                 printf("%s", echo_verif_quote(tab[i], eko));
//                                 free_tab(tab);
//                                 return;
//                         }
//                         printf("%s ", echo_verif_quote(tab[i], eko));
//                         ++i;
//                 }
// }
char *remake_str(char **tab, t_echo *eko, int i)
{
        int j;
        int k;
        char *new_str;
        
        new_str = malloc(sizeof(char) * eko->len_str + 1);
        if (new_str == NULL)
                return (NULL);
        j = 0;
        k = 0;
        while (tab[i])
        {
                while(tab[i][j])
                {
                        new_str[k] = tab[i][j];
                        ++k;
                        ++j;
                }
                j = 0;
                ++i;
        }
        new_str[k] = '\0';
        return(new_str);
}
// int verif_even_quote(char *str, t_echo *eko)
// {
//         int i;
        
//         i = 0;
//         eko->flag_double = 0;
//         eko->flag_simple = 0;
        
//         while (str[i])
//         {
//                 if (str[i] == '"')
//                         eko->flag_double += 1;
//                 if (str[i] == 39)
//                         eko->flag_simple += 1;
//         }
//         if (eko->flag_double != 0)
//         {
//                 if (eko->flag_double % 2 != 0)
//                 {
                        
//                 }

//                 else {
                        
//                 }
                
//         }
//         if else (eko->flag_double == 0)
        

//         || eko->flag_simple != 0
        
// }

void echo(char **tab, t_echo *eko)
{
        char *line;
        char *tmp;


        line = remake_str(tab, eko, 1);
        printf("%s\n", line);
        // verif_even_quote(line, eko);
        // if (ft_strcmp(tab[1], "-n") == 0)
        //         return (echo_args(tab, &eko));
        // else {
        tmp = echo_verif_quote(line, eko);
        if (tmp == NULL)
                return;
        printf("%s\n", tmp);
}


int builtin(char *line)
{
        
        char **tab;
        
        t_echo eko;
        eko.len_str = ft_strlen(line);
        tab = ft_split(line, ' ');
        if (ft_strcmp(tab[0], "echo") == 0)
                return (echo(tab, &eko), 1);
        if (ft_strcmp(tab[0], "cd") == 0)
                return (cd_project(tab), 1);
        if (ft_strcmp(tab[0], "pwd") == 0)
                return (pwd(tab), 1);
        if (ft_strcmp(tab[0], "export") == 0)
                return (export(tab), 1);
        return(0);
}
