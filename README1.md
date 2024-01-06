
##### Heredoc
Here the official readme
->https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Here-Documents

In the heredoc var expansion also works!
The heredoc doenst consider qoutes at all, so there are no contextual quotes
So in generall all variables no matter the qoute state will expand!

Anyhow, if the LIM is put in either single or double qoutes like ```<< "LIM" cat```
var expansion is somehow suppressed. This is atm a huge problem since our code removes
all contextual qoutes so the heredoc function doesnt receive any information about
qoutes! Not sure how to fix!
Because we can not leave contextual qoutes in a all cases inside the args node because
in all other cases they need to be removed before execution!

Functions of \ $ ` 
\   is a flag that the next one will be ignored if its $ or `
        e.g. "Hi \$LESS" -> "HI $LESS"
    if its something else we print both
        e.g. "Hello W\orld" -> "Hello W\orld"

$   is just doint normal var expansion (if the LIM isnt in qoutes)

`   the strange qouted string will be executed! (if the LIM isnt in qoutes)
        e.g. "Hi `ls` World" -> "Hi libft Makefile minishell World"
        e.g. "Hi `cmdnotexist` World" -> "cmdnotexist: command not found \n Hi  World"

maybe the remove conte






HEREDOC EXIT AND SIGNALS

FUNCTION	CASE			RETURN VALUE	FD	EXIT STATUS	ERROR MSG
open		NORMAL FILE		42		42	-		NO
open		NO PERMISSION TO FILE	-1		-1	-		YES

heredoc		ended with LIM		0		PIPE	0		NO
heredoc		ended with CTRL C	130		PIPE	130		NO
heredoc		ended with CTRL D	0		PIPE	0		> bash: warning: here-document at line 21 delimited by end-of-file (wanted `lol')
