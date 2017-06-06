// Project Name		:	Practice2-Skeleton
// File Name		:	main.c
// Author			:	������
// Creation Date	:	2017/03/26
// Purpose			:	��ϰ2����Ŀ
// History			:
// - 2017/03/26		:	- ��ʼ����
// ---------------------------------------------------------------------------

#include <Windows.h>
#include "System.h"
#include "GamestateManager.h"
#include "GameStateList.h"
#include "Input.h"
#include "AEEngine.h"	// AlphaEngine

// Alpha Libray
#pragma comment (lib, "Alpha_Engine.lib")
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//System Initialize
	System_Initialize(hInstance,nCmdShow);
	//GSM INItialize
	GSM_Initialize(GS_L0);

	// Game Flow
	while (Current != GS_Quit)
	{
		if (Current == GS_Restart)
		{
			Current = Previous;
			Next = Previous;
		}
		else
		{
			// GSM Update
			GSM_Update(Current);
			pLoad();
		}
		pIni();
		// Game Loop
		while (Current == Next)
		{
			// Alpha - ֡��ʼ
			AESysFrameStart();
			//Input_Handle();  �ص�����
			AEInputUpdate();		// Alpha Engine��������
			pUpdate();
			pDraw();
			// Alpha - ֡����
			AESysFrameEnd();
		}
		pFree();
		if (Next != GS_Restart)
			pUnload();
		Previous = Current;
		Current = Next;
	}
	// System Exit
	System_Exit();
	return 0;
}
