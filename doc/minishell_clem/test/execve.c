#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*argList[] = { "ls", "-l", NULL };

	if (execve("/bin/ls", argList, NULL) < 0)
		exit(EXIT_FAILURE);
}
