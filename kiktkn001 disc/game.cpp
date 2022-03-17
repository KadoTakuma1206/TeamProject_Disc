//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "result.h"
#include "player.h"
#include "disc.h"
#include "load.h"
#include "goal.h"
#include <time.h>
#include "billboard.h"

//=============================================================================
// スタティック変数
//=============================================================================
static bool g_bPause = false;		//ポーズ中かどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	//乱数の初期化
	srand((unsigned int)time(0));

	//プレイヤー初期化
	InitPlayer();

	//ロード処理（プレイヤー）
	LoadSetPlayer();

	//ポリゴンの初期化処理
	InitPolygon();

	//ビルボードの初期化処理
	InitBillboard();

	//ゴールの初期化処理
	InitGoal();

	//ディスクの初期化処理
	InitDisc();

	//ディスクの設定
	SetDisc(E_PLAYER_1);
	//SetDisc(E_PLAYER_2);

	//ディスクの位置を強制的に変える
	SetDiscPos(0, D3DXVECTOR3(500.0f, 0.0f, 0.0f));

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//リザルトの初期化処理
	InitResult();

	//ポーズ画面の初期化処理
	InitPause();		

	//ポーズ解除
	g_bPause = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	//ポリゴンの終了処理
	UninitPolygon();

	//ビルボードの終了処理
	UninitBillboard();

	//ディスクの終了処理
	UninitDisc();

	//ゴールの終了処理
	UninitGoal();

	//プレイヤー終了処理
	UninitPlayer();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//リザルトの終了処理
	UninitResult();

	//ポーズ画面の終了処理
	UninitPause();		
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	//ポーズ情報の取得
	PAUSE *pPause = GetPause();

	if (GetKeyboardTrigger(DIK_P) == true && g_bPause == false)
	{//ポーズキー(Pキー)が押された
		g_bPause = g_bPause ? false : true;		//trueならfalse,falseならtrue 三項演算子
	}

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの更新処理
		UpdatePause();
	}

	if (g_bPause == false /*&& nTimer != 0*/)
	{//ポーズ中でなければ
		//ポリゴンの更新処理
		UpdatePolygon();

		//ディスクの更新処理
		UpdateDisc();

		//ゴールの更新処理
		UpdateGoal();

		//プレイヤーの更新処理
		UpdatePlayer();

		//ビルボードの更新処理
		UpdatePlayer();

		//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//カメラの設定処理
	SetCamera();

	//ポリゴンの描画処理
	DrawPolygon();

	//ディスクの描画処理
	DrawDisc();

	//ゴールの描画
	DrawGoal();

	//プレイヤーの描画処理
	DrawPlayer();

	//ビルボードの描画処理
	DrawBillboard();

	//リザルトの描画処理
	DrawResult();

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}
}

//=============================================================================
// ポーズの有効無効設定
//=============================================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}