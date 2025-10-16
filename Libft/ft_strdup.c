/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:01:32 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 12:56:00 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*no;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		size++;
	no = malloc(sizeof(char) * (size + 1));
	if (!no)
		return (NULL);
	i = 0;
	while (s[i])
	{
		no[i] = s[i];
		i++;
	}
	no[i] = '\0';
	return (no);
}

/*
#include <stdio.h>

int main(void)
{
    const char *original = "Hello, world!";
    char *copy;

    copy = ft_strdup(original);
    if (!copy)
    {
        printf("Erreur d'allocation.\n");
        return (1);
    }

    printf("Original : %s\n", original);
    printf("Copie     : %s\n", copy);

    // Vérifie si les pointeurs sont différents
    if (copy != original)
        printf("Les chaînes sont différentes en mémoire.\n");
    else
        printf("Erreur : les chaînes pointent vers la même adresse !\n");

    free(copy); // N'oublie pas de free la copie
    return (0);
}
*/
