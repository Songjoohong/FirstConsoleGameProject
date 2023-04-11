#include <windows.h>
#include <cassert>
#include <iostream>
#include <conio.h>
#include "InputSystem.h"

namespace global
{
	namespace input
	{
		bool inputKeyTable[2][MAX_KEY]; // 정의된 키 값을 처리 합니다.

		// Helper Functions ..
		void Set(const int keyIdx, bool bOn, int i)
		{
			assert(keyIdx >= 0 && keyIdx < MAX_KEY); // 방어 코드를 작성하는 것에 익숙해져야 합니다.  배열을 다룰 때는 인덱스를 조심해야 합니다!!

			inputKeyTable[i][keyIdx] = bOn;			// bool 타입을 활용 합시다.
		}

		bool IsEscapeCmdOn(int i)
		{
			return inputKeyTable[i][ESCAPE_KEY_INDEX];
		}

		bool IsLeftCmdOn(int i)
		{
			return inputKeyTable[i][USER_CMD_LEFT];
		}

		bool IsRightCmdOn(int i)
		{
			return inputKeyTable[i][USER_CMD_RIGHT];
		}

		bool IsUpCmdOn(int i)
		{
			return inputKeyTable[i][USER_CMD_UP];
		}

		bool IsDownCmdOn(int i)
		{
			return inputKeyTable[i][USER_CMD_DOWN];
		}

		bool IsAttackCmdOn(int i)
		{
			return inputKeyTable[i][USER_CMD_ATTACK];
		}

		int MenuInput()
		{
			int v = 0;
			if (_kbhit()) {
				v = _getch();

				if (v == 72) {
					//std::cout << "위" << std::endl;
					return UP;
				}
				else if (v == 80) {
					//std::cout << "아래" << std::endl;
					return DOWN;
				}
				else if (v == 75) {
					//std::cout << "왼쪽" << std::endl;
					return LEFT;
				}
				else if (v == 77) {
					//std::cout << "오른쪽" << std::endl;
					return RIGHT;
				}
				else if (v == 32) {
					return SUBMIT;
				}
				else if (v == 13)
				{
					return ENTER;
				}
				else {
					return -1;
				}
			}

			return -1;
		}

		
		// 입력 키값에 대해 알아 봅시다. 블러킹과 넌블러킹에 대해서만 이해하고 가기로 합니다!!
		// * 비트 연산에 대해 학습합니다. & 와 && 은 달라요. 
		// &, * 연산자가 맥락에 따라 다르게 해석되는 것에 주의 해야 합니다. 
		void UpdateInput()
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				global::input::Set(ESCAPE_KEY_INDEX, true, 0);
			}

			if (GetAsyncKeyState('A') & 0x8000) //왼쪽 'A'
			{
				global::input::Set(USER_CMD_LEFT, true, 0);
			}

			if (GetAsyncKeyState('D') & 0x8000) //오른쪽 'D'
			{
				global::input::Set(USER_CMD_RIGHT, true, 0);
			}

			if (GetAsyncKeyState('W') & 0x8000) //위쪽 'W'
			{
				global::input::Set(USER_CMD_UP, true, 0);
			}

			if (GetAsyncKeyState('S') & 0x8000) //아래쪽 'S'
			{
				global::input::Set(USER_CMD_DOWN, true, 0);
			}

			if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
			{
				global::input::Set(USER_CMD_ATTACK, true, 0);
			}

			if (GetAsyncKeyState('J') & 0x8000) //왼쪽 'J'
			{
				global::input::Set(USER_CMD_LEFT, true, 1);
			}

			if (GetAsyncKeyState('L') & 0x8000) //오른쪽 'L'
			{
				global::input::Set(USER_CMD_RIGHT, true, 1);
			}

			if (GetAsyncKeyState('I') & 0x8000) //위쪽 'I'
			{
				global::input::Set(USER_CMD_UP, true, 1);
			}

			if (GetAsyncKeyState('K') & 0x8000) //아래쪽 'K'
			{
				global::input::Set(USER_CMD_DOWN, true, 1);
			}

			if (GetAsyncKeyState(VK_RSHIFT) & 0x8000)
			{
				global::input::Set(USER_CMD_ATTACK, true, 1);
			}
		}
	};
};
