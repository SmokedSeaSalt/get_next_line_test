#include <sys/stat.h> //to use open
#include <fcntl.h> //to use open
#include <unistd.h> //to use close
#include "get_next_line.h"
#include <stdio.h> //to use printf for debugging

void runfile(char *filename);
void testbonus(void);


int main(void)
{
	runfile("testfiles/basic.txt");
	printf("\n");
	runfile("testfiles/empty.txt");
	printf("\n");
	runfile("testfiles/multi_empty_lines.txt");
	printf("\n");
	runfile("testfiles/multi_single_char.txt");
	printf("\n");
	runfile("testfiles/multi_single_word.txt");
	printf("\n");
	runfile("testfiles/single_char.txt");
	printf("\n");
	runfile("testfiles/single_word.txt");
	printf("\n");

	testbonus();
	//runfile("testfiles/100bee_movie.txt");
	//printf("\n");
}

void runfile(char *filename)
{
	int i = 0;
	char *ret;

	int fd = open(filename, O_RDWR);

	ret = (char *)&i;
	while(ret != NULL)
	{
		ret = get_next_line(fd);
		printf("%d: %s", i++, ret);
		if (ret == NULL)
			break;
		free(ret);
		//ret = NULL;
	}

	close(fd);
}

void testbonus(void)
{

	char *ret1, *ret2, *ret3;
	int i = 0;
	int fd1, fd2, fd3;
	int stopped = 0;

	fd1 = open("testfiles/basic.txt", O_RDWR);
	fd2 = open("testfiles/multi_single_word.txt", O_RDWR);
	fd3 = open("testfiles/multi_empty_lines.txt", O_RDWR);

	ret1 = "start";
	ret2 = "start";
	ret3 = "start";

	while (stopped != 3)
	{
		if(ret1 != NULL)
		{
			ret1 = get_next_line(fd1);
			printf("fd: %d, line: %d: %s",fd1, i++, ret1);
			if (ret1 != NULL)
				free(ret1);
			if (ret1 == NULL)
				stopped++;
		}

		if(ret2 != NULL)
		{
			ret2 = get_next_line(fd2);
			printf("fd: %d, line: %d: %s",fd2, i++, ret2);
			if (ret2 != NULL)
				free(ret2);
			if (ret2 == NULL)
				stopped++;
		}

		if(ret3 != NULL)
		{
			ret3 = get_next_line(fd3);
			printf("fd: %d, line: %d: %s",fd3, i++, ret3);
			if (ret3 != NULL)
				free(ret3);
			if (ret3 == NULL)
				stopped++;
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);


}