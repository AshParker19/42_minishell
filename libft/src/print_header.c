/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:57:11 by astein            #+#    #+#             */
/*   Updated: 2023/07/27 18:59:43 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief 	simple function that prints the char 'c' int 'amount' of times to the
 * 			standard output
 * 
 * @param c			char to be printed 
 * @param amount 	amount of times 'c' should be printed
 */
static void	print_n_times(char c, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
}

/**
 * @brief	prints a line like this
 * 
 * 				📭---------------------------------------------------📭
 * 
 * 			- the first and last symbol can be modified via 'symbol'
 * 			- the '-' char can be modified in the .h file via 'HEADER_SEP'
 * 
 * @param symbol
 */
static void	print_borders(char *symbol)
{
	ft_printf("%s", symbol);
	print_n_times(HEADER_SEP, HEADER_WIDTH);
	ft_printf("%s\n", symbol);
}

/**
 * @brief	prints a header like this
 * 
 * 				📭---------------------------------------------------📭
 * 				📭              ASTEINS MINITALK SERVER              📭
 * 				📭                (PID SERVER: 9057)                 📭
 * 				📭---------------------------------------------------📭
 * 
 * 			- the first and last symbol can be modified via the parm 'symbol'
 * 			- the message can be modified via the string 'msg'
 * 			- the '-' char can be modified in the .h file via 'HEADER_SEP'
 * 
 * @param symbol 
 * @param msg 
 */
void	put_header(char *symbol, char *msg)
{
	int		cur_line;
	char	**msg_lines;
	int		count_sep;

	print_borders(symbol);
	msg_lines = ft_split(msg, '\n');
	cur_line = 0;
	while (msg_lines[cur_line])
	{
		count_sep = HEADER_WIDTH - ft_strlen(msg_lines[cur_line]);
		ft_printf("%s", symbol);
		print_n_times(' ', count_sep / 2);
		ft_printf("%s", msg_lines[cur_line]);
		if (count_sep % 2 != 0)
			count_sep++;
		print_n_times(' ', count_sep / 2);
		ft_printf("%s\n", symbol);
		cur_line++;
	}
	free_whatever("a", msg_lines);
	print_borders(symbol);
	ft_printf("\n");
}

/**
 * @brief	prints a header *see function 'put_header' and in addition
 * 			terminates the programm.
 * 			the exit code can be set via 'exit_status"
 * 
 * @param exit_status	either EXIT_SUCCESS or EXIT_FAILURE
 * @param msg			defines the message of 'put_header'
 */
void	put_exit_header(int exit_status, char *msg)
{
	if (exit_status == EXIT_SUCCESS)
	{
		put_header("🟢", msg);
		exit(EXIT_SUCCESS);
	}
	else
	{
		put_header("❌️", msg);
		exit(EXIT_FAILURE);
	}
}
