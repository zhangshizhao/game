/* Project:		practice1
   File Name:	Level1.c
   Author:		������
   Date:		2017-3-28
   Purpose:		Levelģ��  */

#include <stdio.h>
#include "GameStateList.h"
#include "System.h"
#include "Level1.h"
#include "Input.h"
#include "GamestateManager.h"
#include "AEEngine.h"
#include "SoundSystem.h"
#include "Math2D.h"
#include "Matrix2D.h"
#include <stdlib.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------
#define GAME_OBJ_BASE_NUM_MAX	32			// �������ͣ�������ࣩ��Ŀ����
#define GAME_OBJ_NUM_MAX		4096*20		// ������Ŀ����

#define FLAG_ACTIVE				0x00000001  // ������־

#define PARTICLE_SIZE			3.5f

// ����ЧӦ����
enum PARTICLE_EFFECT
{
	PARTICLE_EFFECT_EXPLOSION,
	PARTICLE_EFFECT_FOUNTAIN,
	PARTICLE_EFFECT_FIRE,
	PARTICLE_EFFECT_FIREBALL,
	PARTICLE_EFFECT_FADE
};
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// ��Ϸ������/�ṹ
typedef struct
{
	unsigned long       type;       //��Ϸ��������
	AEGfxVertexList*	pMesh;		// ��״
	unsigned long		flag;		// ���־
	//float				scale;		// �ߴ�
	float width;                    //���
	float height;                   //�߶�
	int outo;
	Vector2D			posCurr;	// ��ǰλ��
	//Vector2D			velCurr;	// ��ǰ�ٶ�
	//float				dirCurr;	// ��ǰ����

	//AEMtx33				transform;	// �任����ÿһ֡����ҪΪÿһ���������

	//int					gridCollisionFlag; // ����ͼ��ײ����־
}GameObj;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
GameObj Hero;
GameObj Wall[30];
GameObj Enemy[10];
GameObj Key;
GameObj Door;
AEGfxVertexList* background;
float camX, camY;               // Used to temporary store camera position
static AEGfxTexture *pTex1;            //Pointer to Texture (Image)
static AEGfxTexture *pKey;
static AEGfxTexture *pBack;
static AEGfxTexture *pWall;
static AEGfxTexture *pEnemy;
static AEGfxTexture *pDoor;
static int AnimationController = 8; // ���Ʋ���֡
static int AnimationCurFrameR = 1;  //������
static int AnimationCurFrameL = 1;  //������
static int flag;          //�ж϶����˶���״̬
static int FLAG[5];
static int up;            //��Ծ��״̬
static int high;        //��Ծ�߶�
static int control;    //֡�ʿ���
static float speed;      //��Ծ�ٶ�
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void Load1(void)
{

	// ��ʼ��ӱ���
	AEGfxMeshStart();
	AEGfxTriAdd(
		-2500.0f, -500.0f, 0x00000000, 0.0f, 1.0f,
		2500.0f, -500.0f, 0x00000000, 1.0f, 1.0f,
		-2500.0f, 500.0f, 0x00000000, 0.0f, 0.0f);
	AEGfxTriAdd(
		2500.0f, -500.0f, 0x00000000, 1.0f, 1.0f,
		2500.0f, 500.0f, 0x00000000, 1.0f, 0.0f,
		-2500.0f, 500.0f, 0x00000000, 0.0f, 0.0f);
	background = AEGfxMeshEnd();
	AE_ASSERT_MESG(background, "Failed to create mesh 1!!");


	// ��ʼ��Ӷ���1
	AEGfxMeshStart();
	AEGfxTriAdd(
		-35.0f, -46.0f, 0x00000000, 0.0f, 1.0f,
		35.0f, -46.0f, 0x00000000, 0.0625f, 1.0f,
		-35.0f, 46.0f, 0x00000000, 0.0f, 0.0f);
	AEGfxTriAdd(
		35.0f, -46.0f, 0x00000000, 0.0625f, 1.0f,
		35.0f, 46.0f, 0x00000000, 0.0625f, 0.0f,
		-35.0f, 46.0f, 0x00000000, 0.0f, 0.0f);
	Hero.pMesh = AEGfxMeshEnd();
	Hero.width = 50;
	Hero.height = 90;
	AE_ASSERT_MESG(Hero.pMesh, "Failed to create mesh 1!!");



	AEGfxMeshStart();

	// ��ӵ���
	AEGfxTriAdd(
		-400.0f, -10.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		400.0f, -10.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-400.0f, 10.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		400.0f, -10.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		400.0f, 10.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-400.0f, 10.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[0].pMesh = AEGfxMeshEnd();
	Wall[0].width = 800;
	Wall[0].height = 20;
	AE_ASSERT_MESG(Wall[0].pMesh, "Failed to create mesh 2!!");


	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[1].pMesh = AEGfxMeshEnd();
	Wall[1].width = 200;
	Wall[1].height = 40;
	AE_ASSERT_MESG(Wall[1].pMesh, "Failed to create mesh 2!!");


	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[2].pMesh = AEGfxMeshEnd();
	Wall[2].width = 200;
	Wall[2].height = 40;
	AE_ASSERT_MESG(Wall[2].pMesh, "Failed to create mesh 2!!");


	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[3].pMesh = AEGfxMeshEnd();
	Wall[3].width = 200;
	Wall[3].height = 40;
	Wall[3].outo = 3;
	AE_ASSERT_MESG(Wall[3].pMesh, "Failed to create mesh 2!!");




	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[4].pMesh = AEGfxMeshEnd();
	Wall[4].width = 200;
	Wall[4].height = 40;
	AE_ASSERT_MESG(Wall[4].pMesh, "Failed to create mesh 2!!");


	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[5].pMesh = AEGfxMeshEnd();
	Wall[5].width = 200;
	Wall[5].height = 40;
	Wall[5].outo = 0;
	AE_ASSERT_MESG(Wall[5].pMesh, "Failed to create mesh 2!!");



	AEGfxTriAdd(
		-100.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		100.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-100.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[6].pMesh = AEGfxMeshEnd();
	Wall[6].width = 200;
	Wall[6].height = 40;
	AE_ASSERT_MESG(Wall[6].pMesh, "Failed to create mesh 2!!");



	AEGfxTriAdd(
		-250.0f, -20.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		250.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-250.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		250.0f, -20.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		250.0f, 20.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-250.0f, 20.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[7].pMesh = AEGfxMeshEnd();
	Wall[7].width = 500;
	Wall[7].height = 40;
	AE_ASSERT_MESG(Wall[7].pMesh, "Failed to create mesh 2!!");



	AEGfxTriAdd(
		-200.0f, -10.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		200.0f, -10.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		-200.0f, 10.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		200.0f, -10.0f, 0xFFFFFFFF, 1.0f, 1.0f,
		200.0f, 10.0f, 0xFFFFFFFF, 1.0f, 0.0f,
		-200.0f, 10.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	Wall[8].pMesh = AEGfxMeshEnd();
	Wall[8].width = 400;
	Wall[8].height = 20;
	AE_ASSERT_MESG(Wall[8].pMesh, "Failed to create mesh 2!!");




	// ��ӵ���
	AEGfxTriAdd(
		-20.0f, -20.0f, 0xFF00FFFF, 0.0f, 1.0f,
		20.0f, -20.0f, 0xFF00FFFF, 1.0f, 1.0f,
		-20.0f, 20.0f, 0xFF00FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		20.0f, -20.0f, 0xFF00FFFF, 1.0f, 1.0f,
		20.0f, 20.0f, 0xFF00FFFF, 1.0f, 0.0f,
		-20.0f, 20.0f, 0xFF00FFFF, 0.0f, 0.0f);

	Enemy[0].pMesh = AEGfxMeshEnd();
	Enemy[0].width = 30;
	Enemy[0].height = 25;
	AE_ASSERT_MESG(Enemy[0].pMesh, "Failed to create mesh 2!!");


	// ���Կ��
	AEGfxTriAdd(
		-20.0f, -20.0f, 0xFFFFB90F, 0.0f, 1.0f,
		20.0f, -20.0f, 0xFFFFB90F, 1.0f, 1.0f,
		-20.0f, 20.0f, 0xFFFFB90F, 0.0f, 0.0f);

	AEGfxTriAdd(
		20.0f, -20.0f, 0xFFFFB90F, 1.0f, 1.0f,
		20.0f, 20.0f, 0xFFFFB90F, 1.0f, 0.0f,
		-20.0f, 20.0f, 0xFFFFB90F, 0.0f, 0.0f);

	Key.pMesh = AEGfxMeshEnd();
	Key.width = 30;
	Key.height = 25;
	Key.outo = 0;
	AE_ASSERT_MESG(Key.pMesh, "Failed to create mesh 2!!");


	// �����
	AEGfxTriAdd(
		-40.0f, -40.0f, 0xFFFFB90F, 0.0f, 1.0f,
		40.0f, -40.0f, 0xFFFFB90F, 1.0f, 1.0f,
		-40.0f, 40.0f, 0xFFFFB90F, 0.0f, 0.0f);

	AEGfxTriAdd(
		40.0f, -40.0f, 0xFFFFB90F, 1.0f, 1.0f,
		40.0f, 40.0f, 0xFFFFB90F, 1.0f, 0.0f,
		-40.0f, 40.0f, 0xFFFFB90F, 0.0f, 0.0f);

	Door.pMesh = AEGfxMeshEnd();
	Door.width = 80;
	Door.height = 80;
	Door.outo = 0;
	AE_ASSERT_MESG(Door.pMesh, "Failed to create mesh 2!!");




	// Texture 1: From file
	pTex1 = AEGfxTextureLoad("walk3.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

	// Texture 1: From file
	pKey = AEGfxTextureLoad("Key.png");
	AE_ASSERT_MESG(pKey, "Failed to create texture2!!");

	// Texture 1: From file
	pBack = AEGfxTextureLoad("background1.png");
	AE_ASSERT_MESG(pBack, "Failed to create texture3!!");

	// Texture 1: From file
	pWall = AEGfxTextureLoad("wall.png");
	AE_ASSERT_MESG(pWall, "Failed to create texture4!!");

	// Texture 1: From file
	pEnemy = AEGfxTextureLoad("enemy1.png");
	AE_ASSERT_MESG(pEnemy, "Failed to create texture5!!");

	// Texture 1: From file
	pDoor = AEGfxTextureLoad("Door.png");
	AE_ASSERT_MESG(pDoor, "Failed to create texture6!!");

	// ��������
	SoundAdd("menu.wav", FMOD_LOOP_NORMAL, SOUND_1);

	// ǩ��
	fprintf(fp, "Level1:Load\n");
}

void Ini1(void)
{

	flag = 0;
	up = 0;
	high = 0;
	control = 0;
	speed = 0;
	// ����1�ĳ�ʼλ��
	Hero.posCurr.x = -370.0f;
	Hero.posCurr.y = -142.0f;
	
	// ǽ��0�ĳ�ʼλ��
	Wall[0].posCurr.x = 0.0f;
	Wall[0].posCurr.y = -200.0f;

	// ǽ��1�ĳ�ʼλ��
	Wall[1].posCurr.x = 450.0f;
	Wall[1].posCurr.y = -140.0f;

	// ǽ��2�ĳ�ʼλ��
	Wall[2].posCurr.x = 500.0f;
	Wall[2].posCurr.y = -90.0f;

	// ǽ��3�ĳ�ʼλ��
	Wall[3].posCurr.x = 550.0f;
	Wall[3].posCurr.y = -40.0f;

	// ǽ��4�ĳ�ʼλ��
	Wall[4].posCurr.x = 300.0f;
	Wall[4].posCurr.y = 100.0f;

	// ǽ��5�ĳ�ʼλ��
	Wall[5].posCurr.x = 780.0f;
	Wall[5].posCurr.y = 100.0f;

	// ǽ��6�ĳ�ʼλ��
	Wall[6].posCurr.x = 1500.0f;
	Wall[6].posCurr.y = 100.0f;

	// ǽ��7�ĳ�ʼλ��
	Wall[7].posCurr.x = -200.0f;
	Wall[7].posCurr.y = 100.0f;

	// ǽ��8�ĳ�ʼλ��
	Wall[8].posCurr.x = 1600.0f;
	Wall[8].posCurr.y = -200.0f;


	Enemy[0].posCurr.x = 200.0f;
	Enemy[0].posCurr.y = -170.0f;

	Key.posCurr.x = -400.0f;
	Key.posCurr.y = 140.0f;

	Door.posCurr.x = 1780.0f;
	Door.posCurr.y = -150.0f;

	//�����λ�ó�ʼ��
	camX = 0.0f;
	camY = 0.0f;
	AEGfxSetCamPosition(camX, camY);

	FLAG[0] = 0;

	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // ����ɫRGB
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);           // Alpha�ȵȣ���ѧ����ʾ��ͬģʽ��Ч��

	// ��������
	SoundPlay(SOUND_1);

	// ǩ��
	fprintf(fp, "Level1:Initialize\n");
}

void Update1(void)
{
	int i;
	for (i = 0; i < 5; i++) {
		FLAG[i] = 0;
	}
	for (i = 0; i <= 8; i++) {
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[i].posCurr, Wall[i].width, Wall[i].height) == 1) FLAG[1] = 1;
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[i].posCurr, Wall[i].width, Wall[i].height) == 2) FLAG[2] = 2;
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[i].posCurr, Wall[i].width, Wall[i].height) == 3) FLAG[3] = 3;
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[i].posCurr, Wall[i].width, Wall[i].height) == 4) FLAG[4] = 4;
	}
	if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Enemy[0].posCurr, Enemy[0].width, Enemy[0].height)) FLAG[0] = 1;
	if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Key.posCurr, Key.width, Key.height)) {
		Key.outo = -1; 
		Wall[5].outo = 1;
	}
	if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Door.posCurr, Door.width, Door.height)) {
		FLAG[0] = 10; 
		Next = GS_L2;
	}
	if ((FLAG[0] == 1) || (Hero.posCurr.y < -350)) {// ����1�ĳ�ʼλ��
		Hero.posCurr.x = -370.0f;
		Hero.posCurr.y = -142.0f;
		speed = 0;
		AEGfxSetCamPosition(0, 0);
		return;
	}





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
		Next = GS_L0;
		return;
	}
	if (AEInputCheckTriggered('2'))
	{
		Next = GS_L2;
		return;
	}

	// Music Pause
	if (AEInputCheckTriggered('P'))
	{
		SoundPausePlay(SOUND_1);
	}
	// Music Volume +
	if (AEInputCheckTriggered('V'))
	{
		SetVolume(SOUND_1, GetVolume(SOUND_1) + .1f);
	}



	// Move the camera
	if (Hero.posCurr.x > 0) {
		/*AEGfxGetCamPosition(&camX, &camY);
		if (AEInputCheckCurr(VK_UP)
			AEGfxSetCamPosition(camX, camY + 3);
		else
			if (AEInputCheckCurr(VK_DOWN))
				AEGfxSetCamPosition(camX, camY - 3);*/

		AEGfxGetCamPosition(&camX, &camY);
		AEGfxSetCamPosition(Hero.posCurr.x, camY);
		/*if (AEInputCheckCurr(VK_LEFT) && (FLAG[2] != 2))
			AEGfxSetCamPosition(camX - frameTime * 100, camY);
		else
			if (AEInputCheckCurr(VK_RIGHT) && (FLAG[1] != 1))
				AEGfxSetCamPosition(camX + frameTime * 100, camY);*/
	}
	//���µ���ֱ��ײ��ǽ
	if ((FLAG[3] != 3) && (up == 0)) {
		speed += frameTime * 150.0f;
		if (speed >= 150) speed = 150;
		Hero.posCurr.y -= speed * frameTime;
	}
	else
		speed = 0;
	// ������Ծ	
	if ((high == 80) || (FLAG[4] == 4)) {
		up = 0; 
		high = 0;
	}
	if (AEInputCheckCurr(VK_UP)) { //��Ծ
		if (FLAG[3] == 3) {
			up = 1;
		}
	}
	if (up == 1) {
		Hero.posCurr.y += 2.0f;
		high += 2;
	}
	//���������ƶ�
	if (AEInputCheckCurr(VK_LEFT) && (FLAG[2] != 2)) {
		Hero.posCurr.x -= frameTime * 100.0f;         //���ܳ��������
	}
	else
		if (AEInputCheckCurr(VK_RIGHT) && (FLAG[1] != 1))
			Hero.posCurr.x += frameTime * 100.0f;



	if (Wall[3].outo == 3) {
		if(StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[3].posCurr, Wall[3].width, Wall[3].height) == 3)
			Hero.posCurr.y += frameTime * 50.0f;
		Wall[3].posCurr.y += frameTime * 50.0f;
		if (Wall[3].posCurr.y >= 100) Wall[3].outo = 4;
	}
	if (Wall[3].outo == 4) {
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[3].posCurr, Wall[3].width, Wall[3].height) == 3)
			Hero.posCurr.y -= frameTime * 50.0f;
		Wall[3].posCurr.y -= frameTime * 50.0f;
		if (Wall[3].posCurr.y <= -40) Wall[3].outo = 3;
	}

	if (Wall[5].outo == 1) {
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[5].posCurr, Wall[5].width, Wall[5].height) == 3)
			Hero.posCurr.x += frameTime * 50.0f;
		Wall[5].posCurr.x += frameTime * 50.0f;
		if (Wall[5].posCurr.x >= 1200) Wall[5].outo = 2;
	}
	if (Wall[5].outo == 2) {
		if (StaticRectToStaticRect(&Hero.posCurr, Hero.width, Hero.height, &Wall[5].posCurr, Wall[5].width, Wall[5].height) == 3)
			Hero.posCurr.x -= frameTime * 50.0f;
		Wall[5].posCurr.x -= frameTime * 50.0f;
		if (Wall[5].posCurr.x <= 780) Wall[5].outo = 1;
	}






	// ��������
	Input_Initialize();

	// ǩ��
	fprintf(fp, "Level1:Update\n");
}

