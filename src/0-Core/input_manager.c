/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/02 12:23:26 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_tree *root);
void	add_token(t_minibox *minibox, char *value, int type);

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
        // tokenize(minibox, 0);
        minibox->tokens = NULL;
        add_token(minibox, "ls", TEXT_TOKEN);
        add_token(minibox, "-l", TEXT_TOKEN);
        add_token(minibox, "-a", TEXT_TOKEN);
        parse(minibox);
        print_parser_output(minibox->root);
    }

    // somehow call something to execute everything

    // free
    //  input_original, input_trimmed, input_expanded, .....
    free_input_strings(minibox);    
}
