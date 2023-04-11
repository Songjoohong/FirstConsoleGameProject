#pragma once
#include <Windows.h>
void Stat_menu(int, int);
void Move_Speed(int);
void Damage(int);
void HP(int i);
void Rate(int);
int Stat_point(int);

namespace global {
    struct Player
    {
        COORD curPlayerPos; // 현재 플레이어 위치
        int playerMoveSpeed = 100;
        int curStatus = 1;
        int hp = 100;
        int damage = 50;
    };
	extern Player player[2];

    extern int rate[2];
    extern int bulletMoveSpeed[2];
    extern int range[2];
}
extern void GotoXY(int, int);
void Stat_UI(int, int);