/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:38:51 by lspohle           #+#    #+#             */
/*   Updated: 2023/01/11 15:04:55 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Returns the number of characters that precede the terminating NULL
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// Allocates and returns a substring from the string given as argument
// The substring begins at index start and is of size len
// Returns the substring
// Returns NULL if allocation fails
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (ft_strlen(s) == 0)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	sub = (char *) malloc ((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (len-- != 0 && start < (unsigned int) ft_strlen(s))
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

// Locates the first occurrence of c in s
// The terminating null character is considered to be part of the string
// Returns a pointer to the located character
// Returns NULL if the character does not appear in the string
char	*ft_strchr(const char *s, int c)
{
	char			char_c;
	char			*char_s;
	size_t			i;

	char_c = (char) c;
	char_s = (char *) s;
	i = -1;
	while (char_s[++i] != '\0')
		if (char_s[i] == char_c)
			return (&char_s[i]);
	if (char_s[i] == char_c)
		return (&char_s[i]);
	return (NULL);
}

// Allocates and returns a “fresh” string ending with ’\0’
// Returns the concatenation of s1 and s2
// Returns NULL if allocation fails
char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*output;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	output = (char *) malloc ((ft_strlen(s1)+ft_strlen(s2)+1) * sizeof(char));
	if (!output)
		return (NULL);
	i = -1;
	while (s1 != NULL && s1[++i])
		output[i] = s1[i];
	j = -1;
	while (s2 != NULL && s2[++j])
		output[i++] = s2[j];
	output[i] = '\0';
	return (output);
}

// Allocates enough space for count objects that are size bytes of memory each
// Allocated memory is filled with bytes of value zero
// Returns a pointer to the allocated memory
// Returns a NULL pointer and sets errno to ENOMEM
void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*mem;

	mem = malloc (count * size);
	if (mem == 0)
		return (0);
	i = -1;
	while (++i < (size * count))
		((char *)mem)[i] = '\0';
	return (mem);
}
