#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int getrand(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

class Piece
{
public:
	int score;
	int shape;
	int next_shape;

	int head_x;
	int head_y;

	int size_h;
	int size_w;

	int next_size_h;
	int next_size_w;

	int box_shape[4][4];
	int next_box_shape[4][4];

	int box_map[30][45];

	bool game_over;

public:
	void initial();
	void set_shape(int &cshape, int box_shape[][4], int &size_w, int &size_h);

	void score_next();
	void judge();
	void move();
	void rotate();
	bool isaggin();
	bool exsqr(int row);
}

void Piece::set_shape(int &cshape, int shape[][4], int &size_w, int &size_h)
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			shape[i][j] = 0;

	switch(cshape)
	{
		case 0:
			size_h = 1;
			size_w = 4;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[0][2] = 1;
			shape[0][3] = 1;
			break;
		case 1:
			size_h = 2;
			size_w = 3;
			shape[0][0] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		case 2:
			size_h = 2;
			size_w = 3;
			shape[0][2] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		case 3:
			size_h = 2;
			size_w = 3;
			shape[0][1] = 1;
			shape[0][2] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			break;
		case 4:
			size_h = 2;
			size_w = 3;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		case 5:
			size_h = 2;
			size_w = 2;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			break;
		case 6:
			size_h = 2;
			size_w = 3;
			shape[0][1] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
	}

	head_x = game_win_width / 2;
	head_y = 1;
	
	if (isaggin())
		game_over = true;
}

void Piece::rorate()
{
	int temp[4][4] = {0};
	int temp_piece[4][4] = {0};
	int i, j, tmp_size_h, tmp_size_w;

	tmp_size_h = size_h;
	tmp_size_w = size_w;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j <4; j++)
			temp_piece[i][j] = box_shape[i][j];

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			temp[j][i] = box_shape[i][j];
	i = size_h;
	size_h = size_w;
	size_w = i;
	for (i = 0; i < size_h; i++)
		for (j = 0; j < size_w; j++)
			box_shape[i][size_w - 1 - j] = temp[i][j];

	if (isaggin())
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				box_shape[i][j] = temp_piece[i][j];
		size_w = tmp_size_w;
		size_h = tmp_size_h;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (temp_piece[i][j] == 1)
				{
					mvwaddch(game_win, head_y + i, head_x + j, ' ');
					wrefresh(game_win);
				}
			}
		for (int i = 0; i < size_h; i++)
			for (int j = 0; j < size_w; j++)
			{
				if (this -> box_shape[i][j] == 1)
				{
					mvwaddch(game_win, head_y + i, head_x + j, '#');
					wrefresh(game_win);
				}
			}
	}
}

void Piece::move()
{
	fd_set set;
	FD_ZERO(&set);
	FD_SET(0, &set);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;

	if (select(1, &set, NULL, NULL, &timeout) == 0)
	{
		head_y++;
		if (isaggin())
		{
			head_y--;
			for (int i = 0; i < size_h; i++)
				for (int j = 0; j < size_w; j++)
					if (box_shape[i][j] == 1)
						box_map[head_y + i][head_x + j] = 1;
			score_next();
		}
		else
		{
			for (int i = size_h - 1; i >= 0; i--)
				for (int j = 0; j < size_w; j++)
				{
					if (this -> box_shape[i][j] == 1)
					{
						mvwaddch(game_win, head_y - 1 + i, head_x + j, ' ');
						mvwaddch(game_win, head_y + i, head_x + j, '#');
					}
				}
			wrefresh(game_win);
		}
	}

	if (FD_ISSET(0, &set))
	{
		while ((key = getch()) == -1);

		if (key == KEY_LEFT)
		{
			head_x--;
			if (isaggin())
				head_x++;
			else
			{
				for (int i = 0; i < size_h; i++)
			}
		}
	}
}

































