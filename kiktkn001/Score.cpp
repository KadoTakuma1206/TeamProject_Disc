//-------------------------
//作者　磯江ジュキア
//開幕のスコア表示
//-------------------------
#include "Score.h"
#include "polygon.h"
#include "input.h"


//
////-------------------------------------------------------
////列挙型
//typedef enum
//{
//	R_FiveScore,	//五点用スコアテクスチャ
//	L_FiveScore,	//五点用スコアテクスチャ
//
//	R_ThreeScore,	//三点用スコアテクスチャ
//	L_ThreeScore,	//三点用スコアテクスチャ
//
//	//ROUND_COUNT1,
//	//ROUND_COUNT2,
//	//ROUND_COUNT3,
//
//	SET_COUNT1,
//	SET_COUNT2,
//	SET_COUNT3,
//
//	ScoreState_MAX
//}ScoreType;
//
void UpdatePreBattle(void)
{
	if (GetKeyboardPress(DIK_L))
	{//Lキーが押された
		SetGameSet(1);
	}
	if (GetKeyboardPress(DIK_K))
	{//Lキーが押された
		SetGameSet(2);
	}
	if (GetKeyboardPress(DIK_J))
	{//Lキーが押された
		SetGameSet(3);
	}
}

void SetGameSet(int nSet)
{
		for (int a = 0; a < 2; a++)
		{
			for (int i = 0; i < 2; i++)
			{
				SetPolygon(D3DXVECTOR3(-500.0f + 1000 * a, 50.0f, -250.0f + 500 * i), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, TEXTURE_3PT_R);
				SetPolygon(D3DXVECTOR3(-500.0f + 1000 * a, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, TEXTURE_5PT_R);		 
			}
		}


	SetPolygon(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, TEXTURE_3PT_R);
	SetPolygon(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, TEXTURE_3PT_L);

	if (nSet == 3)
	{
		SetPolygon(D3DXVECTOR3(40.0f, 90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 200, TEXTURE_SET3);

	}
	if (nSet == 2)
	{
		SetPolygon(D3DXVECTOR3(40.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 200, TEXTURE_SET2);

	}
	if (nSet == 1)
	{
		SetPolygon(D3DXVECTOR3(40.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 200, TEXTURE_SET1);
	}
}
