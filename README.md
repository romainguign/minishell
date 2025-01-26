# `minishell`

## 📋 Description
This project is a minimalist shell that can execute commands, manage environment variables and re-create some built-in commands.

It was developed as part of the 42 Angoulême curriculum. It has to respect the following rules:
- The project must be written in C language.
- The project must be normed.
- The project must be compiled with the flags `-Wall`, `-Wextra`, and `-Werror`.
- The project must be compiled with the Makefile.

## 🚀 Usage
To compile the project, run the following command:
```make```

To run the shell, run the following command:
```./minishell```

Then, you can run any command you want.



## 📦 Features

- Execute commands
- Manage environment variables
- Manage the PATH variable
- Manage the exit status of the last command
- Manage the redirections: `>`, `>>`, `<`
- Manage the pipes: `|`
- Manage the environment variables: `export`, `unset`
- Manage heredocs `<<`
- Manage the signals: `Ctrl-C`, `Ctrl-D`, `Ctrl-\`

## Exemple
```cat -e << EOF | grep "word" | wc -l > file.txt```
## 🛠️ Tools
- C language (execve, fork, waitpid, pipe, dup2, open, close, read, write, malloc, free, ...)
- Makefile

<br/>

Authors:
- **Brice, brguicho**
- **Romain, roguigna**