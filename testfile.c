#include "shell.h"

/**
 * main - request name from user
 *
 * Return: 0
 */

int main(void)
{
 char name[25];

 printf("Enter your name: \n");
 scanf("%s", name);

 printf("Hello %s\n", name);
 return (0);
}
