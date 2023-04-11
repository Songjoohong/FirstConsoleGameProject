#pragma once
enum key
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SUBMIT,
	ENTER
};
namespace global
{
	// �Լ��� ����� ���� ���信 ���� ������ ���ô�.
	// �ʿ��� �������̽��� �����Ѵٴ� ���信 ���� ������ ���ô�.
	namespace input
	{
		// ����� ���� �ϴ� ����� ���� �˾� ���ô�. 
		// const Ű�� #define �� ���̸� �˾ƾ� �մϴ�. ��Ʈ! const �� ������ ���� Ű�����̰� #�� ������ ���������Ͽ� ���� �˴ϴ�.
		const int ESCAPE_KEY_INDEX = 0;
		const int USER_CMD_LEFT = 1;
		const int USER_CMD_RIGHT = 2;
		const int USER_CMD_UP = 3;
		const int USER_CMD_DOWN = 4;
		const int USER_CMD_ATTACK = 5;

		const int MAX_KEY = 6;

		void Set(const int keyIdx, bool bOn, int i);
		
		int MenuInput();
		void UpdateInput();
		bool IsEscapeCmdOn(int i = 0);
		bool IsLeftCmdOn(int i);
		bool IsRightCmdOn(int i);
		bool IsUpCmdOn(int i);
		bool IsDownCmdOn(int i);
		bool IsAttackCmdOn(int i);


		void UpdateInput();
	};
};