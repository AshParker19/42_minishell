/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_minibox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/26 14:43:22 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_box(t_minibox *minibox, char **env)
{
	minibox->env = env;
	minibox->input_original = NULL;
	minibox->input_trimmed = NULL;
	minibox->input_quoted = NULL;
	minibox->input_expanded = NULL;
	minibox->tokens = NULL;
	minibox->root = NULL;
	minibox->local_vars = NULL;
	minibox->global_vars = NULL;
}

void free_input_strings(t_minibox *minibox)
{
	if (minibox->input_original)
		free(minibox->input_original);
	if (minibox->input_trimmed)
		free(minibox->input_trimmed);
	if (minibox->input_quoted)
		free (minibox->input_quoted);
	if (minibox->input_expanded)
		free(minibox->input_expanded);
}

void	free_matrix(t_minibox *minibox, int i)
{
	if (minibox->global_vars)
	{
		while (minibox->global_vars[++i])
			free (minibox->global_vars[i]);
		free (minibox->global_vars);		
	}
}

// TODO:
// Function should check all members of the minibox struct 
// and frees them if they are inizialised
// exits program
void free_and_close_box(t_minibox *minibox, int exit_status)
{
	free_input_strings(minibox);
	free_matrix(minibox, -1);
	free_local_vars(minibox);
    exit(exit_status);
}
