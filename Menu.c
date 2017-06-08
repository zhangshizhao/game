/* Project:		practice1
File Name:	Menu.c
Author:		������
Date:		2017-3-28
Purpose:		Levelģ��  */

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
int FFLAG;
static AEGfxTexture *pTex1;            //Pointer to Texture (Image)
static AEGfxTexture *pTex2;            //Pointer to Texture (Image)
static AEGfxTexture *pTex3;            //Pointer to Texture (Image)
static AEGfxTexture *pabout;            //Pointer to Texture (Image)
static int AnimationController = 8; // ���Ʋ���֡
static int AnimationCurFramex = 1;  //֡״̬
static int AnimationCurFramey = 1;  //֡״̬
static int control;
AEGfxVertexList*	pMesh1;		// ��״
AEGfxVertexList*	pMesh2;		// ��״
AEGfxVertexList*	pMesh3;		// ��״
 //------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void Load0(void)
{
	

	AEGfxMeshStart();
	AEGfxTriAdd(
		-576.0f, -324.0f, 0xFFFFFFFF, 0.0f, 0.16667f,
		576.0f, -324.0f, 0xFFFFFFFF, 0.125f, 0.16667f,
		-576.0f, 324.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		576.0f, -324.0f, 0xFFFFFFFF, 0.125f, 0.16667f,
		576.0f, 324.0f, 0xFFFFFFFF, 0.125f, 0.0f,
		-576.0f, 324.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 2!!");
	// Texture 1: From file
	pTex1 = AEGfxTextureLoad("menu.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-120.0f, -80.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		120.0f, -80.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-120.0f, 80.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		120.0f, -80.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		120.0f, 80.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-120.0f, 80.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");
	// Texture 1: From file
	pTex2 = AEGfxTextureLoad("start.png");
	AE_ASSERT_MESG(pTex2, "Failed to create texture1!!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-80.0f, -120.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		80.0f, -120.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-80.0f, 120.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		80.0f, -120.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		80.0f, 120.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-80.0f, 120.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh3 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh3, "Failed to create mesh 2!!");
	// Texture 1: From file
	pTex3 = AEGfxTextureLoad("list.png");
	AE_ASSERT_MESG(pTex3, "Failed to create texture1!!");

	// Texture 1: From file
	pabout = AEGfxTextureLoad("about.png");
	AE_ASSERT_MESG(pabout, "Failed to create texture1!!");

	// ǩ��
	fprintf(fp, "Menu:Load\n");
}

void Ini0(void)
{

	
	control = 0;

	// ǽ��1�ĳ�ʼλ��
	p1.x = 0.0f;
	p1.y = 0.0f;
	//�����λ�ó�ʼ��
	AEGfxSetCamPosition(0.0f, 0.0f);
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // ����ɫRGB
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);           // Alpha�ȵȣ���ѧ����ʾ��ͬģʽ��Ч��

												  // ǩ��
	fprintf(fp, "Menu:Initialize\n");
}

void Update0(void)
{
	double frameTime;
	// ======================
	// ֡ʱ�䣺�൱��zero�е�dt
	// ======================
	frameTime = AEFrameRateControllerGetFrameTime();

	// ״̬�л�
	if (AEInputCheckTriggered('R'))
	{
		Next = GS_Restart;
		return;
	}
	if (AEInputCheckTriggered(VK_ESCAPE))
	{
		if (FFLAG == 1)
		{
			FFLAG = 0;
			return;
		}
		else
		{
			Next = GS_Quit;
			return;
		}
	}
	if (AEInputCheckTriggered('1'))
	{
		Next = GS_L1;
		return;
	}
	if (AEInputCheckTriggered('2'))
	{
		Next = GS_L2;
		return;
	}
	if (AEInputCheckTriggered('A'))
	{
		FFLAG = 1;
		return;
	}
	
		
	

	// ��������
	Input_Initialize();

	// ǩ��
	fprintf(fp, "Menu:Update\n");
}

void Draw0(void)
{
	// ������1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(p1.x, p1.y);
	// Set texture for object 2
	                            //Ϊ�������ó�״̬
	if (AnimationCurFramey < 6) {
		if (AnimationCurFramex < AnimationController)
		{
			AEGfxTextureSet(pTex1, AnimationCurFramex*0.125f, AnimationCurFramey*0.16667f);
			if (control % 10 == 0)
				AnimationCurFramex += 1;
		}
		else
		{
			AEGfxTextureSet(pTex1, 0.0f, AnimationCurFramey*0.16667f); // ����1������ƫ����(x,y)
			AnimationCurFramex = 0;
		}
		if (control % (10 * 8) == 0)
			AnimationCurFramey += 1;
	}
	else {
		AnimationCurFramey = 0;
		AEGfxTextureSet(pTex1, 0.0f, 0.0f); // ����1������ƫ����(x,y)
	}
	control++;
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

	
	// ������2
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 100.0f);
	// Set texture for object 2
	//Ϊ�������ó�״̬
	AEGfxTextureSet(pTex2, 0.0f, 0.0f); // ����1������ƫ����(x,y)		
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
	if (FFLAG == 0)
	{
		// ������3
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.0f, -100.0f);
		// Set texture for object 2
		//Ϊ�������ó�״̬
		AEGfxTextureSet(pTex3, 0.0f, 0.0f); // ����1������ƫ����(x,y)
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh3, AE_GFX_MDM_TRIANGLES);
	}

	if (FFLAG == 1)
	{
		// ������3
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.0f, -100.0f);
		// Set texture for object 2
		//Ϊ�������ó�״̬
		AEGfxTextureSet(pabout, 0.0f, 0.0f); // ����1������ƫ����(x,y)
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh3, AE_GFX_MDM_TRIANGLES);
	}


	




	// ǩ��
	fprintf(fp, "Menu:Draw\n");
}

void Free0(void)
{
	// ǩ��
	fprintf(fp, "Menu:Free\n");
}

void Unload0(void)
{
	AEGfxMeshFree(pMesh1);		// ע�������Ķ���
	AEGfxMeshFree(pMesh2);		// ע�������Ķ���
	AEGfxMeshFree(pMesh3);		// ע�������Ķ���

	AEGfxTextureUnload(pTex1);
	AEGfxTextureUnload(pTex2);
	AEGfxTextureUnload(pTex3);
	AEGfxTextureUnload(pabout);

	// ǩ��
	fprintf(fp, "Menu:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//--------------------------------------------------------