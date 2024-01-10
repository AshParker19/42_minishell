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


<br>

## Initialization

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>



> :page_facing_up:  The file ['manage_mbox.c'](../src/0_core/manage_mbox.c) contains the functions for initializing and destroying the mbox instance.


<br>

### Processing a cycle

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


---

#### Trim Input

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>



---

#### Mark Empty Quotes

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


---

#### Shift Separators

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


###### Quote State

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


---

### Variable Expansion





---

### Tokenizing



### Parsing



### Executing





#### Setup Command



#### Setup Redirections

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>








###### Heredoc






#### Run Command


### Termination

**:warning: :building_construction:	Documentation under construction! :warning: :building_construction:**<br>


<br>

<br><h1 id="known-bugs">
	<a href="#table-of-content">🔝 </a>
	<a href="#known-bugs">▶️ </a>
	Known Bugs
</h1>

---












































<!-- MARKDOWN LINKS & IMAGES -->
