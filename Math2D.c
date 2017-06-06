#include "Math2D.h"
#include "stdio.h"
#define EPSILON 0.0001f
/*
检测点pP是否与圆（圆心pCenter，半径pRadius）发生碰撞
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	float distance;
	distance = (pP->x - pCenter->x) * (pP->x - pCenter->x) + (pP->y - pCenter->y) * (pP->y - pCenter->y);
	Radius = Radius * Radius;
	if ((distance - Radius) <= EPSILON)
		return 1;
	else
		return 0;
}


/*
检测点pPos是否与矩形（中心pRect，宽度Width，高度Height）发生碰撞
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	if (pPos->x < (pRect->x - Width / 2)) return 0;
	if (pPos->x > (pRect->x + Width / 2)) return 0;
	if (pPos->y < (pRect->y - Height / 2)) return 0;
	if (pPos->y < (pRect->y + Height / 2)) return 0;
	return 1;
}

/*
Circle0: 圆心pCenter0，半径pRadius0
Circle1: 圆心pCenter1，半径pRadius1
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	float distance,add;
	distance = (pCenter0->x - pCenter1->x) * (pCenter0->x - pCenter1->x) + (pCenter0->y - pCenter1->y) * (pCenter0->y - pCenter1->y);
	add = Radius0 + Radius1;
	add = add * add;
	if ((distance - add) <= EPSILON)
		return 1;
	else
		return 0;
}

/*
检测两个矩形是否发生碰撞
Rectangle0: 中心pRect0，宽度Width0，高度Height0
Rectangle1: 中心pRect1，宽度Width1，高度Height0
0碰撞1右边返回1
0碰撞1左边返回2
0碰撞1上边返回3
0碰撞1下边返回4
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	if ((pRect0->x - Width0 / 2) > (pRect1->x + Width1 / 2)) return 0;
	if ((pRect0->x + Width0 / 2) < (pRect1->x - Width1 / 2)) return 0;
	if ((pRect0->y - Height0 / 2) > (pRect1->y + Height1 / 2)) return 0;
	if ((pRect0->y + Height0 / 2) < (pRect1->y - Height1 / 2)) return 0;

	if (((pRect0->y - Height0 / 2) < (pRect1->y + Height1 / 2)) && ((pRect0->y + Height0 / 2) > (pRect1->y - Height1 / 2))) {
		if (abs((pRect0->x - Width0 / 2) - (pRect1->x + Width1 / 2)) <= 2) return 2;
		if (abs((pRect0->x + Width0 / 2) - (pRect1->x - Width1 / 2)) <= 2) return 1;
	}
	if (((pRect0->x - Width0 / 2) < (pRect1->x + Width1 / 2)) && ((pRect0->x + Width0 / 2) > (pRect1->x - Width1 / 2))) {
		if (abs((pRect0->y - Height0 / 2) - (pRect1->y + Height1 / 2)) <= 2) return 3;
		if (abs((pRect0->y + Height0 / 2) - (pRect1->y - Height1 / 2)) <= 2) return 4;
	}
}
