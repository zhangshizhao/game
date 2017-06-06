/* Project:		practice1
File Name:	Menu.c
Author:		张仕钊
Date:		2017-3-28
Purpose:		Level模块  */

#include <stdio.h>
#include "GameStateList.h"
#include "System.h"
#include "Menu.h"
#include "Input.h"
#include "GamestateManager.h"
#include "AEEngine.h"
#include "Math2D.h"
#include "Matrix2D.h"
#include <stdlib.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
Vector2D p1;
static AEGfxTexture *pTex1;            //Pointer to Texture (Image)

AEGfxVertexList*	pMesh1;		// 形状

								//------------------------------------------------------------------------------
								// Private Function Declarations:
								//------------------------------------------------------------------------------

								//------------------------------------------------------------------------------
								// Public Functions:
								//------------------------------------------------------------------------------

void Load3(void)
{


	AEGfxMeshStart();
	AEGfxTriAdd(
		-550.0f, -380.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		550.0f, -380.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-550.0f, 380.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		550.0f, -380.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		550.0f, 380.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-550.0f, 380.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 2!!");

	// Texture 1: From file
	pTex1 = AEGfxTextureLoad("Success.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");


	// 签到
	fprintf(fp, "Success:Load\n");
}

void Ini3(void)
{

	// 墙体1的初始位置
	p1.x = 0.0f;
	p1.y = 0.0f;
	//摄像机位置初始化
	AEGfxSetCamPosition(0.0f, 0.0f);
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // 背景色RGB
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);           // Alpha等等，向学生演示不同模式的效果

												  // 签到
	fprintf(fp, "Success:Initialize\n");
}

void Update3(void)
{

	if (AEInputCheckTriggered(VK_ESCAPE))
	{
		Next = GS_L0;
		return;
	}
	
	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Success:Update\n");
}

void Draw3(void)
{
	

	// 画对象1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, -50.0f);
	// Set texture for object 1
	//为纹理设置初状态
	AEGfxTextureSet(pTex1, 0.0f, 0.0f); // 参数1：纹理，偏移量(x,y)		
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);


	// 签到
	fprintf(fp, "Success:Draw\n");
}

void Free3(void)
{
	// 签到
	fprintf(fp, "Success:Free\n");
}

void Unload3(void)
{
	AEGfxMeshFree(pMesh1);		// 注销创建的对象


	AEGfxTextureUnload(pTex1);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------