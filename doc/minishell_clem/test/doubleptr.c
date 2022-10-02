#include <stdio.h>
#include <stdlib.h>

void	*wmalloc(size_t size, size_t len)
{
	void	*mem;

	mem = NULL;
	mem = malloc (size * len);
	return (mem);
}

void	stralter (char *s)
{
	s[0] = '1';
	s[1] = '2';
	s[2] = '3';
	s[3] = '\0';
}

int	main(void)
{
	char *str;

	str = wmalloc (sizeof(char), 3 + 1);
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';


	dprintf (2, "before: %s\n", str);
	stralter (str);
	dprintf (2, "after: %s\n", str);

	return (0);
}
