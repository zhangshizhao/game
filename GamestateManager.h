/* Project:		practice1
   File Name:	GamestateManager.h
   Author:		’≈ ÀÓ»
   Date:		2017-3-28
   Purpose:		GSMƒ£øÈ  */

#ifndef _GameStateManager
#define _GameStateManager
int Previous,Current,Next;
void (*pLoad)(void);
void (*pIni)(void);
void (*pUpdate)(void);
void (*pDraw)(void);
void (*pFree)(void);
void (*pUnload)(void);

void GSM_Initialize(int FLAGE);
void GSM_Update(int FLAGE);


#endif
