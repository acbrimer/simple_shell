int is_path(char *s1)
{
	int i = 0;
	char *s2 = "PATH";

	while (s1[i])
	{
		if (s1[i] == '=')
			return (1);
		if (s1[i] != s2[i])
			break;
		i++;
	}

	return (0);
}

char **get_env_paths(char **envp)
{
	int i = 0, ii = 0;
	char *p = "PATH";
	char *path;

	/* loop through strings in envp to see if envp[i] is path */
	/* once envp[i] == path, split string on ':' after '=' */
	while (is_path(envp[i]) == 0)
		i++;
	path = envp[i];
	return (strtow((path + 5), ':'));
}