void Draw1(void)
{
	static int i;
	//������
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);   
	AEGfxSetPosition(0, 0);
	// Set texture for object 2
	AEGfxTextureSet(pBack, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(background, AE_GFX_MDM_TRIANGLES);




	// ������1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(Hero.posCurr.x, Hero.posCurr.y);
	// Set texture for object 2
	if(flag == 0)                             //Ϊ�������ó�״̬
		AEGfxTextureSet(pTex1, 0.0f, 0.0f);       
	else
		AEGfxTextureSet(pTex1, 1.0f - 0.0625f, 0.0f);
	if (AEInputCheckCurr(VK_RIGHT)) {         //���Ҽ�ʱ����
		flag = 0;
		if (AnimationCurFrameR < AnimationController)
		{
			
			AEGfxTextureSet(pTex1, AnimationCurFrameR*0.0625f, 0.0f);
			if (control % 8 == 0) {
				AnimationCurFrameR += 1;
			}
			control++;
		}
		else
		{
			AEGfxTextureSet(pTex1, 0.0f, 0.0f); // ����1������ƫ����(x,y)
			AnimationCurFrameR = 0;
			control = 0;
		}

	}
	if (AEInputCheckCurr(VK_LEFT)) {         //�����ʱ����
		flag = 1;
		if (AnimationCurFrameL < AnimationController)
		{
			AEGfxTextureSet(pTex1, 1.0f - AnimationCurFrameL*0.0625f, 0.0f);
			if (control % 8 == 0) {
				AnimationCurFrameL += 1;
			}
			control++;
		}
		else
		{
			AEGfxTextureSet(pTex1, 1.0f - 0.0625f, 0.0f); // ����1������ƫ����(x,y)
			AnimationCurFrameL = 1;
			control = 0;
		}

	}
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(Hero.pMesh, AE_GFX_MDM_TRIANGLES);

	for (i = 0; i <= 8; i++)
	{
		// Drawing object 2
		// Set position for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(Wall[i].posCurr.x, Wall[i].posCurr.y);
		// Set texture for object 2
		AEGfxTextureSet(pWall, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(Wall[i].pMesh, AE_GFX_MDM_TRIANGLES);
	}
	


	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);   // �����������û���ģʽΪRGB
	AEGfxSetPosition(Enemy[0].posCurr.x, Enemy[0].posCurr.y);
	// Set texture for object 2
	AEGfxTextureSet(pEnemy, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(Enemy[0].pMesh, AE_GFX_MDM_TRIANGLES);

	if(Key.outo != -1)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);   // �����������û���ģʽΪRGB
		AEGfxSetPosition(Key.posCurr.x, Key.posCurr.y);
		// Set texture for object 2
		AEGfxTextureSet(pKey, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(Key.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);   // �����������û���ģʽΪRGB
	AEGfxSetPosition(Door.posCurr.x, Door.posCurr.y);
	// Set texture for object 2
	AEGfxTextureSet(pDoor, 0, 0);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(Door.pMesh, AE_GFX_MDM_TRIANGLES);

	// ǩ��
	fprintf(fp, "Level1:Draw\n");
}

void Free1(void)
{
	// ǩ��
	fprintf(fp, "Level1:Free\n");
}

void Unload1(void)
{
	static int i;
	AEGfxMeshFree(Hero.pMesh);		// ע�������Ķ���
	for(i = 0;i <= 8; i++)
		AEGfxMeshFree(Wall[i].pMesh);	
	AEGfxMeshFree(Enemy[0].pMesh);
	AEGfxMeshFree(Key.pMesh);
	AEGfxMeshFree(Door.pMesh);
	AEGfxTextureUnload(pTex1);
	AEGfxTextureUnload(pEnemy);
	AEGfxTextureUnload(pWall);
	AEGfxTextureUnload(pKey);
	AEGfxTextureUnload(pDoor);

								// ǩ��
	fprintf(fp, "Level1:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------