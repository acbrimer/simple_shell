#include "benny.h"

/**
 * parse_command - reads command string and returns struct
 * @cmd_str: command string
 *
 * Return: new cmd_t struct with info from string
*/

cmd_t *parse_command(char *cmd_str)
{
	char **cmd_arr = NULL;
	cmd_t *cmd = malloc(sizeof(cmd_t));

	/* replace tabs with spaces */
	replace_char(cmd_str, 9, ' ');
	/* skip leading spaces */
	while (*cmd_str == ' ')
		cmd_str++;
	/* split string into array on spaces */
	cmd_arr = _strtow(cmd_str, ' ');
	if (cmd == NULL)
		return (NULL);
	if (cmd_arr[0])
		cmd->cmd = _strdup(cmd_arr[0]);

	cmd->args = cmd_arr;

	return (cmd);
}

/**
 * replace_char - replaces find char with replace char in str
 * @str: string to replace chars
 * @find: char to find
 * @replace: char to replace find
 *
 * Return: pointer to string with replaced char
 */

char *replace_char(char *str, char find, char replace)
{
	int i;

	for (i = 0; str[i]; i++)
		if (str[i] == find)
			str[i] = replace;
	return (str);
}
