#include "get_next_line.h"
/* UNIT TESTS FOR bookmark_manager()

	TEST 1: 
	There are 10 fd, none are stored in bookmark. bookmark_manager() must store each. 
	If return index is equal to (i + 1) then result++. Expected result: 10

	TEST 2: 
	There are 10 fd, 3 of them already bookmarked. bookmark_manager() must store the missing ones. 
	If return index is equal to (i + 1) then result++. Expected result: 10

	TEST 3: 
	There are 10 fd, all bookmarked. bookmark_manager() must store none. The will be search in arbitrary order. 
	Index will be saved and check if found the correct fd. Expected result int[10] = {9, 5, 3, 10, 7, 1, 4, 2, 6, 8}
*/
int	test_1 (t_bookmark *bookmark, int fd[]);
int	test_2 (t_bookmark *bookmark, int fd[]);
int	*test_3 (t_bookmark *bookmark, int fd[]);
void checkTest(int result, int testNumber);
int checkArrayTest(int *result, int testNumber);
void resetBookmark(t_bookmark * bookmark);

int main()
{
	t_bookmark bookmark[BOOKMARK_SIZE];
	int fd[10] = {3, 30, 300, 5, 50, 500, 7, 70, 700, 9};
	int fd_order[10] = {700, 50, 300, 9, 7, 3, 5, 30,  500, 70};
	int i = 1;
	int *fd_result;

	resetBookmark(bookmark);
	int result = test_1(bookmark, fd);
	checkTest(result, i++);
	resetBookmark(bookmark);
	result = test_2(bookmark, fd);
	checkTest(result, i++);
	// Do not reset to use bookmark with all fd
	fd_result = test_3(bookmark, fd_order);
	checkArrayTest(fd_result, i++);

	free(fd_result);
	return (0);
}

int	test_1 (t_bookmark *bookmark, int fd[])
{
	int found_index = 0;
	int result = 0;
	int i;

	for(i = 0; i < 10; i++)
	{
		found_index = bookmark_manager(bookmark, fd[i]);
		if (found_index == (i + 1))
			result++;
	}
	if (result == 10)
		return (1);
	return (0);
}

int	test_2 (t_bookmark *bookmark, int fd[])
{
	bookmark[0].fd = -1;
	bookmark[0].init = 'Y';
	bookmark[1].fd = 3;
	bookmark[1].init = 'Y';
	bookmark[2].fd = 30;
	bookmark[2].init = 'Y';
	bookmark[3].fd = 300;
	bookmark[3].init = 'Y';
	int found_index = 0;
	int result = 0;
	int i;

	for(i = 0; i < 10; i++)
	{
		found_index = bookmark_manager(bookmark, fd[i]);
		if (found_index == (i + 1))
			result++;
	}
	if (result == 10)
		return (1);
	return (0);
}

int	*test_3 (t_bookmark *bookmark, int fd[])
{
	int found_index = 0;
	int i;
	int *result = (int *) malloc(sizeof(int) * 10);

	for(i = 0; i < 10; i++)
	{
		found_index = bookmark_manager(bookmark, fd[i]);
		result[i] = found_index;
	}
	return result;
}

void checkTest(int result, int testNumber)
{
	if (result == 1)
		printf("Test %d is successful!\n", testNumber);
	else
		printf("Test %d is unsuccessful! You suck! :)\n", testNumber);
}

int checkArrayTest(int *result, int testNumber)
{
	int i = 0;
	int expected[10] = {9, 5, 3, 10, 7, 1, 4, 2, 6, 8};

	while (i < 10)
	{
		if (result[i] != expected[i])
		{
			printf("Test %d is unsuccessful! You suck! :)\n", testNumber);
			return (0);
		}
			
		i++;
	}
	printf("Test %d is successful!\n", testNumber);
	return (1);
}

void resetBookmark(t_bookmark * bookmark)
{
	int i = 0;

	while (i < 10)
	{
		bookmark[i].init = 'N';
		i++;
	}
}