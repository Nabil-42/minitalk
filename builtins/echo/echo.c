/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/08 20:05:10 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

#define PATH_MAX 4096

char *echo_verif_quote(char *str, t_echo *eko)
{
        int i;
        int flag;
        int flag_i;
        
        i = 0;
        flag_i = 0;
        flag = 0;
        eko->line[0] = '\0';
        while (str[i])
        {
                if (str[i] == '"')
                {
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == '"')
                                        {
                                                flag = 1;
                                                if (echo_take_of_double_quote(str, eko, i) == -1)
                                                        return (NULL);
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
                        while (str[i])
                        {
                                ++i;
                                if (str[i] == 39)
                                        {
                                                flag = 1;
                                                ++i;
                                                echo_take_of_simple_quote(str, eko, i);                                        }
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

void echo_args(char *str, t_echo *eko, char **tab, char *tmp)
{
        if (tmp[0] == '\0')
        {
                dollar_n(str, eko);
                free_tab(tab);
                return;
        }
        printf("%s", tmp);
        free_tab(tab);
}
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
                new_str[k] = ' ';
                ++k;
                j = 0;
                ++i;
        }
        new_str[k] = '\0';
        return(new_str);
}

void echo(char **tab, t_echo *eko)
{
    char *str = NULL;
    char *tmp = NULL;

    if (tab[1] && ft_strcmp(tab[1], "-n") == 0) {
        str = remake_str(tab, eko, 2);
    } else {
        str = remake_str(tab, eko, 1);
    }
    if (!str) {
        
        return;
    }
    eko->line = malloc(sizeof(char) * (eko->len_str + PATH_MAX + 1));
    if (!eko->line) {
        
        free(str); 
        return;
    }
    tmp = echo_verif_quote(str, eko);
    if (tmp == NULL) {
        free(eko->line);
        free(str); 
        return;
    }

    if (tab[1] && ft_strcmp(tab[1], "-n") == 0) {
        echo_args(str, eko, tab, tmp);
        free(eko->line);
        free(str);
        return;
    }

    if (*tmp == '\0') {
        dollar(str, eko);
        free_tab(tab);
        free(eko->line);
        free(str);
        return;
    }

    printf("%s\n", tmp);
    free_tab(tab);
    free(eko->line);
    free(str);
}

void init_eko(t_echo *eko, char *line)
{
        (void)line;
        eko->len_str = 200;
        eko->i = 0;
        eko->j = 0;
        eko->flag_double = 0;
        eko->flag_simple = 0;
        eko->line = NULL;
}

int builtin(char *line)
{
        
        char **tab;
        
        t_echo eko;
        tab = ft_split(line, ' ');
        init_eko(&eko, line);
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
