/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 16:56:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   recursively traverses through the ll and
 * 			returns the amount of nodes in it
 * 
 * @param   env_var     
 * @return  int         
 */
static int	env_counter(t_env *env_var)
{
	if (!env_var)
		return (0);
	else
		return (1 + env_counter(env_var->next));
}

/**
 * @brief   uses simple bubble sort method to sort 'env_copy' alphabetically
 * 
 * @param   mbox        
 * @param   env_matrix  
 * @return  char**      
 */
static char	**bubble_sort(const t_mbox *mbox, char **env_matrix)
{
	int	sorted;
	int	i;
	int	env_count;

	env_count = env_counter(mbox->env) - 1;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = -1;
		while (++i < env_count - 1)
		{
			if (ft_strcmp(env_matrix[i], env_matrix[i + 1]) > 0)
			{
				ft_swap_strings(&env_matrix[i], &env_matrix[i + 1]);
				sorted = 0;
			}
		}
		env_count--;
	}
	return (env_matrix);
}

/**
 * @brief   uses 'env_counter' to determine the size of the 't_env' ll;
 * 			creates a matrix of the ll via 'env_to_matrix' and passes those
 * 			informations to 'bubble_sort' to sort the array.
 * 
 * @param   mbox        
 */
static void	sort_and_print_var(const t_mbox *mbox)
{
	char	**env_matrix;
	int		i;

	env_matrix = env_to_matrix(mbox, "\"");
	env_matrix = bubble_sort(mbox, env_matrix);
	if (!env_matrix)
		return ;
	i = -1;
	while (env_matrix[++i])
	{
		ft_putstr_fd("declare -x ", mbox->exec.io.cmd_fd[CMD_OUT]);
		ft_putendl_fd(env_matrix[i], mbox->exec.io.cmd_fd[CMD_OUT]);
	}
	free_whatever("m", env_matrix);
}

/**
 * @brief   responsible for 2 things:
 *              if doesnt have one 'arg_node'
 *                  sorts & prints the 't_env' ll via 'sort_and_print_var'
 *              else
 *                for each 'arg_node'
 * 	
 * 					CASE: NO EQUAL SIGN
 *						CASE: no equal sign & correct key (PATH)
 *							->ignores the arg / dont do nothing
 *						CASE: no equal sign & wrong key (@)
 *							-> export: `@': not a valid identifier
 * 
 * 					CASE: EQUAL SIGN
 *						CASE: correct (PATH=hello)
 *							->add/changes value in ll
 *						CASE: equal sign & wrong key (@=lol)
 *							-> export: `@=LL': not a valid identifier
 * 
 * DOUCMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#export
 * @param   arg_node 
 * @param   mbox 
 */
void	builtin_export(t_mbox *mbox, t_ast *arg_node)
{
	char	*equal_sign;
	t_bool	fnd_err;

	fnd_err = ft_true;
	if (!arg_node)
		sort_and_print_var(mbox);
	while (arg_node)
	{
		equal_sign = NULL;
		equal_sign = ft_strchr(arg_node->content, '=');
		if (equal_sign)
			case_equal_sign(mbox, arg_node, &fnd_err, equal_sign);
		else
			case_no_equal_sign(mbox, arg_node, &fnd_err);
		arg_node = arg_node->right;
	}
	if (fnd_err)
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
	else
		set_var_value_int(mbox, "?", EXIT_FAILURE);
}
