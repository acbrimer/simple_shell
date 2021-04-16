# B.E.N.N.Y. Simple Shell

![](https://img.dog-learn.com/dog-breeds/cavalier-king-charles-spaniel/cavalier-king-charles-spaniel-sz14.jpg "Benny")

## Description

B.E.N.N.Y. Shell is a simple UNIX command interpreter, or a shell program that is used to send commands to computers. The name is an acronym for Best Ever iNteractive and noN-interactive Yes, referring to its capability to be used in both interactive and non-interactive mode.

B.E.N.N.Y. Shell (hereafter referred to as BENNY) is a command-line interpreter that serves as the interface between a user and that user's operating system. BENNY is a program designed to read characters that are input into the terminal, interpret them, and pass those commands to the operating system to execute.

Who's a good shell?

## Installation

### 1. Install

Clone BENNY into your system with the command:

```
git clone https://github.com/acbrimer/simple_shell.git
```

### 2. Compile

Compile BENNY with the command:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

### 3. Use

BENNY is now ready to use in either interactive or non-interactive mode. See below for details.

## Usage

### Interactive Mode

In interactive mode, the user can have ongoing interaction with BENNY. BENNY will provide a prompt that will remain until the user exits from this mode.

To enter interactive mode, start the BENNY program with "./hsh" if compiled as directed.

```
$ ./hsh
BENNY$ [desired command]
BENNY$ [BENNY's output]
BENNY$ exit
$
```

### Non-Interactive Mode

In non-interactive mode, the user can have a one-time interaction with BENNY.

To use BENNY in non-interactive mode, echo a command in double quotes and pipe it into BENNY with "./hsh" if compiled as directed.

```
$ echo "[desired command]" | ./hsh
$ [BENNY's output]
$
```

## Examples

__Interactive__

Run a command with:
```
$ ./hsh
BENNY$ ls
a.out    builtin.c          free_mem_fns.c      log_command.c  man_1_simple_shell  string.c
AUTHORS  error.c            get_command_path.c  log.txt        parse_command.c     strtow.c
benny.h  execute_command.c  getenv.c            main.c         README.md
BENNY$
```

Include the path with:
```
$ ./hsh
BENNY$ /bin/cat hello
Hello!
BENNY$
```

__Non-Interactive__

Pipe a command into BENNY with:
```
$ echo "ls" | ./hsh
AUTHORS  builtin.c          free_mem_fns.c      getenv.c  main.c              parse_command.c  setenv.c  strtow.c
benny.h  execute_command.c  get_command_path.c  itoa.c    man_1_simple_shell  README.md        string.c
$
```

Use multi-line commands with:
```
$ echo "ls
> ls -a" | ./hsh
AUTHORS  builtin.c          free_mem_fns.c      getenv.c  main.c              parse_command.c  setenv.c  strtow.c
benny.h  execute_command.c  get_command_path.c  itoa.c    man_1_simple_shell  README.md        string.c
.      AUTHORS    error.c            get_command_path.c  .gitignore     main.c              README.md
..     benny.h    execute_command.c  getenv.c            log_command.c  man_1_simple_shell  string.c
a.out  builtin.c  free_mem_fns.c     .git                log.txt        parse_command.c     strtow.c
$
```

## Features

- Zero memory leaks
- Custom env builtin command
- Custom exit builtin command
- Custom setenv builtin command
- Custom unsetenv builtin command
- Custom cd builtin command
- Custom _getenv function
- Custom _strtok function
- Ctrl-D exits the program
- Ctrl-C does not exit the program

## Structure

### Main Structure

##### main.c
- Prototypes:
  - void check_linelen(char *exename, char *cmdBuffer, int mode, int linelen);
  - void sigint_handler(int sig);
  - int main(int argc, char **argv);
#### parse_command.c
- Prototypes:
  - cmd_t *parse_command(char *cmd_str);
  - char *replace_char(char *str, char find, char replace);
#### execute_command.c
- Prototypes:
  - int execute_command(cmd_t *cmd, char *cmdBuffer, int linec, char *exename);
  - int check_file_exists(char *path);
  - void free_cmd_vars(cmd_t *cmd, char *cmd_path, char *cmdBuffer);

#### get_command_path.c
- Prototypes:
  - char **get_env_paths(void);
  - char *get_command_path(cmd_t *cmd);
  - char **add_pwd_to_paths(char *path, int pcount, char **env_paths);
#### free_mem_fns.c
- Prototypes:
  - char **free_str_array(char **arr);
  - void free_cmd_t(cmd_t *cmd);

### Builtin Functions

#### builtin.c
- Prototypes:
  - int builtin(cmd_t *cmd, char *cmdBuffer);
  - void exitFunction(cmd_t *cmd, char *cmdBuffer);
  - void printEnv(void);
#### getenv.c
- Prototypes:
  - char *_getenv(const char *name);
#### setenv.c
- Prototypes:
  - int _unsetenv(const char *name);
  - int _setenv(const char *name, const char *value, int overwrite);
  - int _strncmp(char *s1, char *s2, unsigned int n);
  - int f_error(char *err, int eno, cmd_t *cmd, int linec, char *exe, char *path);
### Helper Functions

#### strtow.c
- Prototypes:
  - char **_strtow(char *str, char delim);
  - char char *_strtok(char *str, int start, char delim);
  - int _charcount(char *str, char delim);
  - int _wordcount(char *str, char delim);
#### string.c
- Prototypes:
  - char *str_concat(char *s1, char *s2, char *delim);
  - int _strchr(char *s, char c);
  - int _strcmp(char *s1, char *s2);
  - char *_strdup(char *str);
  - int _strlen(char *s);
#### itoa.c
- Prototypes:
  - char *_itoa(int n);

### Library Functions limited to:

- access
- execve
- exit
- fork
- free
- getcwd
- getline
- isatty
- malloc
- perror
- stat
- waitpid

## Bugs

Yeah, probably.

## Authors

BENNY was written by Adam Brimer and Rachel Lewis. See AUTHORS page for more details.

## Links

A test suite for testing BENNY's capabilities can be found [here](https://github.com/Christopher-Caswell/simple_shell_test_suite).
