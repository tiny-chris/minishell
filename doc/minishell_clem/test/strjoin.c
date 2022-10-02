#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
		ptr++;
	return ((size_t)(ptr - s));
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*ptr;

	if (!s1)
		return (NULL);
	s2 = malloc (sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	ptr = s2;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = *s1;
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[(size_t)i + ft_strlen(s1)] = s2[i];
	str[(size_t)i + ft_strlen(s1)] = '\0';
	return (str);
}

/* char	*temp; */

/* temp = s2; */
/* s2 = ft_strjoin(s1, s2); */
/* if (temp) */
/* { */
/* 	free(temp); */
/* 	temp = NULL; */
/* } */
/* } */

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp1;
	char	*temp2;
	char	*s3;

	temp1 = s1;
	temp2 = s2;
	s3 = ft_strjoin(s1, s2);
	if (temp1)
	{
		free(temp1);
		temp1 = NULL;
	}
	if (temp2)
	{
		free(temp2);
		temp2 = NULL;
	}
	return (s3);
}

int	main(void)
{

	///////////////////
	//// EXAMPLE 1 ////
	///////////////////

	char *s1 = ft_strdup("salut");
	char *s2 = ft_strdup(" ");
	char *s3 = ft_strdup("super-man");
	char *s4 = ft_strdup(" ");
	char *s5 = ft_strdup("éla");

	s1 = ft_strjoin_free(s1, s2);
	s1 = ft_strjoin_free(s1, s3);
	s1 = ft_strjoin_free(s1, s4);
	s1 = ft_strjoin_free(s1, s5);

	// On a tout join en un minimum de lignes et sans leaks
	// la contrepartie c'est de ne plus pouvoir utiliser s2,3,4..
	// comme ils ont été free au fur et à mesure.

	dprintf(2, "1) %s\n", s1);

	// et pour enfin on free s1
	free(s1);

	///////////////////
	//// EXAMPLE 2 ////
	///////////////////

	// Si on avait utilisé ft_strjoin on aurait du faire quelque chose comme ça:
	s1 = ft_strdup("salut");
	s2 = ft_strdup(" ");
	s3 = ft_strdup("super-man");
	s4 = ft_strdup(" ");
	s5 = ft_strdup("éla");
	char *temp1;
	char *temp2;

	temp1 = s1;
	temp2 = s2;
	s1 = ft_strjoin(s1, s2);
	if (temp1)
		free(temp1);
	if (temp2)
		free(temp2);

	temp1 = s1;
	temp2 = s3;
	s1 = ft_strjoin(s1, s3);
	if (temp1)
		free(temp1);
	if (temp2)
		free(temp2);

	temp1 = s1;
	temp2 = s4;
	s1 = ft_strjoin(s1, s4);
	if (temp1)
		free(temp1);
	if (temp2)
		free(temp2);

	temp1 = s1;
	temp2 = s5;
	s1 = ft_strjoin(s1, s5);
	if (temp1)
		free(temp1);
	if (temp2)
		free(temp2);

	// Ici on a utilisé la même méthode que l'example 1
	// mais sans utiliser de fonction, c'est donc plus long
	// mais on peut choisir si on veut free s1 ou s2 ou les deux
	// si jamais s1 ou s2 est une string pas malloc etc.
	// D'ou mes 3 fonctions utils (strjoin_free: s1, s2 ou les deux)

	dprintf(2, "2) %s\n", s1);

	// et pour enfin on free s1
	free(s1);
}
