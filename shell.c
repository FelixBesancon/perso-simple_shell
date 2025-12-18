#include "shell.h"

ssize_t read_line(char **line, size_t *buffer)
{
	ssize_t len;

	len = getline(line, buffer, stdin);

	if (len > 0 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	return (len);
}

char **parse_line(char *line, int *argc)
{
	int index;
	char **argv = NULL;
	char *token = NULL, line_cpy;

	argv = malloc((len + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	line_cpy = strdup()
	token = strtok(line, " \n\t");
	for (index = 0; token != NULL; index++)
	{
		argv[index] = token;
		token = strtok(NULL, " \n\t");
	}
	argv[index] = NULL;
	*argc = index;
	return (argv);
}

int main(int ac, char **av, char **env)
{
	int argc;
	pid_t PID;
	char **argv = NULL;
	char *line = NULL;
	size_t buffer = 0;
	ssize_t len;

	(void)ac;
	(void)av;
	while (1)
	{
		printf("#shell$ ");

		len = read_line(&line, &buffer);
		if (len == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}
		argv = parse_line(line, &argc);
		
		if (argv == NULL)
		{
			free(line);
			exit(1);
		}
		
		if (argv[0] != NULL)
		{
			PID = fork();
			if (PID == -1)
			{
				perror("./shell");
				free(argv);
				free(line);
				return (1);
			}
			if (PID == 0)
			{
				execve(argv[0], argv, env);
				perror("./shell");
				exit(1);
			}
			else
				wait(NULL);
		}
		free(argv);
	}
	free(line);
	return (0);
}
