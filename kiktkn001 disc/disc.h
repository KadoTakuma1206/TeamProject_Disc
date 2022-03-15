//-------------------------------------
//
//ディスクヘッダー[disc.h]
//Author:梶田大夢
//
//-------------------------------------
#ifndef  _DISC_H_						//このマクロ定義がされてなかったら
#define  _DISC_H_						//二重インクルード防止のマクロ定義

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_DISC		(1)			//ディスクの最大数
#define MAX_SPEED		(1.0f)		//移動速度

typedef enum
{
	E_PLAYER_1 = 0,					//1Pのディスク
	E_PLAYER_2,						//2Pのディスク
	E_PLAYER_MAX
}Player;

typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 posOld;								//前の位置
	D3DXVECTOR3 move;								//移動量
	D3DXVECTOR3 size;								//サイズ
	D3DXVECTOR3 rotDisc;							//向き
	D3DXVECTOR3 rotDestDisc;
	D3DXVECTOR3 vtxMinDisc;							//最大頂点
	D3DXVECTOR3 vtxMaxDisc;							//最小頂点
	bool bUse;										//使われているか
	bool bGoal;										//ゴールしたかどうか
	int nGoal;										//どちらがゴールしたか
	D3DXMATRIX mtxWorldDisc;						//ワールドマトリックス
}Disc;

//プロトタイプ宣言
void InitDisc(void);			//ディスクの初期化処理
void UninitDisc(void);			//ディスクの終了処理
void UpdateDisc(void);			//ディスクの更新処理
void DrawDisc(void);			//ディスクの描画処理
void SetDisc(Player player);	//ディスクの設定処理

Disc * GetDisc(void);

#endif
