/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:05 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 21:04:32 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars(t_shell *sh, const char *str, int expand)
{
	char	buf[4096];
	int		i;
	int		j;
	int		copied;

	copied = 0;
	if (!expand)
		return (ft_strdup(str));
	i = 0;
	j = 0;
	while (str[i] && j < 4095)
	{
		if (str[i] == '$' && str[i + 1])
		{
			copied = copy_var_value(sh, &buf[j], str, &i);
			j += copied;
		}
		else
			buf[j++] = str[i++];
	}
	buf[j] = '\0';
	return (ft_strdup(buf));
}

/*
char	*get_env_value(char **env, const char *var)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}*/

char	*get_env_value(t_shell *sh, char **envp, char *name)
{
	char	*prefix;
	size_t	len;
	int		i;

	if (!name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(sh->exit_status));
	len = ft_strlen(name);
	prefix = ft_strjoin(name, "=");
	if (!prefix)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], prefix, len + 1) == 0)
			return (free_null((void **)&prefix), ft_strdup(envp[i] + len + 1));
		i++;
	}
	free_null((void **)&prefix);
	return (ft_strdup(""));
}

int	copy_var_value(t_shell *sh, char *dst, const char *src, int *i)
{
	char	name[256];
	int		n;
	char	*val;
	int		len;

	n = 0;
	(*i)++;
	if (src[*i] == '?')
	{
		val = ft_itoa(sh->exit_status);
		len = ft_strlcpy(dst, val, 4096);
		free_null((void **)&val);
		(*i)++;
		return (len);
	}
	while (ft_isalnum(src[*i]) || src[*i] == '_')
		name[n++] = src[(*i)++];
	name[n] = '\0';
	val = get_env_value(sh, sh->env, name);
	if (!val)
		return (0);
	return (ft_strlcpy(dst, val, 4096));
}
