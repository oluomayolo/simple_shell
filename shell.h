#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int _exec(char **argc);
char *_getline();
char **tokenizer(char *cmd);

#endif
























