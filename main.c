// Project Name		:	Practice2-Skeleton
// File Name		:	main.c
// Author			:	张仕钊
// Creation Date	:	2017/03/26
// Purpose			:	练习2空项目
// History			:
// - 2017/03/26		:	- 初始创建
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
			// Alpha - 帧开始
			AESysFrameStart();
			//Input_Handle();  回调函数
			AEInputUpdate();		// Alpha Engine处理输入
			pUpdate();
			pDraw();
			// Alpha - 帧结束
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
