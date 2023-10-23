/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_minibox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/23 16:20:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_box(t_minibox *minibox, char **env)
{
	minibox->env = env;
	minibox->vars = NULL;
	minibox->input_original = NULL;
	minibox->input_trimmed = NULL;
	minibox->input_quoted = NULL;
	minibox->input_expanded = NULL;
	minibox->error_status = false;
	minibox->tokens = NULL;
	minibox->root = NULL;
	minibox->tmp_token = NULL;
	minibox->tmp_node = NULL;
}
// void	free_matrix(char **matrix, int i)
// {
// 	if (matrix)
// 	{
// 		while (matrix[++i])
// 			free (matrix[i]);
// 		free (matrix);		
// 	}
// }

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

void free_tokens(t_minibox *minibox)
{
	t_token *current;

	while(minibox->tokens)
	{
		current = minibox->tokens;
		minibox->tokens = minibox->tokens->next;
		free(current->value);
		free(current);
	}
	minibox->tokens = NULL;
}

void free_cycle(t_minibox *minibox)
{
    free_input_strings(minibox);    
    free_tokens(minibox);
    minibox->tokens = NULL;
    delete_ast(minibox->root);
    minibox->root = NULL;
	free_process(minibox);
	if (minibox->executor.pid)
	{
		free (minibox->executor.pid);
		minibox->executor.pid = NULL;
	}
	dbg_printf(no_block, "FREED CYCLE READY TO GO AGAIN!\n");
}

// TODO:
// Function should check all members of the minibox struct 
// and frees them if they are inizialised
// exits program
void free_and_close_box(t_minibox *minibox, int exit_status)
{
	free_input_strings(minibox);
	free_tokens(minibox);
	delete_ast(minibox->root);
	free_vars(minibox);
	free_executor(minibox);
    exit(exit_status);
}
