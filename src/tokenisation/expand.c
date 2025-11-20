/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:05 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 16:52:42 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars(const char *str, char **env, int expand)
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
			copied = copy_var_value(&buf[j], str, &i, env);
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

char	*get_env_value(char **envp, char *name, int exit_status)
{
	char	*prefix;
	size_t	len;
	int		i;

	if (!name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 2) == 0)
		return (itoa_status(exit_status));
	len = ft_strlen(name);
	prefix = ft_strjoin(name, "=");
	if (!prefix)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], prefix, len + 1) == 0)
			return (free(prefix), ft_strdup(envp[i] + len + 1));
		i++;
	}
	free(prefix);
	return (ft_strdup(""));
}

int	copy_var_value(char *dst, const char *src, int *i, char **env)
{
	char	name[256];
	int		n;
	char	*val;
	int		len;
	t_shell	*sh;

	n = 0;
	(*i)++;
	if (src[*i] == '?')
	{
		val = sh->exit_status;
		len = ft_strlcpy(dst, val, 4096);
		free(val);
		(*i)++;
		return (len);
	}
	while (ft_isalnum(src[*i]) || src[*i] == '_')
		name[n++] = src[(*i)++];
	name[n] = '\0';
	val = get_env_value(env, name, sh->exit_status);
	if (!val)
		return (0);
	return (ft_strlcpy(dst, val, 4096));
}
