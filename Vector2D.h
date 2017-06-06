#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <stdio.h>
// 2ά����
typedef struct Vector2D
{
	float x, y;
}Vector2D;

/*
��2ά����pResult����������ֵ����Ϊ0
*/
void Vector2DZero(Vector2D *pResult);

/*
�ֱ�2ά����pResult������ֵ����Ϊx��y
*/
void Vector2DSet(Vector2D *pResult, float x, float y);

/*
pResult����ΪpVec0�ķ�����
*/
void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0);

/*
pResult = pVec0 + pVec1
*/
void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

/*
pResult = pVec0 - pVec1
*/
void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

/*
pResult����Ϊ����pVec0�ĵ�λ����
*/
void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0);

/*
pResult����Ϊ����pVec0����c���Ľ��
*/
void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c);

/*
pResult = ����pVec0����c�� + pVec1 
*/
void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

/*
pResult = ����pVec0����c�� - pVec1 
*/
void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

/*
��������pVec0�ĳ���
*/
float Vector2DLength(Vector2D *pVec0);

/*
��������pVec0���ȵ�ƽ��������ƽ��������
*/
float Vector2DSquareLength(Vector2D *pVec0);

/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ���
*/
float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1);

/*
pVec0��pVec1��2ά�ռ�������㣬������������ľ����ƽ��������ƽ��������
*/
float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1);

/*
����pVec0��pVec1�ĵ��
*/
float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1);

/*
�����굽ֱ�������µ�λ������ת����angleΪ��������30��
*/
void Vector2DFromAngleDeg(Vector2D *pResult, float angle);

/*
�����굽ֱ�������µ�λ������ת����angleΪ����
*/
void Vector2DFromAngleRad(Vector2D *pResult, float angle);

#endif