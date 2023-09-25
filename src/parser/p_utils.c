/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:05:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/21 15:13:19 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_addback(t_token *head, char *token_v, int type)
{
	t_token	*new;
	t_token	*current;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token_value = token_v;
	new->type = type;
	if (!head)
		return (new);	
	current = head;
	while (current->next)
		current = current->next;
	current->next = new;
	return (head);	
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
			str++;
	return (str);		
}

bool	special_characters(char c, int i)
{	
	char	sp_chars[20];
	
	sp_chars[0] = '|';
	sp_chars[1] = '&';
	sp_chars[2] = '"';
	sp_chars[3] = '\'';
	sp_chars[4] = '>';
	sp_chars[5] = '<';
	sp_chars[6] = '$';
	sp_chars[7] = '{';
	sp_chars[8] = '}';
	sp_chars[9] = 0;
	
	if (!c)
		return (false);
	while (sp_chars[++i])
	{
		if (c == sp_chars[i])
			return (true);
	}
	return (false);
}
