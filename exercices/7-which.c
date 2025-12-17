#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **get_path_array(char **path_cpy)
{
	char *path = getenv("PATH");
	char **path_array, *path_token;
	int index = 0, index_2, path_count = 1;

	if (path == NULL)
		exit(1);
	while (path[index] != '\0')
		index++;
	*path_cpy = malloc((index + 1) * sizeof(char));
	if (*path_cpy == NULL)
		exit(1);
	for (index = 0; path[index] != '\0'; index++)
	{
		if (path[index] == ':')
			path_count++;
		(*path_cpy)[index] = path[index];
	}
	(*path_cpy)[index] = '\0';
	path_array = malloc((path_count + 1) * sizeof(char *));
	if (path_array == NULL)
	{
		free(path_cpy);
		exit(1);
	}
	path_token = strtok(*path_cpy, ":");
	for (index = 0; path_token != NULL; index++)
	{
		path_array[index] = path_token;
		path_token = strtok(NULL, ":");
	}
	path_array[index] = NULL;
	return (path_array);
}

int main(int ac, char **av)
{
	char *path_cpy, **path_array;
	struct stat av_stat;

	if (ac < 2)
		return (1);
	path_array = get_path_array(&path_cpy);

	free(path_array);
	free(*path_cpy);
	return (0);
}
