#include <Windows.h>
void PrintCountsPerSecond();
void PrintPlayerPosition();
void UpdatePlayerPosition(int);
void UpdateBulletPosition(int);
bool isOnCollision(int);
namespace global
{
    namespace time
    {
        ULONGLONG previousTime;
        ULONGLONG currentTime;
        ULONGLONG deltaTime;

        int updateCount;
        int fixedUpdateCount;

        void InitTime()
        {
            currentTime = previousTime = GetTickCount64();
        }

        void UpdateTime()
        {
            previousTime = currentTime;
            currentTime = GetTickCount64();

            deltaTime = currentTime - previousTime;
        }

        ULONGLONG GetDeltaTime()
        {
            return deltaTime;
        }
    };


    SMALL_RECT playerMovableRect = { 5, 5, 30, 30 }; // @SEE StartGame()
    const int UP = 1;
    const int RIGHT = 2;
    const int DOWN = 3;
    const int LEFT = 4;


    struct Player
    {
        COORD curPlayerPos; // 현재 플레이어 위치
        int playerMoveSpeed = 100;
        int curStatus = 1;
        int hp = 50;
        int damage = 10;
    };
    Player player[2];

    struct Bullet
    {
        COORD curBulletPos;
        COORD direction = { 0,0 };
        Bullet* NextBullet = nullptr;
        bool isCollision = 0;
        int pri_range;
    };
    int rate[2] = { 1000,1000 };
    int bulletMoveSpeed[2] = { 20,20 };
    int range[2] = { 10,10 };
    global::Bullet* head[2] = { nullptr, nullptr };
    global::Bullet* tail[2] = { nullptr, nullptr };

};