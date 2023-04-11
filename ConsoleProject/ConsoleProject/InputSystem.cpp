#include <windows.h>
#include <cassert>
#include <iostream>
#include <conio.h>
#include "InputSystem.h"

namespace global
{
	namespace input
	{
		bool inputKeyTable[2][MAX_KEY]; // ���ǵ� Ű ���� ó�� �մϴ�.

		// Helper Functions ..
		void Set(const int keyIdx, bool bOn, int i)
		{
			assert(keyIdx >= 0 && keyIdx < MAX_KEY); // ��� �ڵ带 �ۼ��ϴ� �Ϳ� �ͼ������� �մϴ�.  �迭�� �ٷ� ���� �ε����� �����ؾ� �մϴ�!!

			inputKeyTable[i][keyIdx] = bOn;			// bool Ÿ���� Ȱ�� �սô�.
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
					//std::cout << "��" << std::endl;
					return UP;
				}
				else if (v == 80) {
					//std::cout << "�Ʒ�" << std::endl;
					return DOWN;
				}
				else if (v == 75) {
					//std::cout << "����" << std::endl;
					return LEFT;
				}
				else if (v == 77) {
					//std::cout << "������" << std::endl;
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

		
		// �Է� Ű���� ���� �˾� ���ô�. ��ŷ�� �ͺ�ŷ�� ���ؼ��� �����ϰ� ����� �մϴ�!!
		// * ��Ʈ ���꿡 ���� �н��մϴ�. & �� && �� �޶��. 
		// &, * �����ڰ� �ƶ��� ���� �ٸ��� �ؼ��Ǵ� �Ϳ� ���� �ؾ� �մϴ�. 
		void UpdateInput()
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				global::input::Set(ESCAPE_KEY_INDEX, true, 0);
			}

			if (GetAsyncKeyState('A') & 0x8000) //���� 'A'
			{
				global::input::Set(USER_CMD_LEFT, true, 0);
			}

			if (GetAsyncKeyState('D') & 0x8000) //������ 'D'
			{
				global::input::Set(USER_CMD_RIGHT, true, 0);
			}

			if (GetAsyncKeyState('W') & 0x8000) //���� 'W'
			{
				global::input::Set(USER_CMD_UP, true, 0);
			}

			if (GetAsyncKeyState('S') & 0x8000) //�Ʒ��� 'S'
			{
				global::input::Set(USER_CMD_DOWN, true, 0);
			}

			if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
			{
				global::input::Set(USER_CMD_ATTACK, true, 0);
			}

			if (GetAsyncKeyState('J') & 0x8000) //���� 'J'
			{
				global::input::Set(USER_CMD_LEFT, true, 1);
			}

			if (GetAsyncKeyState('L') & 0x8000) //������ 'L'
			{
				global::input::Set(USER_CMD_RIGHT, true, 1);
			}

			if (GetAsyncKeyState('I') & 0x8000) //���� 'I'
			{
				global::input::Set(USER_CMD_UP, true, 1);
			}

			if (GetAsyncKeyState('K') & 0x8000) //�Ʒ��� 'K'
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
