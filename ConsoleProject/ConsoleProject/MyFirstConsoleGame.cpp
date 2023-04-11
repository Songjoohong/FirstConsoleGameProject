#include <stdio.h>
#include <windows.h>
#include <random>
#include <iostream>
#include "InputSystem.h" // 기능 별로 모듈화를 한다는 개념에 대해 생각해 봅시다!
#include "RenderSystem.h"
#include "MyFirstConsoleGame.h"
#include "Title.h"

bool Clamp(short& n, short min, short max) // 레퍼런스 타입에 대해 배워 봅시다.
{
    int isblock = 0;
    if (n < min)
    {
        n = min;
        isblock = 1;
    }
    if (n > max)
    {
        n = max;
        isblock = 1;
    }
    if (isblock) return 1;
    return 0;
}
//Bullet part
void CreateBullet(int i)
{
    static ULONGLONG elapsedTime1;
    static ULONGLONG elapsedTime2;

    elapsedTime1 += global::time::GetDeltaTime();
    elapsedTime2 += global::time::GetDeltaTime();
    global::Bullet* bullet = new global::Bullet;
    bullet->curBulletPos = global::player[i].curPlayerPos;
    bullet->NextBullet = nullptr;
    bullet->pri_range = global::range[i];
    if (global::player[i].curStatus == 2)
        bullet->direction.X = 1;
    else if (global::player[i].curStatus == 4)
        bullet->direction.X = -1;
    else
        bullet->direction.X = 0;

    if (global::player[i].curStatus == 1)
        bullet->direction.Y = -1;
    else if (global::player[i].curStatus == 3)
        bullet->direction.Y = 1;
    else
        bullet->direction.Y = 0;
    if (global::head[i] == nullptr)
    {
        global::head[i] = bullet;
        global::tail[i] = bullet;
    }
    else
    {
        global::tail[i]->NextBullet = bullet;
        global::tail[i] = bullet;
    }
}

void DestroyBullet(global::Bullet* Node, int i)
{
    global::Bullet* ptr = global::head[i];
    global::Bullet* preptr = nullptr;
    while (ptr->NextBullet != nullptr)
    {
        if (ptr == Node)
        {
            if (ptr == global::head[i] && ptr == global::tail[i])
            {
                delete ptr;
                global::head[i] == nullptr;
                global::tail[i] == nullptr;
            }
            else if (ptr == global::head[i])
            {
                global::head[i] = ptr->NextBullet;

                delete ptr;
                break;
            }
            else if (ptr == global::tail[i])
            {
                global::tail[i] = preptr;
                preptr->NextBullet = nullptr;
                delete ptr;
                break;
            }
            else
            {
                preptr->NextBullet = ptr->NextBullet;
                delete ptr;
                break;
            }
        }
        preptr = ptr;
        ptr = ptr->NextBullet;
    }

}

void DrawBullet()
{
    if (global::head[0] != nullptr)
    {
        global::Bullet* temp1 = global::head[0];
        while (temp1 != nullptr)
        {
            if (temp1->direction.X == 0)
            {
                render::ScreenDraw2(temp1->curBulletPos.X, temp1->curBulletPos.Y, "|" );
                temp1 = temp1->NextBullet;
            }
            else if (temp1->direction.Y == 0)
            {
                render::ScreenDraw2(temp1->curBulletPos.X, temp1->curBulletPos.Y, "-");
                temp1 = temp1->NextBullet;
            }
        }
    }
    if (global::head[1] != nullptr)
    {
        global::Bullet* temp2 = global::head[1];
        while (temp2 != nullptr)
        {
            if (temp2->direction.X == 0)
            {
                render::ScreenDraw2(temp2->curBulletPos.X, temp2->curBulletPos.Y, "|");
                temp2 = temp2->NextBullet;
            }
            else if (temp2->direction.Y == 0)
            {
                render::ScreenDraw2(temp2->curBulletPos.X, temp2->curBulletPos.Y, "-");
                temp2 = temp2->NextBullet;
            }

        }
    }

}

void DrawBullet(int i)
{

    global::Bullet* temp = global::head[i];
    while(temp != nullptr)
    {
        temp->curBulletPos.X = temp->curBulletPos.X + temp->direction.X;
        temp->curBulletPos.Y = temp->curBulletPos.Y + temp->direction.Y;
        if (Clamp(temp->curBulletPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right))
            DestroyBullet(temp, i);
        if (Clamp(temp->curBulletPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom))
            DestroyBullet(temp, i);
        if (temp->pri_range == 0)
        {
            DestroyBullet(temp, i);
            
        }
        else
        {
            temp->pri_range--;
            //render::ScreenDraw(temp->curBulletPos.X, temp->curBulletPos.Y, '-');
            if (temp->direction.X == 0)
            {
                render::ScreenDraw2(temp->curBulletPos.X, temp->curBulletPos.Y, "|");

            }
            if (temp->direction.Y == 0)
            {
                render::ScreenDraw2(temp->curBulletPos.X, temp->curBulletPos.Y, "-");

            }
        }
        temp = temp->NextBullet;
    }

}

