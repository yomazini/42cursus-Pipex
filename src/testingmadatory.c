
#include "libft.h"

	#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("test.txt",O_RDONLY );
	int i = 1;
	if (fd == -1)
		return (1);
	char *line = get_next_line(fd);
	while (line)
	{
		printf("%d-->the line: %s",i, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	
}