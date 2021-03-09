# Ush

Create a basic command-line interpreter with features without which there can be no shell. As a reference, you must take zsh. Your shell must: <br>
• have the default prompt must look like u$h> , followed by a space character <br>
• deal only with one line user input. In other cases, the appropriate descriptive error message must be displayed <br>
• implement builtin commands without flags: export, unset, exit, fg <br>
• implement the following builtin commands with flags: <br>
  – env with -i , -P , -u <br>
  – cd with -s , -P and - argument <br>
  – pwd with -L , -P <br>
  – which with -a , -s <br>
  – echo with -n , -e , -E <br>
• find builtins or flags in manuals to other shells if zsh hasn't got them <br>
• call the builtin command instead of the binary program if there is a name match among them <br>
• correctly manage errors <br>
• manage user environment correctly <br>
• run programs located in the directories listed in the PATH variable <br>
• manage signals CTRL+D , CTRL+C and CTRL+Z <br>
• implement the command separator ; <br>
• manage these expansions correctly: <br>
  – the tilde expansion ~ with the following tilde-prefixes: ~ , ~/dir_name , ~username/dir_name , ~+/dir_name , ~-/dir_name <br>
  – the basic form of parameter expansion ${parameter} <br>
  – the two-level-nested command substitution $(command) <br>
The purpose of this challenge is to learn the system APIs, so you are allowed to use any functions of the C POSIX library. This implies that you are forbidden to use any thirdparty libraries, except as expressly indicated in the story. If you need it, you must develop it and consider adding to your libmx for future use.
