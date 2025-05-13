int main(void)
{
	int testcount = 1;

	testfile("testfiles/basic.txt", testcount++);
	testfile("testfiles/empty.txt", testcount++);
	testfile("testfiles/multi_empty_lines.txt", testcount++);
	testfile("testfiles/multi_single_char.txt", testcount++);
	testfile("testfiles/multi_single_word.txt", testcount++);
	testfile("testfiles/single_char.txt", testcount++);
	testfile("testfiles/single_word.txt", testcount++);
	testfile("testfiles/bee_movie.txt", testcount++);

}