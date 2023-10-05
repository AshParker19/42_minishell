/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 20:56:00 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_minibox *minibox);

// dealing with everything thats before exection
void	manage_input(t_minibox *minibox)
{
    add_history(minibox->input_original);
    // printf ("minibox->input_original:\t%s\n", minibox->input_original);
    minibox->input_trimmed = ft_strtrim(minibox->input_original, " \n\t\v");
    // printf ("minibox->input_trimmed:\t\t%s\n", minibox->input_trimmed);
    mark_seps(minibox, 0, 0);
    // printf ("minibox->input_quoted:\t\t%s\n", minibox->input_quoted);
    expand_variables(minibox, 0, 0, OUT_Q);
    printf ("minibox->input_expanded:\t%s\n", minibox->input_expanded);
    if (ft_strlen(minibox->input_expanded) != 0)
    {
        if (ft_strlen(minibox->input_expanded) == 4 && !ft_strncmp(minibox->input_expanded, "exit", 4))
        {
            printf("Bye Bye fuckers!\n");
            // Deal with exit satus!
            free_and_close_box(minibox, -1);
        }
        tokenize(minibox, 0);
        parse(minibox);
        print_parser_output(minibox);
    }

    // somehow call something to execute everything

    // free
    //  input_original, input_trimmed, input_expanded, .....
    free_input_strings(minibox);    
    free_tokens(minibox);
    minibox->tokens = NULL;
    delete_ast(minibox->root);
    minibox->root = NULL;
}
