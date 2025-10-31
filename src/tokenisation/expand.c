/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:05 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 16:54:06 by rgalmich         ###   ########.fr       */
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

int	copy_var_value(char *dst, const char *src, int *i, char **env)
{
	char	name[256];
	int		n;
	char	*val;
	int		len;

	n = 0;
	(*i)++;
	if (src[*i] == '?')
	{
		val = ft_itoa(g_exit_status);
		len = ft_strlcpy(dst, val, 4096);
		free(val);
		(*i)++;
		return (len);
	}
	while (ft_isalnum(src[*i]) || src[*i] == '_')
		name[n++] = src[(*i)++];
	name[n] = '\0';
	val = get_env_value(env, name);
	if (!val)
		return (0);
	return (ft_strlcpy(dst, val, 4096));
}
