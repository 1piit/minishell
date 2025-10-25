/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:10:47 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/25 18:36:34 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars(const char *str, char **env, int expand)
{
	char	buf[4096];
	int		i;
	int		j;

	if (!expand)
		return (ft_strdup(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			j += copy_var_value(&buf[j], str, &i, env);
		else
			buf[j++] = str[i++];
	}
	buf[j] = '\0';
	return (ft_strdup(buf));
}

int	copy_var_value(char *dst, const char *src, int *i, char **env)
{
	char	name[256];
	int		n;
	char	*val;

	n = 0;
	(*i)++;
	if (src[*i] == '?')
	{
		val = ft_itoa(g_exit_status);
		(*i)++;
		return (ft_strlcpy(dst, val, 4096));
	}
	while (ft_isalnum(src[*i]) || src[*i] == '_')
		name[n++] = src[(*i)++];
	name[n] = '\0';
	val = get_env_value(env, name);
	if (!val)
		return (0);
	return (ft_strlcpy(dst, val, 4096));
}
