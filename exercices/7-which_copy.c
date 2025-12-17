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
	int index = 0, path_count = 1;

	if (path == NULL)
		exit(1);
	*path_cpy = malloc((strlen(path) + 1) * sizeof(char));
	if (*path_cpy == NULL)
		exit(1);
	strcpy(*path_cpy, path);
	for (index = 0; path[index] != '\0'; index++)
	{
		if (path[index] == ':')
			path_count++;
	}
	path_array = malloc((path_count + 1) * sizeof(char *));
	if (path_array == NULL)
	{
		free(*path_cpy);
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
	char *path_cpy, **path_array, full_path[1024];
	struct stat av_stat;
	int index, stat_return = 1;

	if (ac != 2)
	{
		printf("Usage: %s path_to_file\n", av[0]);
		return (1);
	}
	path_array = get_path_array(&path_cpy);
	for (index = 0; path_array[index] != NULL && stat_return != 0; index++)
	{
		sprintf(full_path, "%s/%s", path_array[index], av[1]);
		stat_return = stat(full_path, &av_stat);
	}
	if (stat_return == 0)
		printf("Found: %s\n", full_path);
	else
		printf("Not Found\n");
	free(path_array);
	free(path_cpy);
	return (0);
}
