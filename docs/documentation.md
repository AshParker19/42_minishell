<a id="docu-top"></a>
<br />
<div align="center">
	<a href="../art.sh">
    	<img src="../images/logo.png" alt="Logo" width="224" height="300">
  	</a>
  	<h1 align="center">Documentation of frankenshell</h1>
</div>

<div style="text-align: center;">
  <a href="https://www.buymeacoffee.com/ahokcool" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"><br>
  </a>
    If this documentation is helpful for you, feel free to buy me a coffee ;)
	<br>
	<br>
</div>



#### Legend
 **:building_construction:	Section under construction!**<br>
 :book:						Link to another chapter<br>
 :top:						Link to top of the page / table of content<br>	
 :arrow_backward:			Link to previous chapter<br>
 :arrow_forward:			Link to this chapter<br>
 :computer:		 			Link to related.c file<br>
 :page_facing_up: 			Link to related.h file<br>
 :bulb:	 					Hint<br>
 :pencil2:					Example<br>
 :warning:					Warning / Important<br>
 :jigsaw:					Part of smth<br>
 




<br><h1 id="table-of-content">
	<a href="#docu-top">🔝 </a>
	<a href="#table-of-content">▶️ </a>
	Table of Contents
</h1>

1. [Introduction](#introduction)
1. [Installation](#installation)
1. [Usage](#usage)
	[[Info Mode](#info-mode)]
1. [Definitions](#definitions)
1. [Syntax](#syntax)
	[[Quotes](#quotes), 
	[Seperators](#seperators)]
1. [Structs](#structs)
	[[t_mbox](#t_mbox), 
	[t_env](#t_env), 
	[t_history](#t_history), 
	[t_token](#t_token), 
	[t_ast](#t_ast), 
	[t_list](#t_list), 
	[t_exec](#t_exec), 
	[t_io](#t_io), 
	[t_hd](#t_hd), 
	[t_builtin_cmd](#t_builtin_cmd)]
1. [Environment Variables](#environment-variables)
7. [Builtins](#builtin-commands)
	[[42](#42-builtin), 
	[cd](#cd-builtin), 
	[echo](#echo-builtin), 
	[env](#env-builtin), 
	[exit](#exit-builtin), 
	[export](#export-builtin), 
	[history](#history-builtin), 
	[pwd](#pwd-builtin), 
	[unset](#unset-builtin)]
1. [Exit Status](#exit-status)
2. [Signals](#signals)
1. [How frankenshell operates](#how-frankenshell-operates)
   1. [Initialization](#initialization)
    1. [Processing a cycle](#processing-a-cycle)
		1. [Trim Input](#trim-input),
		[Mark Empty Quotes](#mark-empty-quotes),
		[Shift Separators](#shift-separators),
		[Variable Expansion](#variable-expansion)
		2. [Tokenizing](#tokenizing)
		3. [Parsing](#parsing)
       	4. [Executing](#executing),
        [Setup Pipes](#setup-pipes),
        [Setup Redirections](#setup-redirections)
    	6. [Heredoc](#heredoc)
       	2. [Executing](#executeing)
   4. [Termination](#termination)
9. [Known Bugs](#known-bugs)
10. [Acknowledgments](#acknowledgments)


















### Readable Input String
To get a 'readable' Version of the input strings, their [shifted values](#shift-separators) will be displayed like:
- `S` for `'` (contextual single quote)
- `D` for `"` (contextual double quote)
- `P` for `|` (seperating pipe)
- `I` for `<` (redirection in)
- `O` for `>` (redirection out)
- `_` (space that can be removed)
- `E` ('empty token' flag to inform the tokenizer that it should generate an empty token)



TODO: UPDATE THE EXAMPLES SINCE I CHANGED THE DEBUG INFO LAYOUT
<details>
  <summary>Example <code>echo "Hello" $USER "" '!' | wc    -l&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</code></summary>

</details>

<details>
  <summary>Example <code>ls -l -a</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>ls -l -a

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(ls -l -a)

input trimmed:			(ls -l -a)

input shifted:	shifted:	(ls�-l�-a)
		readable:	(ls_-l_-a)
input expanded:	shifted:	(ls�-l�-a)
		readable:	(ls_-l_-a)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(ls)
type:(0) 	 token:(-l)
type:(0) 	 token:(-a)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

              [arg] (-a)

       [arg] (-l)

[cmd] (ls)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
total 288
drwxrwxr-x 10 astein astein   4096 Dez 16 23:04 .
drwxrwxr-x  3 astein astein   4096 Dez 15 14:03 ..
-rwxrwxr-x  1 astein astein   6323 Dez 15 20:15 art.sh
-rwxrwxr-x  1 astein astein   1498 Dez 15 20:03 count_stats.sh
drwxrwxr-x  3 astein astein   4096 Dez 15 20:03 docs
-rwxrwxr-x  1 astein astein 214360 Dez 16 23:04 frankenshell
drwxrwxr-x  8 astein astein   4096 Dez 17 01:58 .git
-rw-rw-r--  1 astein astein    215 Dez 15 20:03 .gitignore
drwxrwxr-x  2 astein astein   4096 Dez 17 01:44 images
drwxrwxr-x  2 astein astein   4096 Dez 15 20:03 includes
drwxrwxr-x  4 astein astein   4096 Dez 16 23:04 libft
-rw-rw-r--  1 astein astein   3841 Dez 15 20:30 Makefile
drwxrwxr-x  6 astein astein   4096 Dez 16 23:04 obj
-rw-rw-r--  1 astein astein   4768 Dez 16 23:14 README1.md
-rw-rw-r--  1 astein astein   2797 Dez 16 15:22 README.md
drwxrwxr-x  7 astein astein   4096 Dez 15 20:03 src
-rw-rw-r--  1 astein astein     46 Dez 16 18:08 todo.txt
drwxrwxr-x  2 astein astein   4096 Dez 15 20:22 .vscode
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

<details>
  <summary>Example <code>echo the home dir of $USER is storred in '$HOME'</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>echo the home dir of $USER is storred in &apos;$HOME&apos;

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(echo the home dir of $USER is storred in &apos;$HOME&apos;)

input trimmed:			(echo the home dir of $USER is storred in &apos;$HOME&apos;)

input shifted:	shifted:	(echo�the�home�dir�of�$USER�is�storred�in��$HOME�)
		readable:	(echo_the_home_dir_of_$USER_is_storred_in_`$HOME`)
input expanded:	shifted:	(echo�the�home�dir�of�astein�is�storred�in��$HOME�)
		readable:	(echo_the_home_dir_of_astein_is_storred_in_`$HOME`)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(echo)
type:(0) 	 token:(the)
type:(0) 	 token:(home)
type:(0) 	 token:(dir)
type:(0) 	 token:(of)
type:(0) 	 token:(astein)
type:(0) 	 token:(is)
type:(0) 	 token:(storred)
type:(0) 	 token:(in)
type:(0) 	 token:($HOME)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

                                                               [arg] ($HOME)

                                                        [arg] (in)

                                                 [arg] (storred)

                                          [arg] (is)

                                   [arg] (astein)

                            [arg] (of)

                     [arg] (dir)

              [arg] (home)

       [arg] (the)

[cmd] (echo)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
the home dir of astein is storred in $HOME
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

<details>
  <summary>Example <code><< $DONT_EXPAND cat | wc -l</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>&lt;&lt; $DONT_EXPAND cat | wc -l

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(&lt;&lt; $DONT_EXPAND cat | wc -l)

input trimmed:			(&lt;&lt; $DONT_EXPAND cat | wc -l)

input shifted:	shifted:	(���$DONT_EXPAND�cat���wc�-l)
		readable:	(II_$DONT_EXPAND_cat_P_wc_-l)
input expanded:	shifted:	(��$DONT_EXPAND�cat���wc�-l)
		readable:	(II$DONT_EXPAND_cat_P_wc_-l)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(2) 	 token:(&lt;)
type:(2) 	 token:(&lt;)
type:(0) 	 token:($DONT_EXPAND)
type:(0) 	 token:(cat)
type:(1) 	 token:(|)
type:(0) 	 token:(wc)
type:(0) 	 token:(-l)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

              [arg] (-l)

       [cmd] (wc)

[|] (|)

       [cmd] (cat)

              [&lt;&lt;] ($DONT_EXPAND)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 2)             |</font>
 <font color="#26A269">----------------------------------------</font>
<font color="#A2734C">frankendoc&gt; </font>
</pre>

</details>

<details>
  <summary>Example <code>echo hi"" "" "" ""there</code></summary>

<pre>╰─± ./frankenshell -i
 <font color="#A347BA">----------------------------------------</font>
<font color="#A347BA">|          INFO MODE ACTIVATED!          |</font>
<font color="#A347BA"> ----------------------------------------</font>
<font color="#2AA1B3">frankenshell--&gt; </font>echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there

 <font color="#FF5F5F">----------------------------------------</font>
<font color="#FF5F5F">|              INPUT STATES              |</font>
<font color="#FF5F5F"> ----------------------------------------</font>
input original:			(echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there)

input trimmed:			(echo hi&quot;&quot; &quot;&quot; &quot;&quot; &quot;&quot;there)

input shifted:	shifted:	(echo�hi�����������there)
		readable:	(echo_hiDD_E__E__DDthere)
input expanded:	shifted:	(echo�hi�����������there)
		readable:	(echo_hiDD_E__E__DDthere)
 <font color="#FF5F5F">========================================</font>

 <font color="#A2734C">----------------------------------------</font>
<font color="#A2734C">|               TOKENIZER                |</font>
<font color="#A2734C"> ----------------------------------------</font>
type:(0) 	 token:(echo)
type:(0) 	 token:(hi)
type:(0) 	 token:()
type:(0) 	 token:()
type:(0) 	 token:(there)
 <font color="#A2734C">========================================</font>

 <font color="#2AA1B3">----------------------------------------</font>
<font color="#2AA1B3">|                 PARSER                 |</font>
<font color="#2AA1B3"> ----------------------------------------</font>

                            [arg] (there)

                     [arg] ()

              [arg] ()

       [arg] (hi)

[cmd] (echo)
 <font color="#2AA1B3">========================================</font>

 <font color="#26A269">----------------------------------------</font>
<font color="#26A269">|                EXECUTOR                |</font>
<font color="#26A269">|             (cmd count: 1)             |</font>
 <font color="#26A269">----------------------------------------</font>
hi   there
 <font color="#26A269">========================================</font>

<font color="#2AA1B3">frankenshell--&gt; </font>
</pre>

</details>

:arrow_right: Refer to the section [Parsing](#parsing) for a better understanding of the ast.


























<br><h1 id="definitions">
	<a href="#table-of-content">🔝 </a>
	Definitions
</h1>






















<br><h1 id="syntax">
	<a href="#table-of-content">🔝 </a>
	Syntax
</h1>





















<br><h2 id="quotes">
	<a href="#table-of-content">🔝 </a>
	<a href="#syntax">◀️ </a>
	Quotes
</h2>



















<br><h2 id="seperators">
	<a href="#table-of-content">🔝 </a>
	<a href="#syntax">◀️ </a>
	Seperators
</h2>




















































<br><h1 id="environment-variables">
	<a href="#table-of-content">🔝 </a>
	▶️ Environment Variables
</h1>



















<br><h1 id="builtin-commands">
	<a href="#table-of-content">🔝 </a>
	▶️ Builtin Commands
</h1>

---

## 42 (builtin)



---

## cd (builtin)



---

## echo (builtin)



---

## env (builtin)



---

## exit (builtin)


## export (builtin)



## help (builtin)



---

## history (builtin)



---

## infomode (builtin)



## pwd (builtin)



## unset (builtin)































<br><h1 id="exit-status">
	<a href="#table-of-content">🔝 </a>
	▶️ Exit Status
</h1>

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


























<br><h1 id="signals">
	<a href="#table-of-content">🔝 </a>
	▶️ Signals
</h1>













<br><h1 id="how-frankenshell-operates">
	<a href="#table-of-content">🔝 </a>
	<a href="#how-frankenshell-operates">▶️ </a>
	How Frankenshell Operates
</h1>

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

The main task of frankenshell can be grouped into those steps:
- [Initialization](#initialization)
- Processing a Single Cycle
    - [Input Management](#processing-a-cycle)
    - [Execution](#execution)
- [Termination](#termination)

Below you can find a detailed description of each step.
> :page_facing_up:  The file ['input_management.c'](../src/0_core/input_management.c) calls all the input management functions.


<br>

## Initialization

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

On startup the program will initialize the [`t_mbox`](#t_mbox) struct. This struct contains all the information needed for the program to work. It is passed as an argument to most of the functions.\
The following steps are executed during initialization:
- creating a [t_env](#t_env) linked list for the [environment variables](#environment-variables)
- creating a [t_builtin_cmd](#t_builtin_cmd) array for the [builtin commands](#builtin-commands)
- ini

> :page_facing_up:  The file ['manage_mbox.c'](../src/0_core/manage_mbox.c) contains the functions for initializing and destroying the mbox instance.


<br>

### Processing a cycle

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

All the following steps are executed for each cycle.

| **Step** 										| **Example** |
| --------------------------------- 			| ----------- |
| Finished Reading    							| `echo "Hello" $USER "" '!' \| wc    -l     `          |
| [Trim Input](#trim-input)       				| `echo "Hello" $USER "" '!' \| wc -l`                  |
| [Mark Empty Quotes](#mark-empty-quotes) 		| `echo "Hello" $USER E_ '!' \| wc    -l`               |
| [Shift Separators](#shift-separators) 		| `echo_DHelloD_$USER_E__S!S_P_wc____-l`                |
| [Variable Expansion](#variable-expansion) 	| `echo_DHelloD_astein_E__S!S_P_wc____-l`               |
| [Tokenize](#tokenizing) 						| ![Example][token-table] 						        |
| [Parsing](#parsing) 							| ![Example][mindmap-ast-echo-hello-astein]				|

<!--
THIS TABLE IS IN THE TABLE ABOVE AS SCREENSHOT!
| Type | Value |
| ---- | ----- |
| WORD_TOKEN | `echo` |
| WORD_TOKEN | `Hello`	|
| WORD_TOKEN | `astein`	|
| WORD_TOKEN | ` `	|
| WORD_TOKEN | `!`	|
| PIPE_TOKEN | `|`	|
| WORD_TOKEN | `wc`	|
| WORD_TOKEN | `-l`	|
-->

---

#### Trim Input

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

First step is to trim the input. This means that all leading and trailing whitespaces are removed.
> :bulb:  Activate the [info mode](#info-mode) to see all input string states during runtime

---

#### Mark Empty Quotes

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

Bash generates an empty token for a pair of empty quotes if the two conditions are met:
- the empty quotes are not inside another pair of quotes\
(refer to `OUT_Q` as the [quote state](#quote-state))
- the empty quotes are surrounded by at least one whitespace character (or the beginning/end of the string) before and after 

Empty quotes will be marked as `EMPTY_TOKEN` and `NO_SPACE` characters.
```
# define NO_SPACE       -125
# define EMPTY_TOKEN    -126
```
> :arrow_right: Refer to the section [Shift Separators](#shift-separators) for a better understanding of the marked input string.

Examples
| inp_trim		        | inp_eq            | empty quotes      |
| ----------------------|-------------------|:-----------------:|
| `echo ""`			    | `echo E_`         | :white_check_mark:|
| `echo ''`			    | `echo E_`         | :white_check_mark:|
| `echo """"`			| `echo E___`       | :white_check_mark:|
| `echo "" "" "'hi"`    | `echo E_ E_ "'hi"`| :white_check_mark:|
| `echo hi""`			| `echo hi""`       | :x:               |
| `echo hi''`			| `echo hi''`       | :x:               |
| `echo ""hi`			| `echo ""hi`       | :x:               |
| `echo ''hi`			| `echo ''hi`       | :x:               |
| `echo '""'`			| `echo '""'`       | :x:               |
| `echo "''"`			| `echo "''"`       | :x:               |

> :arrow_right: Refer to the section [Readble Input String](#readable-input-string) for a better understanding of the marked input string.\
> :bulb: Activate the [info mode](#info-mode) to see all input string states during runtime

---

#### Shift Separators

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

To prepare the input string for the tokenizer all seperating characters need to be found. To mark them frankenshell shifts their ASCII value by `-126`. This makes an easy check for all of them possible (`ASCII < 0`) without loosing their original value. A seperating char needs to be outside of any quotes to be shifted.
Those are the characters which we consider as seperating characters:
- whitespace (` `, `\n`, `\t`, `\v`, `\a`, `\b`, `\f`, `\r`)
- pipe	(`|`)
- redirections (`<`, `>`)

Examples
| inp_trim		        | inp_eq		    | inp_shift         |
| ----------------------|-------------------|---|
| `echo "" "" "'hi"`    | `echo E_ E_ "'hi"`|  TODO |
| `echo hi""`			| `echo hi""`       |   |
| `echo hi''`			| `echo hi''`       |   |
| `echo ""hi`			| `echo ""hi`       |   |
| `echo ''hi`			| `echo ''hi`       |   |
| `echo '""'`			| `echo '""'`       |   |
| `echo "''"`			| `echo "''"`       |   |

###### Quote State

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

```
 * IDEA:
 * 		If somwehre at frankenshell we loop through the an input string
 * 		sometimes we need to know if we are inside or outside of contextual
 * 		quotes. This function updates the quote_state variable to the current
 * 		state of the quotes.
 * 
 * LOGIC:
 * 		if quote_state is OUT_Q (the cur_char is outside of contextual quotes)
 * 			if cur_char is a quote
 * 				update quote_state to the cur_char
 * 			else
 * 				quote_state stays OUT_Q
 *		else (the cur_char is inside of contextual quotes)
 * 			if matching quote is found
 * 				update quote_state to OUT_Q
 * 			else
 * 				quote_state stays the same          
```

While traversing the input string, the `quote state` will be updated for each character. So if a seperating character is found it will be only marked if the `quote state` is `OUT__QUOTE`  TODO LINK TO H FILE:
```
# define OUT_Q  0
```
TODO EMOJI Examples:
```
Trimmed String:	echo "Hello 'astein', how are you?"
Quote State: 	OOOOODDDDDDDDDDDDDDDDDDDDDDDDDDDDDO
Marked String:	echo DHello 'astein', how are you?D
Explanation:	The single quote is inside a double quote, so it will be ignored.
```

> :bulb:  Activate the [info mode](#info-mode) to see all input string states during runtime

---

### Variable Expansion

The [environment variable](#environment-variables) expansion works similar like in bash:

- Variable Expansion happens if the variable is **not** inside single [quotes](#quotes).
- Whitespaces inside the variable value will be [marked as `NO_SPACE` characters](#removal-of-whitespaces-of-expanded-variable-values). Therefore the [tokenizer](#tokenizing) can make multiple tokens out of it.
- If the variable is part of the [heredoc limiter](#extract-limiter) it won't be expanded! (e.g. `<< $USER cat`)

:bulb:  Activate the [info mode](#info-mode) to see the expanded input string states during runtime.

| Command           |  Valid Key 			| Expand       			| Output                        							|
| ------------------|   :------: 			| :----------: 			| ----------------------------- 							|
| `echo $USER`		| :white_check_mark:	| :white_check_mark:	| `astein`				      								|
| `echo "$USER"`    | :white_check_mark:	| :white_check_mark:	| `astein`				      								|
| `echo '$USER'`    | :white_check_mark:	| :x:	        		| `$USER`                   								|
| `<< $USER cat`    | N/A		 			| :x:	        		| Won't expand, so the `EOF` of the [heredoc](#heredoc) will be `$USER` 	|


<br>

---

#### Removal Of Whitespaces Of Expanded Variable Values


If there are whitespaces in the expanded Variable they will be marked as `NO_SPACE` characters.\
Therefore the tokenizer will make multiple tokens out of it.\
Quote Protection of whitespaces is not supported inside a variable. (like in bash)\
Example:
```
frankenshell--> export foo="Hello           World"
frankenshell--> echo $foo
Hello World
frankenshell--> export foo="Hello'        'World" //tries a quote protect of whitespaces
Hello' 'World                                     //doesn't work 
```

---

#### Extract Limiter

The variable expansion for a heredoc limiter is a special case.\
Variable Expension is not allowed inside a heredoc limiter!\
Anyhow there some strange rules for the determine the limiter:
| Case                  | Limiter <br> (send to tokenizer) | Explanation   | Limiter<sup> 1</sup> <br> (to exit hd)                           | Var. expansion <sup> 2</sup> <br> (inside heredoc) |
| ----                  | ---           | -----------                                                                       | -------     | :---:                                    |
| `<< $USER cat`        | `$USER`       |                                                                                   | `$USER`     | :white_check_mark:                        |
| `<< "FOO BAR" cat`    | `"FOO BAR"`   |                                                                                   | `FOO BAR`   | :x:                                       |
| `<< "$FOO $BAR" cat`  | `"$FOO $BAR"` |                                                                                   | `$FOO $BAR` | :x:                                       |
| `<< $'FOO' cat`       | `'FOO'`       |   `$` is followed by contextual `'`; <br> the `$` will be removed                 | `FOO`       | :x:                                       |
| `<< $"FOO" cat`       | `"FOO"`       |   `$` is followed by contextual `"`; <br> the `$` will be removed                 | `FOO`       | :x:                                       |
| `<< $"FOO"$"BAR" cat` | `"FOO""BAR"`  |   twice: <br> `$` is followed by contextual quotes; <br> the `$` will be removed  | `FOOBAR`    | :x:                                       |

<sup>1</sup> The contextual quotes will be removed by the [heredoc](#heredoc) function.\
<sup>2</sup> Different topic: Refer to the section [:book: heredoc](#heredoc) for the variable expansion **inside a heredoc**.

<br>

---

**:pencil2: Variable Expansion Examples (Special Cases)**
| Special Case			| Valid Key					  			| Expand 			| Explanation 												| Output (example)			|
|---------------		| :---:   					  			| :---:				|-------------												|--------------				|
| `echo $@ hi`			| :x:									| :x:				| first char of false key gets swallowed					| `hi` 						|
| `echo $@@ hi`			| :x:									| :x:				| first char of false key gets swallowed					| `@ hi` 					|
| `echo $1HOME`			| :x:									| :x:				| first char of false key gets swallowed					| `HOME` 					|
| `$`					| :x:									| :x:				| no key 													| `$: command not found`	|
| `echo $ hi`			| :x:									| :x:				| no key 													| `$ hi`	 				|
| `$?`					| :negative_squared_cross_mark:			| :white_check_mark:| [:book: exit status](#exit-status) of the last command 	| `42: command not found`	|
| `echo $?`				| :negative_squared_cross_mark:			| :white_check_mark:| [:book: exit status](#exit-status) of the last command 	| `42`						|	
| `echo $??`			| :negative_squared_cross_mark:			| :white_check_mark:| [:book: exit status](#exit-status) of the last command 	| `42?`						|	
| `echo $"USER"`		| :x:									| :x:				| the `"` block the key; <br> contextual quotes get removed	| `USER` 					|
| `echo "foo $'BAR'"`	| :x:									| :x:				| the `'` block the key; <br> contextual quotes get removed	| `foo $'BAR'` 				|
| `echo 'foo $"BAR"'`	| N/A									| :x:				| inside contextual quotes `'` -> no expansion				| `foo $"BAR"` 				|
| `echo 'foo $BAR'`		| N/A									| :x:				| inside contextual quotes `'` -> no expansion				| `foo $BAR` 				|
| `echo foo$USER$HOME`	| :white_check_mark: :white_check_mark:	| :white_check_mark: :white_check_mark:| the second `$` is not an allowed char of a key <br> therfore it terminates the first key. 										| `fooastein/home/astein`	|
| `echo foo $NOTEXIST bar`| :white_check_mark:					| :white_check_mark:| the key doesn't exist; <br> expands to NULL				| `a b`						|





---

### Tokenizing

The expanded input string will be tokenized. This means that the input string will be split into tokens. Each token will be marked with a type. The following token types exist:
```
enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	RED_IN_TOKEN,
	RED_OUT_TOKEN,
};
```

To generate the tokens first the input string will be splited into an array. Therefore the `NO_SPACE` character is used as an seperator. Then a loop will go through the array and generate the tokens. The following table shows the token generation logic:
| Logic | Example |
| ----- | ------- |
| check for forbidden spaces between redir symbols						| `< < file cat`	|
| if seperating characters in array entry (`\|`, `<`, `>`, `'`, `"`)	| `ls\|wc`			|
| &nbsp;&nbsp;&nbsp;&nbsp; if quote state == outside quotes									| `ls\|wc`			| 
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; create token with value: everything until next seperator found| token: `ls`		|
| &nbsp;&nbsp;&nbsp;&nbsp;else																| `"ls\|wc"`		|
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; create token with value: everything until matching quote found| token: `ls\|wc`	|
|else																	| `ls`				|
| &nbsp;&nbsp;&nbsp;&nbsp; create token with value: full array entry							| token: `ls`		|

> :bulb: Activate the [info mode](#info-mode) to see the token list during runtime

### Parsing

After tokienizing the input string, the tokens will be parsed into an AST. If the AST couldn't be build the input contains an syntax error (e.g. `ls | | wc`). If an vaild AST could be built it will be used for the execution.

Each node of the ast tree is an instance of the [t_ast](#t_ast) struct. It therefore has a type, a content and a two pointers to its left and right child node.

This table shows all possible node types and their possible node conections:
| Node Type | Left Child | Right Child |
| --------- | ---------- | ----------- |
| `PIPE`	| `CMD`		 | `PIPE` `CMD`|
| `CMD`     | `REDIR` `NULL`    | `ARG` `NULL`|
| `REDIR`	| `REDIR` `NULL`	| `NULL`      |
| `ARG`     | `NULL`     | `ARG` `NULL`|

To build a vaild AST we use the following logic (check out the BNF Notation):
```
 <job>          : <command> '|' <job>    
                | <command>              
                ;
 
 <command>      : <token list>           
				;
 
 <token list>   : [name]  <token list>   
                | [arg]   <token list>   
                | <redir> <token list>   
                ;
 
 <redir>        : <redir in> 
                | <redir out>
                ;
 
 <redir in>     : '<<' [file]
                | '<'  [file]
                ;
 
 <redir out>    : '>>' [file]
                | '>'  [file]
                ;
  			
```

The following ast is visualiszed in a tree-like structure (left to right):

![Example][mindmap-ast-png]

> :bulb: Activate the [info mode](#info-mode) to see the ast tree during runtime

> :bulb: The boolean `syntax_err_encountered` in the [t_mbox](#t_mbox) struct makes sure, that even if there are multiple errors, only the first error will be printed (like bash)
The possible syntax errors could be:
```
frankenshell: syntax error: unclosed quotes
frankenshell: syntax error near unexpected token `<'
frankenshell: syntax error near unexpected token `>'
frankenshell: syntax error near unexpected token `|'
frankenshell: syntax error near unexpected token `newline'
frankenshell: syntax error near unexpected token `foo'
```

### Executing

The execution of the ast is handled by the file TODO LINK TO FILE

**The execution may contain the following steps. Checkout those sections for more details about the execution steps:**
- [:book: setup command](#setup-command)
- [:book: setup redirections](#setup-redirections)
- [:book: setup heredoc](#setup-heredoc)
- [:book: run command](#run-command)


**Note**
- Before the execution starts a vaild ast must be created. 
	- If the ast couldn't be created the execution will be skipped.
- The executor traverses the ast tree always from **left to right**.
	- This ensures that pipes and redirections will always be setup before any command is executed.
- All commands are executed in a child process.
	- Exception: Single Builtin cmds (refer to bugs)
- Pipes (`|`) allow the output of one command to be used as input for another, enabling command chaining.
	- Note that the redirction into the pipe might be overwritten by the [redirection of the command itself](#setup-redirections).
- All childs will be spawn right after each other (so before the previous child terminates).
- The parent process waits (because of the open pipe fd) until the child process is finished.
	- Exception: Heredoc
	Before spawning a child process the parent process checks if the child includes a heredoc. In this case it waits unti the child is finished. (like bash) TODO EXAMPLE
- The parent waits for all childs to finish before it continues with the next cycle. Each time a child process is finished, the parent process updates the exit status of the last child process. (TODO check if this is true and link to chapter exit status).


**The [BPMN diagram](https://demo.bpmn.io/new) below shows the execution logic:**
<img src="../images/BPMN/bpmn-execute_ast.svg" alt="execution logic" width="1000">




#### Setup Command

Here the command will be setup. This means that a pipe<sup>*</sup> and a fork will be done. The child process will then [setup the redirections](#setup-redirections) and [run the command](#run-the-command).

<sup>*</sup> Exception: 'Single' or 'Last' Commands don't need a pipe!

**The [BPMN diagram](https://demo.bpmn.io/new) below shows the execution logic:**
<img src="../images/BPMN/setup_cmd.svg" alt="execution logic" width="1000">

#### Setup Redirections

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>

The table below describes the redirection features available in frankenshell:

Since there can be multiple redirections we need to keep track if one of them fails. Since bash only troughs one error. Example:
```
$: < file_not_exists < file_not_exists_2 cat
bash: file_not_exists: No such file or directory
```
| Feature| Mode            | Description                                                                                | Example                           |
|------|-------------|--------------------------------------------------------------------------------------------------|-----------------------------------|
| `<`  |Input Redirection         | Redirects input from a file to a command.                                           | `wc < file.txt`              |
| `<<` |Heredoc                   | Allows inputting multiple lines until a termination string is reached.              | `<< this_exits_the_hd wc`                  |
| `>`  |Output Redirection        | Redirects the output of a command to a file, overwriting it if it already exists.   | `echo "replace by foo" > file.txt`              |
| `>>` |Append Output Redirection | Appends command output to a file, creating it if it doesn't exist.                  | `echo "append foo" >> file.txt`

These redirections allow for flexible manipulation of command input and output, similar to standard bash functionality.

**The [BPMN diagram](https://demo.bpmn.io/new) below shows the execution logic:**
<img src="../images/BPMN/setup_redirs.svg" alt="execution logic" width="1000">


#### Setup Heredoc


The heredoc redirection allows inputting multiple lines until a termination string is reached or an EOF is sent via `CTRL+D`. The herdoc runs always in a child process and is connected to the command with a pipe. The herdoc uses `readline` to read the user input.



**The [BPMN diagram](https://demo.bpmn.io/new) below shows the execution logic:**
<img src="../images/BPMN/setup_hd.svg" alt="execution logic" width="1000">






###### Heredoc




:bulb: Variable Expansion inside the heredoc is supported!\
:warning: Like in bash: The expansion is not supposed to work if the limiter contains contextual quotes!\
:bulb: Therefore the [:book:  extract limiter](#extract-limiter) part of the [:book: variable expansion](#variable-expansion) obtains `'`,`"` and `$` characters.
REFERE TO SETUP HERDOC FOR MORE INFORMATION TODO


**This is the heredoc routine:**
1. The heredoc is setup by creating a pipe and forking a child process.
2. The Child Process...
	1. ...determines the heredoc `limiter` (aka EOF) by removing contextual quotes<sup>1</sup>

	2. ...closes the read end of the pipe
	3. ... starts an infinite **loop** that...
		- **reads** the user input via `readline`
		- **expands variables** in the read line<sup>1</sup>
		- **writes** the (expanded) line **to** the write end of the **pipe**
	4. ...**terminates** the loop if one of the following conditions is met:
		- line matches the limiter<sup>2</sup>
		- line matches EOF `CTRL+D`
		- `STDIN` was closed from the signal handler `CTRL+C`<sup>3,4</sup>
	5. ...close the write end of the pipe
	6. ...frees all memory anf updates the the **exit status** to
		- `0` if the heredoc was terminated by the `limiter`
		- `0` if the heredoc was terminated by EOF `CTRL+D`
		- `130` if the heredoc was terminated by the signal handler `CTRL+C`\
3. The Parent Process...
	1. ...closes the write end of the pipe
	2. ...waits for the child process to finish
	3. ...updates the **exit status** to the exit status of the hd child process
	4. ...checks how the hd hild process was terminated:
		- `CTRL+C`
			- closes the read end of the pipe
			- returns `false`
		- `EOF` or `limitter`
			- returns `true`


<sup>1</sup>:warning: If the limiter contains contextual quotes, variable expansion inside the heredoc will be disabled ([:book: extract limiter](#extract-limiter)).\
<sup>3</sup> Before expanison! The heredoc can't be terminated if the expanded input matches the limiter!\
<sup>3</sup> Checked via the global variable: `g_signal_status == SIGNAL_EXIT_HD`\
<sup>4</sup> ```frankenshell: warning: frankendoc at line 1 delimited by end-of-file (wanted `foo')```


EXAMPLES
```
<< foo cat
Hello
World
foo
...

e.g. << -R cat
 * 					   > asd
 * 					   > $LESS (this expands to -R but doens't exit the heredoc)
 * 					   > -R

```




#### Run Command


**The [BPMN diagram](https://demo.bpmn.io/new) below shows the execution logic:**
<img src="../images/BPMN/run_cmd_main.svg" alt="execution logic" width="1000">


### Termination

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


<br>

<br><h1 id="known-bugs">
	<a href="#table-of-content">🔝 </a>
	<a href="#known-bugs">▶️ </a>
	Known Bugs
</h1>

**export vs env**

If the built-in export is called with a valid key but no equal sign (like `export foo`) `foo` should be listed in the output of the `export`, but not in the output of the `env` function call. In frankenshell, `foo` is not added to the linked list of variables and therefore is not printed in either case. A simple boolean in the `s_env` structure could solve the problem.

---

**single cmds with redirs**
Since frankenshell doesn't fork for a single builtin cmd like `echo foo > out` it changes the fds of the main process. This might affect the next cycle since the fds are not reseted.

---












































<!-- MARKDOWN LINKS & IMAGES -->
[example-gif]: 						/images/example.gif
[mindmap-ast-png]: 					/images/mindmap-ast.png
[mindmap-ast-echo-hello-astein]: 	/images/mindmap-ast-echo-hello-astein.png
[token-table]: 						/images/token-table.png