#include "Stats.h"
#include <iostream>
void Stat_menu(int index, int i)
{
	if (index == 17)
	{
		Move_Speed(i);
	}
	else if (index == 18)
	{
		Damage(i);
	}
	else if (index == 19)
	{
		HP(i);
	}
	else if (index == 20)
	{
		Rate(i);
	}
	Stat_UI(index, i);
}
int gauge[4][2] = { 0, };
void Move_Speed(int i)
 {
	gauge[0][i]++;
	global::player[i].playerMoveSpeed = 100 - 10 * (gauge[0][i] % 7);
}

void Damage(int i)
{
	gauge[1][i]++;
	global::player[i].damage = 10 + (gauge[1][i] % 7);
}

void HP(int i)
{
	gauge[2][i]++;
	global::player[i].hp = 50 + 10 * (gauge[2][i] % 7);
}

void Rate(int i)
{
	gauge[3][i]++;
	global::rate[i] = 1000 - 100 * (gauge[3][i] % 7);
}

int Stat_point(int i)
{
	int statPoint[2] = { 0, };
	int sum = 0;
	for (int a = 0; a < 4; a++)
	{
		sum += gauge[a][i] % 7;
	}
	statPoint[i] = 10 - sum;
	return statPoint[i];
}
void Stat_UI(int index, int i)
{
	int new_index = index - 17;
	if (i == 0)
	{
		if (gauge[new_index][i] % 7 == 0)
		{
			GotoXY(43, index);
			std::cout << "брбрбрбрбрбр";
		}
		if (gauge[new_index][i] % 7 > 0)
		{
			GotoXY(43, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 1)
		{
			GotoXY(45, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 2)
		{
			GotoXY(47, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 3)
		{
			GotoXY(49, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 4)
		{
			GotoXY(51, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 5)
		{
			GotoXY(53, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		GotoXY(43, 21);
		std::cout << "   ";
		GotoXY(43, 21);
		std::cout << Stat_point(0);
	}
	else if (i == 1)
	{
		if (gauge[new_index][i] % 7 == 0)
		{
			GotoXY(102, index);
			std::cout << "брбрбрбрбрбр";
		}
		if (gauge[new_index][i] % 7 > 0)
		{
			GotoXY(102, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 1)
		{
			GotoXY(104, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 2)
		{
			GotoXY(106, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 3)
		{
			GotoXY(108, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 4)
		{
			GotoXY(110, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		if (gauge[new_index][i] % 7 > 5)
		{
			GotoXY(112, index);
			std::cout << "бс";
			GotoXY(28, index);
		}
		GotoXY(102, 21);
		std::cout << "   ";
		GotoXY(102, 21);
		std::cout << Stat_point(1);
	}
	
	
	
}