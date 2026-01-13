int	ftlib_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i] == s2[j] && (s1[i] != '\0' && s2[j] != '\0'))
	{
		i++;
		j++;
	}
	if (s2[j] == '\n')
		j++;
	return (s1[i] - s2[j]);
}