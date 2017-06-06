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
static AEGfxTexture *pTex1;            //Pointer to Texture (Image)

AEGfxVertexList*	pMesh1;		// ��״

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


	// ǩ��
	fprintf(fp, "Success:Load\n");
}

void Ini3(void)
{

	// ǽ��1�ĳ�ʼλ��
	p1.x = 0.0f;
	p1.y = 0.0f;
	//�����λ�ó�ʼ��
	AEGfxSetCamPosition(0.0f, 0.0f);
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // ����ɫRGB
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);           // Alpha�ȵȣ���ѧ����ʾ��ͬģʽ��Ч��

												  // ǩ��
	fprintf(fp, "Success:Initialize\n");
}

void Update3(void)
{

	if (AEInputCheckTriggered(VK_ESCAPE))
	{
		Next = GS_L0;
		return;
	}
	
	// ��������
	Input_Initialize();

	// ǩ��
	fprintf(fp, "Success:Update\n");
}

void Draw3(void)
{
	

	// ������1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, -50.0f);
	// Set texture for object 1
	//Ϊ�������ó�״̬
	AEGfxTextureSet(pTex1, 0.0f, 0.0f); // ����1������ƫ����(x,y)		
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);


	// ǩ��
	fprintf(fp, "Success:Draw\n");
}

void Free3(void)
{
	// ǩ��
	fprintf(fp, "Success:Free\n");
}

void Unload3(void)
{
	AEGfxMeshFree(pMesh1);		// ע�������Ķ���


	AEGfxTextureUnload(pTex1);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------