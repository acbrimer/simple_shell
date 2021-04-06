# Simple Shell

## Files
### Main structure
#### main.c
- Prototypes:
  - `int main(int argc, char **argv, char **envp);`
#### log_command.c
- Prototypes:
  - `int log_cmd(const char *logfile, char *cmd, size_t cmd_len);`
#### parse_command.c
- Prototypes:
  - `cmd_t *parse_command(char *cmd_str);`
#### get_command_path.c
- Prototypes:
  - `int is_path(char *envp_str);`
  - `char **get_env_paths(char **envp);`
  - `char *get_command_path(cmd_t cmd, **envp);`
#### get_command_fn.c
- Prototypes:
  - `int (*get_command_fn(cmd_t cmd))(cmd_t);`
#### execute_command.c
- Prototypes:
  - `int execute_command(cmd_t cmd);`
  - `void handle_command_error(cmd_t cmd);`
### Builtin functions
#### builtin_cd.c
- Prototypes:
  - `void _cd(cmd_t cmd);`

### Helper functions
#### strtok.c
- Prototypes:
  - `char **_strtow(char *str, char delim);`
  - `char char *_strtok(char *str, int start, char delim);`
  - `int _charcount(char *str, char delim);`
  - `int _wordcount(char *str, char delim)`

