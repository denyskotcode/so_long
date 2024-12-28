#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

size_t  fft_strlen(const char *s);
char    *fft_strchr(const char *s, int c);
char    *fft_strjoin(const char *s1, const char *s2);
char    *fft_substr(const char *s, unsigned int start, size_t len);

static char *extract_line(const char *stored)
{
    size_t i = 0;
    char *line;
    if (!stored || !stored[0])
        return NULL;
    while (stored[i] && stored[i] != '\n')
        i++;
    if (stored[i] == '\n')
        i++;
    line = fft_substr(stored, 0, i);
    return line;
}

static char *trim_leftover(const char *stored)
{
    size_t i = 0;
    char *new_stored;
    if (!stored)
        return NULL;
    while (stored[i] && stored[i] != '\n')
        i++;
    if (!stored[i])
        return NULL;
    i++;
    new_stored = fft_substr(stored, i, fft_strlen(stored) - i);
    if (!new_stored || !new_stored[0])
    {
        free(new_stored);
        return NULL;
    }
    return new_stored;
}

static char *read_and_accumulate(int fd, char *stored)
{
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read = 1;
    char *tmp;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
            return NULL;
        buffer[bytes_read] = '\0';
        if (!stored)
            stored = fft_substr(buffer, 0, bytes_read);
        else
        {
            tmp = fft_strjoin(stored, buffer);
            free(stored);
            stored = tmp;
        }
        if (fft_strchr(buffer, '\n'))
            break;
    }
    return stored;
}

char *get_next_line(int fd)
{
    static char *stored = NULL;
    char *line;
    char *new_stored;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    stored = read_and_accumulate(fd, stored);
    if (!stored)
        return NULL;
    line = extract_line(stored);
    new_stored = trim_leftover(stored);
    free(stored);
    stored = new_stored;
    return line;
}

size_t fft_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *fft_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}

char *fft_strjoin(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    char *result;
    size_t i;
    size_t j;
    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        return fft_substr(s2, 0, fft_strlen(s2));
    else if (!s2)
        return fft_substr(s1, 0, fft_strlen(s1));
    len1 = fft_strlen(s1);
    len2 = fft_strlen(s2);
    result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return NULL;
    i = 0;
    j = 0;
    while (i < len1)
        result[i++] = s1[j++];
    j = 0;
    while (j < len2)
        result[i++] = s2[j++];
    result[i] = '\0';
    return result;
}

char *fft_substr(const char *s, unsigned int start, size_t len)
{
    char *sub;
    size_t s_len;
    size_t i;
    if (!s)
        return NULL;
    s_len = fft_strlen(s);
    if (start >= s_len)
        return NULL;
    if (len > s_len - start)
        len = s_len - start;
    sub = (char *)malloc(sizeof(char) * (len + 1));
    if (!sub)
        return NULL;
    i = 0;
    while (i < len && s[start + i])
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return sub;
}

#ifdef TEST_GNL
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int fd = open(argv[1], O_RDONLY);
        char *line;
        if (fd == -1)
            return 1;
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s", line);
            free(line);
        }
        close(fd);
    }
    return 0;
}
#endif
