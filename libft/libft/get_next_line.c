/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:41:07 by nfour             #+#    #+#             */
/*   Updated: 2024/04/12 09:30:33 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int     ft_strlen_gnl(const char *s)
{
        int     i;

        i = 0;
        if (!s)
                return (i);
        while (s[i])
                i++;
        return (i);
}

static int     ft_search_end(char *line)
{
        int     i;

        i = 0;
        while (line && line[i])
        {
                if (line[i] == '\n')
                        return (0);
                i++;
        }
        return (1);
}

char    *ft_strjoin_gnl(char *s1, char *s2)
{
        int             len_new_s;
        char    *new_s;
        int             i;
        int             j;

        len_new_s = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
        new_s = malloc((len_new_s + 1) * sizeof(char));
        if (!new_s)
        {
                free(s1);
                return (NULL);
        }
        i = 0;
        while (s1 && s1[i])
        {
                new_s[i] = s1[i];
                i++;
        }
        j = 0;
        while (s2[j] && i < len_new_s)
                new_s[i++] = s2[j++];
        free(s1);
        new_s[i] = '\0';
        return (new_s);
}

static char    *ft_read_fd(int fd, char *first)
{
        char    *read_s;
        int             nb_read;
        int             flag_end;

        flag_end = 1;
        read_s = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!read_s)
                return (NULL);
        while (ft_search_end(first) == 1 && flag_end == 1)
        {
                nb_read = read(fd, read_s, BUFFER_SIZE);
                if (nb_read < 0)
                {
                        free(read_s);
                        return (NULL);
                }
                if (nb_read < BUFFER_SIZE)
                        flag_end = 0;
                read_s[nb_read] = '\0';
                first = ft_strjoin_gnl(first, read_s);
        }
        free(read_s);
        return (first);
}

static char    *ft_get_line(char *joined)
{
        int             i;
        int             j;
        char    *line;

        i = 0;
        while (joined[i] && joined[i] != '\n')
                i++;
        line = malloc(sizeof(char) * (i + 2));
        if (!line)
                return (NULL);
        j = 0;
        while (j <= i)
        {
                line[j] = joined[j];
                j++;
        }
        line[j] = '\0';
        return (line);
}

char    *get_next_line(int fd)
{
        char            *joined;
        char            *line;
        char            *first;

        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        first = NULL;
        joined = ft_read_fd(fd, first);
        if (!joined)
                return (NULL);
        if (joined[0] == '\0')
        {
                free(joined);
                return (NULL);
        }
        line = ft_get_line(joined);
        free(joined);
        return (line);
}