void UpdateBullet()
{
    // 키 입력과 화면 출력과 게임 로직 갱신을 분리해서 생각해 봅시다.
    static ULONGLONG elapsedTime1;
    static ULONGLONG elapsedTime2;

    elapsedTime1 += global::time::GetDeltaTime();
    elapsedTime2 += global::time::GetDeltaTime();
    while (elapsedTime1 >= global::bulletMoveSpeed[0])
    {
        DrawBullet(0);
        elapsedTime1 -= global::bulletMoveSpeed[0];
        isOnCollision(0);
    }
    while (elapsedTime2 >= global::bulletMoveSpeed[1])
    {
        elapsedTime2 -= global::bulletMoveSpeed[1];
        DrawBullet(1);
        isOnCollision(1);
    }
    UpdateBulletPosition(0);
    UpdateBulletPosition(1);
}


void UpdateBulletPosition(int i)
{
    static ULONGLONG elapsedTime[2];

    elapsedTime[0] += global::time::GetDeltaTime();
    elapsedTime[1] += global::time::GetDeltaTime();
    if (global::input::IsAttackCmdOn(i) && elapsedTime[i] > global::rate[i])
    {
        global::input::Set(global::input::USER_CMD_ATTACK, false, i);
        CreateBullet(i);
        elapsedTime[i] = 0;
    }

}
//Player part
void DrawPlayer()
{
    if (global::player[0].curStatus == 1)
    {
        render::ScreenDraw2(global::player[0].curPlayerPos.X, global::player[0].curPlayerPos.Y, "▲");
    }
    if (global::player[0].curStatus == 2)
    {
        render::ScreenDraw2(global::player[0].curPlayerPos.X, global::player[0].curPlayerPos.Y, "▶");
    }
    if (global::player[0].curStatus == 3)
    {
        render::ScreenDraw2(global::player[0].curPlayerPos.X, global::player[0].curPlayerPos.Y, "▼");
    }
    if (global::player[0].curStatus == 4)
    {
        render::ScreenDraw2(global::player[0].curPlayerPos.X, global::player[0].curPlayerPos.Y, "◀");
    }
    if (global::player[1].curStatus == 1)
    {
        render::ScreenDraw2(global::player[1].curPlayerPos.X, global::player[1].curPlayerPos.Y, "△");
    }
    if (global::player[1].curStatus == 2)
    {
        render::ScreenDraw2(global::player[1].curPlayerPos.X, global::player[1].curPlayerPos.Y, "▷");
    }
    if (global::player[1].curStatus == 3)
    {
        render::ScreenDraw2(global::player[1].curPlayerPos.X, global::player[1].curPlayerPos.Y, "▽");
    }
    if (global::player[1].curStatus == 4)
    {
        render::ScreenDraw2(global::player[1].curPlayerPos.X, global::player[1].curPlayerPos.Y, "◁");
    }
}

void UpdatePlayer()
{
    // 키 입력과 화면 출력과 게임 로직 갱신을 분리해서 생각해 봅시다.
    static ULONGLONG elapsedTime1;
    static ULONGLONG elapsedTime2;

    elapsedTime1 += global::time::GetDeltaTime();
    elapsedTime2 += global::time::GetDeltaTime();
    while (elapsedTime1 >= global::player[0].playerMoveSpeed)
    {
        UpdatePlayerPosition(0);

        elapsedTime1 -= global::player[0].playerMoveSpeed;

    }
    while (elapsedTime2 >= global::player[1].playerMoveSpeed)
    {
        UpdatePlayerPosition(1);

        elapsedTime2 -= global::player[1].playerMoveSpeed;

    }

}

