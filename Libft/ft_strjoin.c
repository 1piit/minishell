/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:22:15 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/30 10:49:03 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totallen;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	totallen = ft_strlen(s1) + ft_strlen(s2);
	new = malloc((totallen + 1) * (sizeof(char)));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, totallen + 1);
	ft_strlcat(new, s2, totallen + 1);
	return (new);
}
