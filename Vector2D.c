#include "Vector2D.h"

#define EPSILON 0.0001
#define PI 3.1415926535897932384626433832795
// ---------------------------------------------------------------------------
/*
��2ά����pResult����������ֵ����Ϊ0
*/
void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0.0f;
	pResult->y = 0.0f;
}

// ---------------------------------------------------------------------------
/*
�ֱ�2ά����pResult������ֵ����Ϊx��y
*/
void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------
/*
pResult����ΪpVec0�ķ�����
*/
void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -(pVec0->x);
	pResult->y = -(pVec0->y);
}

// ---------------------------------------------------------------------------
/*
pResult = pVec0 + pVec1
*/
void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// ---------------------------------------------------------------------------
/*
pResult = pVec0 - pVec1
*/
void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------
/*
pResult����Ϊ����pVec0�ĵ�λ����
*/
void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float mole;
	mole = pVec0->x * pVec0->x + pVec0->y * pVec0->y;
	mole = sqrt(mole);
	if (mole < EPSILON)
		printf("ERROR!");
	else {
		pResult->x = pVec0->x / mole;
		pResult->y = pVec0->y / mole;
	}
}

// ---------------------------------------------------------------------------
/*
pResult����Ϊ����pVec0����c���Ľ��
*/
void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------
/*
pResult = ����pVec0����c�� + pVec1
*/
void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c + pVec1->x;
	pResult->y = pVec0->y * c + pVec1->y;
}

// ---------------------------------------------------------------------------
/*
pResult = ����pVec0����c�� - pVec1
*/
void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c - pVec1->x;
	pResult->y = pVec0->y * c - pVec1->y;
}

// ---------------------------------------------------------------------------
/*
��������pVec0�ĳ���
*/
float Vector2DLength(Vector2D *pVec0)
{
	float mole;
	mole = pVec0->x * pVec0->x + pVec0->y * pVec0->y;
	mole = sqrt(mole);
	return mole;
}

// ---------------------------------------------------------------------------
/*
��������pVec0���ȵ�ƽ��������ƽ��������
*/
float Vector2DSquareLength(Vector2D *pVec0)
{
	float mole;
	mole = pVec0->x * pVec0->x + pVec0->y * pVec0->y;
	return mole;
}

// ---------------------------------------------------------------------------
/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ���
*/
float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	float distance;
	distance = (pVec0->x - pVec1->x) * (pVec0->x - pVec1->x) + (pVec0->y - pVec1->y) * (pVec0->y - pVec1->y);
	distance = sqrt(distance);
	return distance;
}

// ---------------------------------------------------------------------------
/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ����ƽ��������ƽ��������
*/
float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	float distance;
	distance = (pVec0->x - pVec1->x) * (pVec0->x - pVec1->x) + (pVec0->y - pVec1->y) * (pVec0->y - pVec1->y);
	return distance;
}

// ---------------------------------------------------------------------------
/*
����pVec0��pVec1�ĵ��
*/
float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	float dot;
	dot = pVec0->x * pVec1->x + pVec0->y * pVec1->y;
	return dot;
}

// ---------------------------------------------------------------------------
/*
�����굽ֱ�������µ�λ������ת����angleΪ��������30��
*/
void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle * PI / 180);
	pResult->y = sin(angle * PI / 180);
}

// ---------------------------------------------------------------------------
/*
�����굽ֱ�������µ�λ������ת����angleΪ����
*/
void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle);
	pResult->y = sin(angle);
}

// ---------------------------------------------------------------------------
