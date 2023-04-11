#include<iostream>
#include<Windows.h>
#include<conio.h>
#include"Title.h"
#include"inputSystem.h"
#include"Stats.h"

void Init()
{
    system("mode con cols=150  lines=40");
    system("title BATTLE BUILDER");

    // �����̴� Ŀ���� �� ���� ��Ű��.
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0; // Ŀ���� ������ ���� ����(0�̸� �Ⱥ���, 0���� ���� ���̸� ����)
    cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void DrawTitle()
{
    std::cout << R"(            



                          
             ######     ##     ######   ######   ####     #######           ######   ##   ##   ####    ####     #####    #######  ######
              ##  ##   ####    # ## #   # ## #    ##       ##   #            ##  ##  ##   ##    ##      ##       ## ##    ##   #   ##  ##
              ##  ##  ##  ##     ##       ##      ##       ## #              ##  ##  ##   ##    ##      ##       ##  ##   ## #     ##  ##
              #####   ##  ##     ##       ##      ##       ####              #####   ##   ##    ##      ##       ##  ##   ####     #####
              ##  ##  ######     ##       ##      ##   #   ## #              ##  ##  ##   ##    ##      ##   #   ##  ##   ## #     ## ##
              ##  ##  ##  ##     ##       ##      ##  ##   ##   #            ##  ##  ##   ##    ##      ##  ##   ## ##    ##   #   ##  ##
             ######   ##  ##    ####     ####    #######  #######           ######    #####    ####    #######  #####    #######  #### ##
      )" << std::endl;

    GotoXY(MENU_POS_X, MENU_POS_Y);
    std::cout << "���� ����";

    GotoXY(MENU_POS_X, MENU_POS_Y + 2);
    std::cout << "���� ����";

    GotoXY(MENU_POS_X, MENU_POS_Y + 4);
    std::cout << "  �� ��  ";
}

int SelectMenu()
{
    int x = MENU_POS_X;
    int y = MENU_POS_Y;

    GotoXY(x - 2, y);
    std::cout << ">";

    while (true)
    {
        int key = global::input::MenuInput();

        switch (key) {
        case UP:
            if (y > 22) {
                GotoXY(x - 2, y);
                std::cout << " ";
                y -= 2;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case DOWN:
            if (y < 26) {
                GotoXY(x - 2, y);
                std::cout << " ";
                y += 2;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case SUBMIT:
            return (y - 22) / 2;
        default:
            break;
        }
    }

    return -1;
}

  bool DrawReady()
{
    system("cls");
    std::cout << R"(



                                             
                                                                       STATS
                                                    
                                                                               


 
                                     
                                         Player 1                                                   Player 2  
                                         
                                         

      
                              move speed : �������                                  Move speed : �������    
                                  Damage : �������                                      Damage : �������
                                      HP : �������                                          HP : �������
                                    Rate : �������                                        Rate : �������
                              Stat point : 10                                            Stat point : 10
                                                                                          
                                                                             
                                   
                                                    
                                                                                                                                            
                                                                



      
                                                          >> Press Enter to start
                                 
                                 
    )";
    int x = 28;
    int y = 17;

    GotoXY(x - 2, y);
    std::cout << ">";

    while (true)
    {
        int key = global::input::MenuInput();

        switch (key) {
        case UP:
            if (y > 17) {
                GotoXY(x - 2, y);
                std::cout << " ";
                y -= 1;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case DOWN:
            if (y < 20) {
                GotoXY(x - 2, y);
                std::cout << " ";
                y += 1;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case RIGHT:
            if (x == 28) {
                GotoXY(x - 2, y);
                std::cout << " ";
                x += 60;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case LEFT:
            if (x == 88)
            {
                GotoXY(x - 2, y);
                std::cout << " ";
                x -= 60;
                GotoXY(x - 2, y);
                std::cout << ">";
            }
            break;
        case SUBMIT:
            Stat_menu(y, x > 50);
            break;
        case ENTER:
            if (Stat_point(0) >= 0 && Stat_point(1) >= 0)
            {
                Init();
                return 1;
            }
            break;
        default:
            break;
        }
    }

    return -1;
}

void DrawInfo()
{
    system("cls");
    std::cout << R"(










                                                    
                                                                          CONTROLS
                                                    
                                                                                
                                                       __________________         ___________________
                                                           Player 1                    Player 2  
                                                    
                                                          �̵� : WASD                 �̵� : IJKL   
                                                         ���� : LShift               ���� : RShift                                             
                                                       __________________         ___________________
                                                    
                                                    
                                                                      ������ : ����ȫ
                                                                      
                                                                      
                                                                  >> Press SpaceBar to Exit
                                 
                                 
    )";

    // �Է��� ���� ����ϱ�
    while (true) {
        if (_kbhit()) {
            if (_getch() == 32)
                return;
        }
    }
}

int DrawEnd()
{
    system("cls");
    std::cout << R"(
















                                                             ������ �����Ͻðڽ��ϱ�?
                                                           
                                                               Yes : y     No : n

    )";

    // �Է��� ���� ����ϱ�
    while (true) {
        if (_kbhit()) {
            int v = _getch();
            if (v == 89 || v == 121)
                return 0;
            else if (v == 78 || v == 110)
                return 1;
        }
    }

    return -1;
}

void GotoXY(int x, int y)
{
    COORD Cur = { (SHORT)x, (SHORT)y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
