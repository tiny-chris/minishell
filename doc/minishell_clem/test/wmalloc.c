#include <stdio.h>
#include <stdlib.h>

void	*wmalloc(size_t size, size_t len)
{
	void	*mem;

	mem = NULL;
	mem = malloc (size * len);
	return (mem);
}

int	main(void)
{
	char *str;

	str = wmalloc (sizeof(char), 3 + 1);
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';
	return (0);
}
