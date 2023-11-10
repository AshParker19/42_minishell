/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:01:34 by astein            #+#    #+#             */
/*   Updated: 2023/05/18 17:13:26 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function takes af file descriptor 'fd' and reads it line by
 * 			line. Each time you call it, will return the next line.
 * 			The BUFFE_SIZE is specified in the .h file but can be overwritten
 * 			during compiling with: '-D BUFFER_SIZE=foo'
 * 
 * 			The function DOES remember which fd you passed during the last call.
 * 			So you can use it with multiple files simultaneously.
 * 				
 * @param	fd		The file descriptor from which to read
 * @return	char*
 * 					The next line (including the \n)
 * 					NULL if no next line exists
 */
char	*gnl(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	size_t		len_line;
	size_t		len_cpy;
	t_bool		flg_nl;

	line = NULL;
	len_line = 0;
	len_cpy = 0;
	flg_nl = ft_false;
	if (fd < 0 || fd > FOPEN_MAX || !BUFFER_SIZE)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (gnl_zero_str(buffer[fd]));
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		gnl_len_nl(line, &len_line, &flg_nl);
		gnl_len_nl(buffer[fd], &len_cpy, &flg_nl);
		line = gnl_safe_buffer(line, len_line, buffer[fd], len_cpy);
		gnl_shift_arr_to_front(buffer[fd], len_cpy);
		if (flg_nl)
			break ;
	}
	return (line);
}

/**
 * @brief 	Same then 'gnl' but it will stop if the parameter 'stop' is set to
 * 			ft_true
 * 
 * @param	fd		The file descriptor from which to read
 * @param	stop 	THIS BOOLEAN CAN STOP THIS FUNCTION!
 * @return	char* 	read line
 */
char	*gnl_stoppable(int fd, t_bool *stop)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	size_t		len[2];
	t_bool		flg_nl;

	line = NULL;
	len[0] = 0;
	len[1] = 0;
	flg_nl = ft_false;
	if (fd < 0 || fd > FOPEN_MAX || !BUFFER_SIZE)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (gnl_zero_str(buffer[fd]));
	while ((buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0) && !*stop)
	{
		gnl_len_nl(line, &len[0], &flg_nl);
		gnl_len_nl(buffer[fd], &len[1], &flg_nl);
		line = gnl_safe_buffer(line, len[0], buffer[fd], len[1]);
		gnl_shift_arr_to_front(buffer[fd], len[1]);
		if (flg_nl || *stop)
			break ;
	}
	if (*stop)
		return (NULL);
	return (line);
}
