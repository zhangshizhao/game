#include "Math2D.h"
#include "stdio.h"
#define EPSILON 0.0001f
/*
����pP�Ƿ���Բ��Բ��pCenter���뾶pRadius��������ײ
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
����pPos�Ƿ�����Σ�����pRect�����Width���߶�Height��������ײ
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
Circle0: Բ��pCenter0���뾶pRadius0
Circle1: Բ��pCenter1���뾶pRadius1
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
������������Ƿ�����ײ
Rectangle0: ����pRect0�����Width0���߶�Height0
Rectangle1: ����pRect1�����Width1���߶�Height0
0��ײ1�ұ߷���1
0��ײ1��߷���2
0��ײ1�ϱ߷���3
0��ײ1�±߷���4
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
