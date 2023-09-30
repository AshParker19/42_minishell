/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:05:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/30 14:05:18 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int add_offset(int c)
{
	return(c - 126);
}

int remove_offset(int c)
{
	return(c + 126);
}

bool	ft_isqoute(char c)
{
	return (c == '\'' || c == '"');
}

bool	ft_issep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}
