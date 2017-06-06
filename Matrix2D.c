#include "Matrix2D.h"
#define PI 3.1415926535897932384626433832795

/*
将pResult设置为单位矩阵
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	pResult->m[0][0] = 1.0f;
	pResult->m[1][1] = 1.0f;
	pResult->m[2][2] = 1.0f;
	pResult->m[0][1] = 0.0f;
	pResult->m[0][2] = 0.0f;
	pResult->m[1][0] = 0.0f;
	pResult->m[1][2] = 0.0f;
	pResult->m[2][0] = 0.0f;
	pResult->m[2][1] = 0.0f;
}

// ---------------------------------------------------------------------------

/*
计算pMtx的转置，并将结果放到pResult
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			pResult->m[j][i] = pMtx->m[i][j];
		}
	}
}

// ---------------------------------------------------------------------------

/*
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D pP;
	pP.m[0][0] = pMtx0->m[0][0] * pMtx1->m[0][0] + pMtx0->m[0][1] * pMtx1->m[1][0] + pMtx0->m[0][2] * pMtx1->m[2][0];
	pP.m[0][1] = pMtx0->m[0][0] * pMtx1->m[0][1] + pMtx0->m[0][1] * pMtx1->m[1][1] + pMtx0->m[0][2] * pMtx1->m[2][1];
	pP.m[0][2] = pMtx0->m[0][0] * pMtx1->m[0][2] + pMtx0->m[0][1] * pMtx1->m[1][2] + pMtx0->m[0][2] * pMtx1->m[2][2];

	pP.m[1][0] = pMtx0->m[1][0] * pMtx1->m[0][0] + pMtx0->m[1][1] * pMtx1->m[1][0] + pMtx0->m[1][2] * pMtx1->m[2][0];
	pP.m[1][1] = pMtx0->m[1][0] * pMtx1->m[0][1] + pMtx0->m[1][1] * pMtx1->m[1][1] + pMtx0->m[1][2] * pMtx1->m[2][1];
	pP.m[1][2] = pMtx0->m[1][0] * pMtx1->m[0][2] + pMtx0->m[1][1] * pMtx1->m[1][2] + pMtx0->m[1][2] * pMtx1->m[2][2];

	pP.m[2][0] = pMtx0->m[2][0] * pMtx1->m[0][0] + pMtx0->m[2][1] * pMtx1->m[1][0] + pMtx0->m[2][2] * pMtx1->m[2][0];
	pP.m[2][1] = pMtx0->m[2][0] * pMtx1->m[0][1] + pMtx0->m[2][1] * pMtx1->m[1][1] + pMtx0->m[2][2] * pMtx1->m[2][1];
	pP.m[2][2] = pMtx0->m[2][0] * pMtx1->m[0][2] + pMtx0->m[2][1] * pMtx1->m[1][2] + pMtx0->m[2][2] * pMtx1->m[2][2];

	pResult->m[0][0] = pP.m[0][0];
	pResult->m[0][1] = pP.m[0][1];
	pResult->m[0][2] = pP.m[0][2];
	pResult->m[1][0] = pP.m[1][0];
	pResult->m[1][1] = pP.m[1][1];
	pResult->m[1][2] = pP.m[1][2];
	pResult->m[2][0] = pP.m[2][0];
	pResult->m[2][1] = pP.m[2][1];
	pResult->m[2][2] = pP.m[2][2];
}

// ---------------------------------------------------------------------------

/*
将pResult设置为平移矩阵，平移位移为x和y
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
将pResult设置为缩放矩阵，x和y分别为水平和垂直方向的缩放比例
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
将pResult设置为旋转矩阵，旋转量为Angle，为度数
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	float angle;
	angle = Angle * PI / 180;
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = cos(angle);
	pResult->m[0][1] = -sin(angle);
	pResult->m[1][0] = sin(angle);
	pResult->m[1][1] = cos(angle);
}

// ---------------------------------------------------------------------------

/*
将pResult设置为旋转矩阵，旋转量为Angle，为弧度
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = cos(Angle);
	pResult->m[0][1] = -sin(Angle);
	pResult->m[1][0] = sin(Angle);
	pResult->m[1][1] = cos(Angle);
}

// ---------------------------------------------------------------------------

/*
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D pP;
	pP.x = pMtx->m[0][0] * pVec->x + pMtx->m[0][1] * pVec->y + pMtx->m[0][2];
	pP.y = pMtx->m[1][0] * pVec->x + pMtx->m[1][1] * pVec->y + pMtx->m[1][2];

	pResult->x = pP.x;
	pResult->y = pP.y;
}

// ---------------------------------------------------------------------------
