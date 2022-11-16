#include "shell.h"

/**
 * _getline - reads an entire line from stdin
 *
 * Return: On success, returns the address of the buffer with the text.
 *
 */
char *_getline()
{
	char *cmd = NULL;
	size_t n = 72;

	getline(&cmd, &n, stdin);

	return (cmd);
}

/**
 * *tokenizer - function that breaks  a string into a sequence of tokens.
 * @cmd:string to be parsed[tokenized]
 *
 * Return: On success, returns an array of pointers
 */

char **tokenizer(char *cmd)
{
	char *del = " \n\t\r";
	char **argv = malloc(sizeof(char *));
	int i = 0;
	int capacity = 32;
	char *token = strtok(cmd, del);

	while (token)
	{
		argv[i] = token;
		i++;

		if (i >= capacity)
		{
			capacity = (int)(capacity * 1.5);
			argv = realloc(argv, capacity * sizeof(char *));
		}

		token = strtok(NULL, del);
	}

	argv[i] = NULL;
	return (argv);
}

/**
 * _exec - function that executes a program
 * @argv: array of pointers
 *
 * Return: On success, zero in the child process, pid of the child
 * in the parent process,and a negative value on failure.
 */

int _exec(char **argv)
{
	int status;
	pid_t pid;
	char cwd[60];

	if ((_strcmp(argv[0], "exit")) == 0)
	{
		exit(EXIT_SUCCESS);
	}

	if ((_strcmp(argv[0], "cd")) == 0)
	{
		if (chdir(argv[1]) != 0)
			write(1, ":( cd: missing argument\n", 25);
	}

	if ((_strcmp(argv[0], "pwd")) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror(":( pwd error");
		else
			write(1, cwd, strlen(cwd));
		write(1, "\n", 2);
	}
	pid = fork();

	if (pid == 0)
	{
		execve(argv[0], argv, NULL);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
	}
	else
	{
		perror(" Failed");
	}
	return (1);
}

/**
 * main - an infinite loop
 *
 * Return: zero on success
 */
int main(void)
{
	char *cmd;
	char **tokens;

	while (true)
	{
		write(1, ":) ", 4);

		cmd = _getline();

		tokens = tokenizer(cmd);

		if (tokens[0] != NULL)
		{
			_exec(tokens);
		}
		free(tokens);
		free(cmd);
	}
	return (0);
}