void UpdatePlayerPosition(int i)
{

    if (global::input::IsLeftCmdOn(i))
    {
        global::input::Set(global::input::USER_CMD_LEFT, false, i);

        global::player[i].curPlayerPos.X--;
        global::player[i].curStatus = global::LEFT;
        Clamp(global::player[i].curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
    }

    if (global::input::IsRightCmdOn(i))
    {
        global::input::Set(global::input::USER_CMD_RIGHT, false, i);

        global::player[i].curPlayerPos.X++;
        global::player[i].curStatus = global::RIGHT;
        Clamp(global::player[i].curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
    }

    if (global::input::IsUpCmdOn(i))
    {
        global::input::Set(global::input::USER_CMD_UP, false, i);

        global::player[i].curPlayerPos.Y--;
        global::player[i].curStatus = global::UP;
        Clamp(global::player[i].curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);
    }

    if (global::input::IsDownCmdOn(i))
    {
        global::input::Set(global::input::USER_CMD_DOWN, false, i);

        global::player[i].curPlayerPos.Y++;
        global::player[i].curStatus = global::DOWN;
        Clamp(global::player[i].curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);
    }

    if (global::input::IsEscapeCmdOn())
    {
        global::input::Set(global::input::ESCAPE_KEY_INDEX, false, 0);

        //TODO: 게임 화면 전환이나 종료 처리

        return; // 다른 키 입력을 신경 쓸 필요가 없어요.
    }



}

bool isOnCollision(int i)
{
    global::Bullet* temp = global::head[i];
    while (temp != nullptr)
    {
        if (temp->curBulletPos.X == global::player[!i].curPlayerPos.X && temp->curBulletPos.Y == global::player[!i].curPlayerPos.Y && !(temp->isCollision))
        {
            global::player[!i].hp -= global::player[i].damage;
            temp->isCollision = true;
            //DestroyBullet(temp, i);
        }
        temp = temp->NextBullet;
    }
    if (global::player[!i].hp <= 0)
        return true;
    return false;
}
void StartGame()
{
    render::InitScreen();

    global::playerMovableRect = render::GetPlayerMovableRect();

    render::DrawBorder(); // 벽을 그려 놓자!

    // 플레이어 시작 위치 설정
    global::player[0].curPlayerPos.X = global::playerMovableRect.Left + (global::playerMovableRect.Left + global::playerMovableRect.Right) / 4;
    global::player[0].curPlayerPos.Y = global::playerMovableRect.Bottom - 2;

    global::player[1].curPlayerPos.X = global::playerMovableRect.Left + (global::playerMovableRect.Left + global::playerMovableRect.Right) / 4 * 3;
    global::player[1].curPlayerPos.Y = global::playerMovableRect.Bottom - 2;
  

    DrawPlayer();
}


void Update()
{
    global::time::updateCount += 1;
    UpdateBullet();
    UpdatePlayer();



}



void PrintCountsPerSecond()
{
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();
    if (elapsedTime >= 1000)
    {
        char buffer1[64] = "";
        char buffer2[64] = "";
        sprintf_s(buffer1, "Player1 HP : %d \n",
            global::player[0].hp);
        sprintf_s(buffer2, "Plater2 HP : %d \n", global::player[1].hp);

        render::ScreenDraw2(15, 0, buffer1);
        render::ScreenDraw2(120, 0, buffer2);
        elapsedTime = 0;
        global::time::updateCount = 0;
        global::time::fixedUpdateCount = 0;
    }
}

bool IsGameRun()
{
    return true;
}

void ProcessInput()
{
    global::input::UpdateInput();
}

void FixedUpdate()
{
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();

    while (elapsedTime >= 1000) //1초
    {
        global::time::fixedUpdateCount += 1;

        elapsedTime -= 1000;

    }
}

void Render()
{
    render::ScreenClear();

    PrintCountsPerSecond();

    DrawBullet();


    DrawPlayer();

    //render::DrawBorder();

    render::ScreenFlipping();
}

void EndGame()
{
    render::ScreenRelease();
}

int main()
{
        while (true)
        {
            Init();
            DrawTitle();

            int selectNum = SelectMenu();

            if (selectNum == 0)
            {
                if (DrawReady())
                    break;
                continue;
            }
            else if (selectNum == 1)
            {
                // 게임 정보
                DrawInfo();
                continue;
            }
            else if (selectNum == 2)
            {
                // 게임 종료
                int ynNum = DrawEnd();

                if (ynNum == 0) {
                    return 0;
                }
                else if (ynNum == 1) {
                    continue;
                }

                return 0;
            }
        }
        global::time::InitTime();

        StartGame();

        while (IsGameRun())
        {
            global::time::UpdateTime();

            ProcessInput();
            FixedUpdate();

            Update();
            Render();
            if (isOnCollision(0) == 1)
            {
                render::ScreenClear();
                render::ScreenDraw(75,50, "Player1 Win!");
                render::ScreenFlipping();
                Sleep(3000);
                break;
            }
            if (isOnCollision(1) == 1)
            {
                
                render::ScreenClear();
                render::ScreenDraw(75, 50, "Player2 Win!");
                render::ScreenFlipping();
                Sleep(3000);
                break;
            }
        }
        EndGame();

    

    return 0;
}
