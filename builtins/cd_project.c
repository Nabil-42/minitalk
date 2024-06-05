/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:19:28 by tissad            #+#    #+#             */
/*   Updated: 2024/06/04 16:27:35 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../lib/libft/includes/libft.h"

int cd_based_path(char *cmd)
{
	int		i;
	int		status;
	char	**tab;
	char	*str;
	char	*tmp;
	char	*path_env;

	status = access(cmd, X_OK);
	if (status == 0)
		return (1);
	path_env = getenv("PATH");
	tab = ft_split(path_env, ':');
	i = 0;
	while (tab[i])
	{
		str = ft_strjoin(tab[i], "/");
		tmp = ft_strjoin(str, cmd);
		free(str);
		status = access(tmp, X_OK);
		if (status == 0)
			return (free_tab(tab), 1);
		free(tmp);
		++i;
	}
	return (printf("minishell: %s: No such file or directory\n", cmd), 0);
}

void cd_project(char **tab)
{
        char *user;
        char *tmp;
        
        if (tab[1] == NULL)
        {
                user = getenv("USER"); 
                tmp = ft_strjoin("/home/", user);
                chdir(tmp);
                free(tmp);
                free_tab(tab);
                return;
        }
        if (cd_based_path(tab[1]) == 1)
        {        
                chdir(tab[1]);
                free_tab(tab);        
        }
}
