#include "shell.h"

/**
 * main - start function
 * @argcount: argument count
 * @argvector: argument vector
 * Return: 0=success, 1=error
 */
int main(int argcount, char **argvector)
{
        info_t information[] = { INFO_INIT };
        int filed = 2;

        asm ("mov %1, %0\n\t"
                "add $3, %0"
                : "=r" (filed)
                : "r" (filed));

        if (argcount == 2)
        {
                filed = open(argvector[1], O_RDONLY);
                if (filed == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(argvector[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(argvector[1]);
                                _eputchar('\n');
                                _eputchar(BUF_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                information->readfd = filed;
        }
        populate_env_list(information);
        read_history(information);
        hsh(information, argvector);
        return (EXIT_SUCCESS);
}
