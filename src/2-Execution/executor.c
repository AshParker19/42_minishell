/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 20:53:00 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    run_cmd_main(t_minibox *minibox, t_tree *cmd_node, int status)
{
    int builtin_cmd_index;
    (void)status;
    
    builtin_cmd_index = check_if_builtin(minibox, cmd_node->content);
    if (builtin_cmd_index != -1)
        run_cmd_builtin(minibox, cmd_node, builtin_cmd_index);
    else
        run_cmd_system(minibox, cmd_node);
}

void    setup_io(t_minibox *minibox, int status)
{
    initialize_io(minibox);
    setup_use_pipe(minibox, status);
    minibox->executor.io.redir = minibox->root->left;
}


void exec_cmd(t_minibox *minibox, t_tree *node, int status)
{
    (void)minibox;
    (void)node;
    (void)status;
    // char    *cmd;

    // // TODO: check for builtin
    
    // setup_io(minibox, status);
    // get_cmd_av(minibox, node);
    // cmd = get_cmd_path(minibox, node->content, -1);
    // if (minibox->executor.cmd_av[0])
    //     free(minibox->executor.cmd_av[0]);
    // minibox->executor.cmd_av[0] = cmd;
    // setup_redir(minibox);
    // // TODO: fork
    // execve(minibox->executor.cmd_av[0], minibox->executor.cmd_av, minibox->env);
    // // TODO:check if execve changes env, if yeas we need to reload the LL
    // perror("Poop");
    
    // // while (minibox->executor.cmd_av[i])
    // // {
    // //     printf("%s\n", minibox->executor.cmd_av[i]);
    // //     i++;
    // // }
    // // if (minibox->executor.io.redir)
    // //     printf("Redir: %s\n", minibox->executor.io.redir->content);
}

static void setup_cmd(t_minibox *minibox, t_tree *cmd_node, int status)
{
    int builtin_cmd_index;
    
    // check if only single buiiltin
    builtin_cmd_index = check_if_builtin(minibox, cmd_node->content);
    if (status == SINGLE_CMD && builtin_cmd_index != -1)
        run_cmd_builtin(minibox, cmd_node, builtin_cmd_index); //TODO: exit status?
    else
    {
        // else all the other cases
        // setup_pipe 
    	// setup_redir
    	// fork (if nessesary)
    	run_cmd_main(minibox, cmd_node, status);
    	// in parent process
		// wait() and catc
        
    }


    
    initialize_io(minibox);
    
}



void    execute(t_minibox *minibox)
{
    t_tree  *cur_node;
    
    if (minibox->root->type == CMD_NODE)
        setup_cmd(minibox, minibox->root, SINGLE_CMD);
    else
    {
        setup_cmd(minibox, minibox->root->left, FIRST_CMD);
        cur_node = minibox->root;
        while(cur_node->right && (cur_node->type == PIPE_NODE))
        {
            setup_cmd(minibox, cur_node->left, MIDDLE_CMD);
            cur_node = cur_node->right;
        }
        setup_cmd(minibox, cur_node,  LAST_CMD);
    }
}
