#include <stdio.h>
#include <stdlib.h>
#define min(a, b) a > b ? b : a;

int check_local(int n, int (*array)[n], int x, int y)
{

	int c = 0;
	if (x - 1 > -1)
	{
		if (array[x][y] < array[x - 1][y])
			c++;
	}
	else
		c++;

	if (x + 1 < n)
	{
		if (array[x][y] < array[x + 1][y])
			c++;
	}
	else
		c++;

	if (y - 1 > -1)
	{
		if (array[x][y] < array[x][y - 1])
			c++;
	}
	else
		c++;

	if (y + 1 < n)
	{
		if (array[x][y] < array[x][y + 1])
			c++;
	}
	else
		c++;

	if (c == 4)
		return 1;
	return 0;
}

int find_local_minimum_2d(int n, int (*array)[n], int row_start, int col_start, int row_end, int col_end)
{

	//Base case
	if (row_start == col_end)
		return array[row_start][col_end];

	int x, y; //temp variables

	int global_min = array[row_start][col_start];

	if (check_local(n, array, row_start, col_start))
		return global_min;

	int mid_row = row_start + (row_end - row_start) / 2;
	int mid_col = col_start + (col_end - col_start) / 2;

	int flag = 0;
	int middle_flag = 0;
	for (int i = col_start; i <= col_end; ++i)
	{
		//checking top panel of the window frame
		if (array[row_start][i] < global_min)
		{
			global_min = array[row_start][i];
			x = row_start;
			y = i;
			flag = 3;
			if (check_local(n, array, x, y))
				return array[x][y];
		}

		//checking bottom panel of the window frame
		if (array[row_end][i] < global_min)
		{
			global_min = array[row_end][i];
			x = row_end;
			y = i;
			flag = 4;
			if (check_local(n, array, x, y))
				return array[x][y];
		}

		//checking middle row of the window frame
		if (array[mid_row][i] < global_min)
		{
			global_min = array[mid_row][i];
			x = mid_row;
			y = i;
			flag = 5;
			middle_flag = 1;
			if (check_local(n, array, x, y))
				return array[x][y];
		}
	}

	for (int i = row_start; i <= row_end; i++)
	{
		//left panel of the window
		if (array[i][col_start] < global_min)
		{
			global_min = array[i][col_start];
			x = i;
			y = col_start;
			flag = 1;
			if (check_local(n, array, x, y))
				return array[x][y];
		}

		//right panel of the window
		if (array[i][col_end] < global_min)
		{
			global_min = array[i][col_end];
			x = i;
			y = col_end;
			flag = 2;
			if (check_local(n, array, x, y))
				return array[x][y];
		}

		//middle column of the window
		if (array[i][mid_col] < global_min)
		{
			global_min = array[i][mid_row];
			x = i;
			y = mid_row;
			flag = 5;
			middle_flag = 2;
			if (check_local(n, array, x, y))
				return array[x][y];
		}
	}

	/*
	flag=1 for right move
	flag=2 for left move
	flag=3 for down move
	flag=4 for up move
	flag=5 for middle
	*/

	if (flag == 5)
	{
		if (middle_flag == 1)
		{
			if (!(array[x][y] < array[x - 1][y]))
				flag = 4; //up
			if (!(array[x][y] < array[x + 1][y]))
				flag = 3; //down
		}
		if (middle_flag == 2)
		{
			if (!(array[x][y] < array[x][y - 1]))
				flag = 2; //left
			if (!(array[x][y] < array[x][y + 1]))
				flag = 1; //right
		}
	}
	if (flag == 1)
	{
		if (array[x][y] < array[x][y + 1])
		{
			return array[x][y];
		}

		if (x < mid_row)
		{
			return find_local_minimum_2d(n, array, row_start + 1, col_start + 1, mid_row - 1, mid_col - 1);
		}

		return find_local_minimum_2d(n, array, mid_row + 1, col_start + 1, row_end - 1, mid_col - 1);
	}
	if (flag == 2)
	{
		if (array[x][y] < array[x][y - 1])
		{
			return array[x][y];
		}

		if (x < mid_row)
		{
			return find_local_minimum_2d(n, array, row_start + 1, mid_col + 1, mid_row - 1, col_end - 1);
		}

		return find_local_minimum_2d(n, array, mid_row + 1, mid_col + 1, row_end - 1, col_end - 1);
	}
	if (flag == 3)
	{
		if (array[x][y] < array[x + 1][y])
		{
			return array[x][y];
		}

		if (y < mid_col)
		{
			return find_local_minimum_2d(n, array, row_start + 1, col_start + 1, mid_row - 1, mid_col - 1);
		}

		return find_local_minimum_2d(n, array, row_start + 1, mid_col + 1, mid_row - 1, col_end - 1);
	}
	if (flag == 4)
	{
		if (array[x][y] < array[x - 1][y])
		{
			return array[x][y];
		}
		if (y < mid_col)
		{
			return find_local_minimum_2d(n, array, mid_row + 1, col_start + 1, row_end - 1, mid_col - 1);
		}
		return find_local_minimum_2d(n, array, mid_row + 1, mid_col + 1, row_end - 1, col_end - 1);
	}
}

int main()
{

	int n;
	printf("Enter n:");
	scanf("%d", &n);
	int array[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &array[i][j]);
		}
	}

	int ans = find_local_minimum_2d(n, array, 0, 0, n - 1, n - 1);
	printf("%d\n", ans);

	return 0;
}