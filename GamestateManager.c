/* Project:		practice1
   File Name:	GamestateManager.c
   Author:		’≈ ÀÓ»
   Date:		2017-3-28
   Purpose:		GSMƒ£øÈ  */
#include"System.h"
#include"GameStateList.h"
#include"GamestateManager.h"
#include"Level1.h"
#include"Level2.h"
#include"Level3.h"
#include"Menu.h"


void GSM_Initialize(int FLAGE)
{
    Previous = Current = FLAGE;
    Next = FLAGE;
    fprintf(fp,"GSM:Initialize\n");
}

void GSM_Update(int FLAGE)
{ 
     if(FLAGE == GS_L1)
     {
            pLoad = Load1;
            pIni = Ini1;
            pUpdate = Update1;
            pDraw = Draw1;
            pFree = Free1;
            pUnload = Unload1;
      }
      else if(FLAGE == GS_L2)
      {
            pLoad = Load2;
            pIni = Ini2;
            pUpdate = Update2;
            pDraw = Draw2;
            pFree = Free2;
            pUnload = Unload2;
      }
	  else if (FLAGE == GS_L0)
	  {
		  pLoad = Load0;
		  pIni = Ini0;
		  pUpdate = Update0;
		  pDraw = Draw0;
		  pFree = Free0;
		  pUnload = Unload0;
	  }
	  else if (FLAGE == GS_L3)
	  {
		  pLoad = Load3;
		  pIni = Ini3;
		  pUpdate = Update3;
		  pDraw = Draw3;
		  pFree = Free3;
		  pUnload = Unload3;
	  }
	 Current = Next;
    fprintf(fp,"GSM:Update\n");
}
