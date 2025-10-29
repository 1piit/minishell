/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:37:17 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(const char *prompt)
{
	char	*line;

	line = readline((char *)prompt);
	if (line && *line)
		add_history(line);
	return (line);
}
