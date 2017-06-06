/* Project:		practice1
   File Name:	Level1.h
   Author:		张仕钊
   Date:		2017-3-28
   Purpose:		Level模块  */
#ifndef _Level1
#define _Level1
enum TYPE
{
	// 游戏对象类型列表
	TYPE_HERO,			//0
	TYPE_WALL,		    //1
	TYPE_SOURCE,        //2
	

	TYPE_NUM
};
void Load1(void);
void Ini1(void);
void Update1(void);
void Draw1(void);
void Free1(void);
void Unload1(void);
#endif
