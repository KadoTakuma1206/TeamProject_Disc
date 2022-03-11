//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _POLYGON_H_			//このマクロ定義がされなかったら
#define _POLYGON_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------

#include "main.h"

//-----------------------------------------------------------------------------
//列挙型の定義
//-----------------------------------------------------------------------------

//テクスチャ列挙型
typedef enum
{
	TEXTURE_0 = 0,		//テクスチャがない状態
	TEXTURE_1,			//床テクスチャ
	TEXTURE_2,			//壁テクスチャ
	TEXTURE_MAX			//テクスチャの最大数
}TexturetPolygon;

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------

void InitPolygon(void);//初期化
void UninitPolygon(void);//終了処理
void UpdatePolygon(void);//更新処理
void DrawPolygon(void);//描画処理
void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadiusX, float fRadiusZ, TexturetPolygon Texturetstate);

#endif
