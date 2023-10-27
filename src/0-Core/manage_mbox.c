/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:14:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_box(t_mbox *minibox, char **env)
{
	minibox->env = env;
	minibox->vars = NULL;
	minibox->inp_orig = NULL;
	minibox->inp_trim = NULL;
	minibox->inp_shift = NULL;
	minibox->inp_expand = NULL;
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

void free_input_strings(t_mbox *minibox)
{
	if (minibox->inp_orig)
		free(minibox->inp_orig);
	if (minibox->inp_trim)
		free(minibox->inp_trim);
	if (minibox->inp_shift)
		free (minibox->inp_shift);
	if (minibox->inp_expand)
		free(minibox->inp_expand);
}

void free_tokens(t_mbox *minibox)
{
	t_token *cur;

	while(minibox->tokens)
	{
		cur = minibox->tokens;
		minibox->tokens = minibox->tokens->next;
		free(cur->value);
		free(cur);
	}
	minibox->tokens = NULL;
}

void free_cycle(t_mbox *minibox)
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
void free_and_close_box(t_mbox *minibox, int exit_status)
{
	free_input_strings(minibox);
	free_tokens(minibox);
	delete_ast(minibox->root);
	free_vars(minibox);
	free_executor(minibox);
    exit(exit_status);
}
