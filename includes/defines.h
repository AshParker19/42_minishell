/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:35:01 by astein            #+#    #+#             */
/*   Updated: 2023/11/11 21:43:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define SIGNAL_NEW_LINE 1
# define SIGNAL_EXIT_HD 2

# define NO_EXIT_STATUS -99999

/* promt strings */
// # define PROMPT      "\x1b[36mfrankenshell-->\033[0m "
// # define ERR_PROMPT  "\033[38;5;203mfrankenshell:\033[0m "
// # define HEREDOC_PROMPT "frankendoc> "

/* test prompts */
# define PROMPT "minishell:"
# define ERR_PROMPT "minishell: "
# define HEREDOC_PROMPT "> "

# define FRANKENSHELL_RISES_AMIDTS_DEATH 1

# define EXIT_STR_SUCCESS "0"
# define EXIT_STR_FAILURE "1"

# define MSG_SE_LT "syntax error near unexpected token `<'"
# define MSG_CD "cd: "
# define MSG_NO_PERM "Permission denied"


#endif