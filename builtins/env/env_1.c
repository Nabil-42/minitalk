/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabil <nabil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:26 by tissad            #+#    #+#             */
/*   Updated: 2024/06/18 20:49:49 by nabil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/libft/includes/libft.h"
#include "env/env.h"

void	delete_envp(t_env *env)
{
	int		i;
	
	i = 0;
	while (i < MAX_ENV)
	{
		ft_lstclear(&env->env_p[i], del);
		i++;
	}	
}

int	exist_env_var(char *env_var, char *key, t_list *lst)
{
	t_list *lst_iter;
	
	lst_iter = lst;
	while (lst_iter)
	{
		if (ft_strncmp(key, lst_iter->content, ft_strlen(key)) == 0)
		{
			free(lst_iter->content);
			lst_iter->content = ft_strdup(env_var);
			return (1);
		}
		lst_iter = lst_iter->next;
	}
	return (0);
}

void	ft_export(t_env *env, char *env_var)
{
	t_list	*new_var;
	char	*key;
	int		hash;

	key = get_key(env_var);
	hash = hash_function(key, MAX_ENV);
	if (!env->env_p[hash])
	{
		new_var = ft_lstnew((void *)ft_strdup(env_var));
		ft_lstadd_back(&env->env_p[hash], new_var);
		env->nb_var++;
	}
	else
	{
		if(!exist_env_var(env_var, key, env->env_p[hash]))
		{
			new_var = ft_lstnew((void *)ft_strdup(env_var));
			ft_lstadd_back(&env->env_p[hash], new_var);
			env->nb_var++;	
		}
	}
	free(key);
}

void	ft_unset(t_env *env, char *key)
{
	t_list	**lst;
	int		hash;

	hash = hash_function(key, MAX_ENV);
	lst = &env->env_p[hash];
	ft_lstdelcond(lst, key, cond, del);
}

void	ft_env(t_env *env)
{
	char	**local_env;
	int		i;

	local_env = get_local_env(env);
	i = 0;
	while (local_env[i])
	{
		if (local_env[i])
			printf("%s\n", local_env[i]);

		i++;
	}
	free(local_env);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	t_env env;
	
// 	init_local_env(&env);
// 	dup_env(&env, envp);
// 	ft_export(&env, "VAR=roroooooooooooooo");
// 	ft_env(&env);
// 	ft_export(&env, "TOTO=111");
// 	ft_export(&env, "TITI=111");
// 	ft_export(&env, "TUTU=111");
// 	ft_export(&env, "VAR=11111111111111111111111111111111111111111");
// 	ft_export(&env, "VAR=0");
// 	ft_env(&env);
// 	ft_unset(&env, "VAR");
// 	ft_env(&env);	
// 	delete_envp(&env);
// }