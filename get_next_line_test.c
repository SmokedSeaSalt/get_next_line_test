#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include <fcntl.h> //to use open
#include <sys/stat.h> //to use open flags
#include <unistd.h> //to use close, read
#include <string.h> //to use strcmp
#include <stdlib.h> //to use malloc, free
#include "get_next_line.h" //to use get_next_line
#include "test.h"

int main(void)
{
	int testcount = 1;

	testfile("testfiles/basic.txt", 150, testcount++);
	testfile("testfiles/empty.txt", 100, testcount++);
	testfile("testfiles/multi_empty_lines.txt", 100, testcount++);
	testfile("testfiles/multi_single_char.txt", 100, testcount++);
	testfile("testfiles/multi_single_word.txt", 100, testcount++);
	testfile("testfiles/single_char.txt", 100, testcount++);
	testfile("testfiles/single_word.txt", 100, testcount++);
	testfile("testfiles/bee_movie.txt", 50000, testcount++);

}

testfile(char *file, size_t filesize, int test_count)
{
	int exp_file = open(file, O_RDONLY);
	int res_file = open("res.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);

	//save default stdout
	int default_stdout = dup(STDOUT_FILENO);

	char *ret_str = &"init";

	//redirect from stdout to exp.txt
	dup2(res_file, STDOUT_FILENO);
	while(ret_str != NULL)
	{
		ret_str = get_next_line(res_file);
		printf("%s", ret_str);
		free(ret_str);
		fflush(stdout);
	}

	//restore default stdout
	dup2(default_stdout, STDOUT_FILENO);

	//compare results
	lseek(exp_file, 0, SEEK_SET);
	lseek(res_file, 0, SEEK_SET);

	//create buffer to read files
	char *buffer_exp, *buffer_res;
	buffer_exp = calloc(filesize, sizeof(char));
	buffer_res = calloc(filesize, sizeof(char));

	if (buffer_exp == NULL || buffer_res == NULL)
		exit(-1);

	int exp_len = read(exp_file, buffer_exp, filesize);
	int res_len = read(res_file, buffer_res, filesize);

	if(exp_len == res_len && strcmp(buffer_exp, buffer_res) == 0)
	{
		printf("%s%d:OK %s", KGRN, test_count, KNRM);
		fflush(stdout);
	}
	else
	{
		printf("%s%d:KO\n%s", KRED, test_count, KNRM);
		printf("exp:%s != res:%s\n", buffer_exp, buffer_res);
		fflush(stdout);
	}

	close(exp_file);
	close(res_file);

	free(buffer_exp);
	free(buffer_res);
}
