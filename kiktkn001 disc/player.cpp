//=============================================================================
//
// モデル処理 [model.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------

#include "player.h"
#include "camera.h"
#include "input.h"
#include "calculation.h"
#include "polygon.h"
#include "disc.h"
#include "collision.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------

#define ANGLE_DAMPING_COEFFICIENT	(0.07f)					//角度の減衰係数
#define SCALE_DOWN					(1.0f)					//スケールサイズの変更
#define ANCHOR_POINT_MAX			(120)					//カメラの移動点
#define GRAVITY_MAX					(3.0f)					//重力
#define ACCELERATION_MAX			(1.0f)					//加速の限界
#define PLAYER_SPEED				(7.0f)


//-----------------------------------------------------------------------------
//構造体
//-----------------------------------------------------------------------------

//モーション再生中に必要な情報構造体
typedef struct
{
	int nFrameCnt;					//現在のフレーム数
	int nNowRebirthKeySet;			//再生中のキーセット番号
	int nNowRebirthMotion;			//再生中のモーション番号
}PlayerMotionData;

//モデルパターン構造体
typedef struct
{
	LPD3DXMESH pMesh = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat = NULL;		//マテリアル情報へのポインタ
	DWORD nNumMat = 0;					//マテリアル情報の数
	bool bUse;							//使用しているかどうか
}PlayerPartsPattern;

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------

D3DXMATRIX g_PlayerPartsmtxWorld[PARENT_MAX];				//ワールドマトリックス(プレイヤーパーツ)
PlayerPartsPattern g_PartsPattern[PARENT_MAX];				//モデルパターン構造体
Player g_Player;											//プレイヤーの構造体
char g_sPlayerModelFilename[PARENT_MAX][256];				//ファイル名
PlayerMotionData g_MotionPlayer;							//モーションに必要なデータ構造体
float g_fDeceleration;										//プレイヤー移動量の減速割合（ゲーム中用）
D3DXVECTOR3 g_PlayerPos;									//ゲーム中の横移動などをやるためのPOS
int g_nLineNmn = 0;

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------

void PlayerMove(void);
void MotionsetPlayer(void);
void ChangeMotion(int nMotion, int nKey);

//*****************************************************************************
//プレイヤーの初期化
//*****************************************************************************

void InitPlayer(void)
{
	//プレイヤーに必要な全ワールドマトリックスの初期化
	ZeroMemory(&g_PlayerPartsmtxWorld, sizeof(g_PlayerPartsmtxWorld));
	//プレイヤーの構造体の初期化
	ZeroMemory(&g_PartsPattern, sizeof(g_PartsPattern));
	ZeroMemory(&g_Player, sizeof(g_Player));
	//モーションに必要なデータ構造体の初期化
	ZeroMemory(&g_MotionPlayer, sizeof(g_MotionPlayer));
	//POS初期化
	ZeroMemory(&g_PlayerPos, sizeof(g_PlayerPos));

	//プレイヤー移動量の減速割合の初期化
	g_fDeceleration = 0.0f;
}

//*****************************************************************************
//プレイヤーの終了処理
//*****************************************************************************

void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		//メッシュの破棄
		if (g_PartsPattern[nCnt].pMesh != NULL)
		{
			g_PartsPattern[nCnt].pMesh->Release();
			g_PartsPattern[nCnt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_PartsPattern[nCnt].pBuffMat != NULL)
		{
			g_PartsPattern[nCnt].pBuffMat->Release();
			g_PartsPattern[nCnt].pBuffMat = NULL;
		}

	}
}

//*****************************************************************************
//プレイヤーの更新処理
//*****************************************************************************

void UpdatePlayer(void)
{
	//カメラの情報の取得（ポインタ）
	Camera *pCamera = GetCamera();

	//プレイヤーの移動
	PlayerMove();

	//ディスクの情報の取得
	Disc *pDisc = GetDisc();
	//持つ処理
	for (int nCnt = 0; nCnt < MAX_DISC; nCnt++)
	{
		if (pDisc[nCnt].bUse
			&& CollisionCircle(pDisc[nCnt].pos,30.0f, g_PlayerPos,30.0f)
			&& !g_Player.bDiscHave
			&& GetKeyboardPress(DIK_RETURN))
		{
			g_Player.nNumDisc = nCnt;
			g_Player.bDiscHave = true;
			break;
		}
	}

	if (g_Player.bDiscHave)
	{
		SetDiscPos(g_Player.nNumDisc, g_PlayerPos);
	}

	if (!GetKeyboardPress(DIK_RETURN)
		&& g_Player.bDiscHave)
	{//右キーが押された
		g_Player.bDiscHave = false;
		pDisc[g_Player.nNumDisc].move.x *= - 1.0f;
	}

	//モーション
	if (g_MotionPlayer.nNowRebirthMotion == g_Player.PlayerState)
	{
		MotionsetPlayer();
	}
}

//*****************************************************************************
//プレイヤーの描画処理
//*****************************************************************************

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRootFirst;			//大元の親の親ワールドマトリックス
	D3DXMATRIX mtxRoot;					//大元の親のワールドマトリックス
	D3DXMATRIX mtxRot, mtxTrans;		//計算用のマトリックス

										//ワールドマトリックスの初期化（大元の親の親）
	D3DXMatrixIdentity(&mtxRootFirst);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&mtxRootFirst, &mtxRootFirst, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_PlayerPos.x, g_PlayerPos.y, g_PlayerPos.z);
	D3DXMatrixMultiply(&mtxRootFirst, &mtxRootFirst, &mtxTrans);

	//ワールドマトリックスの初期化（大元の親）
	D3DXMatrixIdentity(&mtxRoot);

	D3DXMatrixScaling(&mtxRot,
		SCALE_DOWN, SCALE_DOWN, SCALE_DOWN);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRot);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxTrans);

	//モデルのマトリックス　＊　親のワールドマトリックス
	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRootFirst);

	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		if (g_Player.Parts[nCnt].bUse)
		{
			D3DMATERIAL9 matDef;			//現在のマテリアル保存
			D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

											//ワールドマトリックスの初期化（子）
			D3DXMatrixIdentity(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex]);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Player.Parts[nCnt].rot.y, g_Player.Parts[nCnt].rot.x, g_Player.Parts[nCnt].rot.z);

			D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxRot);

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_Player.Parts[nCnt].pos.x, g_Player.Parts[nCnt].pos.y, g_Player.Parts[nCnt].pos.z);
			D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxTrans);

			if (g_Player.Parts[nCnt].nParent < 0)
			{
				//モデルのマトリックス　＊　親のワールドマトリックス
				D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxRoot);
			}
			else
			{
				//モデルのマトリックス　＊　親のワールドマトリックス
				D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nParent]);
			}

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex]);

			//現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_PartsPattern[g_Player.Parts[nCnt].nIndex].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PartsPattern[g_Player.Parts[nCnt].nIndex].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデルパーツの描画
				g_PartsPattern[g_Player.Parts[nCnt].nIndex].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------------------
//プレイヤーの移動
//-----------------------------------------------------------------------------
void PlayerMove(void)
{
	//過去の位置の保存
	g_Player.posOld = g_PlayerPos + g_Player.pos;

	//カメラの情報の取得（ポインタ）
	Camera *pCamera = GetCamera();

	//視点移動
	g_Player.PlayerState = PLAYER_RUN;
	g_MotionPlayer.nNowRebirthMotion = PLAYER_RUN;
	if (GetKeyboardPress(DIK_W))
	{//上キーが押された
		if (GetKeyboardPress(DIK_A))
		{
			g_Player.rotDest.y = D3DX_PI * 0.75f + pCamera->rot.y;
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * g_Player.fMove;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * g_Player.fMove;
		}
		else if (GetKeyboardPress(DIK_D))
		{
			g_Player.rotDest.y = D3DX_PI * -0.75f + pCamera->rot.y;
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * -0.75f) * g_Player.fMove;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * -0.75f) * g_Player.fMove;
		}
		else
		{
			g_Player.rotDest.y = D3DX_PI + pCamera->rot.y;
			g_Player.move.x += sinf(pCamera->rot.y) * g_Player.fMove;
			g_Player.move.z += cosf(pCamera->rot.y) * g_Player.fMove;
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{//下キーが押された
		if (GetKeyboardPress(DIK_A))
		{
			g_Player.rotDest.y = D3DX_PI * 0.25f + pCamera->rot.y;
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * g_Player.fMove;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * g_Player.fMove;
		}
		else if (GetKeyboardPress(DIK_D))
		{
			g_Player.rotDest.y = D3DX_PI * -0.25f + pCamera->rot.y;
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI * -0.25f) * g_Player.fMove;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * -0.25f) * g_Player.fMove;
		}
		else
		{
			g_Player.rotDest.y = pCamera->rot.y;
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * g_Player.fMove;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * g_Player.fMove;
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{//左キーが押された
		g_Player.rotDest.y = D3DX_PI * 0.5f + pCamera->rot.y;
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * g_Player.fMove;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * g_Player.fMove;
	}
	else if (GetKeyboardPress(DIK_D))
	{//右キーが押された
		g_Player.rotDest.y = D3DX_PI * -0.5f + pCamera->rot.y;
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * g_Player.fMove;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * g_Player.fMove;
	}
	else
	{
		ZeroMemory(&g_Player.move, sizeof(g_Player.move));
		
			g_Player.PlayerState = PLAYER_NEUTRAL;
			g_MotionPlayer.nNowRebirthMotion = PLAYER_NEUTRAL;
			//モーションの初期化とキーのセット変更
			//ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
		
	}

	//rotが規定数より超えたときの補正込み
	g_Player.rot.y += Normalization(g_Player.rotDest.y/*目的の角度*/ - g_Player.rot.y/*現在の角度*/)
		* ANGLE_DAMPING_COEFFICIENT;

	//rotが規定数より超えたときの補正
	g_Player.rot.y = Normalization(g_Player.rot.y);

	//プレイヤーPOSの更新
	if (g_Player.move.x > PLAYER_SPEED)
	{
		g_Player.move.x = PLAYER_SPEED;
	}
	else if (g_Player.move.x < -PLAYER_SPEED)
	{
		g_Player.move.x = -PLAYER_SPEED;
	}
	if (g_Player.move.z > PLAYER_SPEED)
	{
		g_Player.move.z = PLAYER_SPEED;
	}
	else if (g_Player.move.z < -PLAYER_SPEED)
	{
		g_Player.move.z = -PLAYER_SPEED;
	}

	g_PlayerPos += g_Player.move * 1.0f;

	//プレイヤーの胴体のPOS更新(ジャンプ処理)
	g_Player.pos.y -= (70.0f - g_Player.pos.y) * 0.1f;
	

	//加速処理
	if (g_fDeceleration < 0.9f)
	{
		g_fDeceleration += (ACCELERATION_MAX - g_fDeceleration) * 0.01f;
	}

	//床
	if (g_Player.pos.y <= 0.0f)
	{
		g_Player.pos.y = 0.0f;
	}
}

//-----------------------------------------------------------------------------
//プレイヤー情報の取得（ポインタ）
//-----------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_Player;
}

//-----------------------------------------------------------------------------
//プレイヤー情報の取得（ポインタではない）
//-----------------------------------------------------------------------------
Player GetPlayerData(void)
{
	return g_Player;
}

//-----------------------------------------------------------------------------
//モデルタイプ読み込み処理
//-----------------------------------------------------------------------------

HRESULT LoadPlayerPattern(HWND hWnd, char *sXFilePath)
{

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	for (int nCntPatn = 0; nCntPatn < PARENT_MAX; nCntPatn++)
	{
		if (!g_PartsPattern[nCntPatn].bUse)
		{

			//Xファイルの読み込み
			D3DXLoadMeshFromX(sXFilePath,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_PartsPattern[nCntPatn].pBuffMat,
				NULL,
				&g_PartsPattern[nCntPatn].nNumMat,
				&g_PartsPattern[nCntPatn].pMesh);

			g_PartsPattern[nCntPatn].bUse = true;

			return S_OK;
		}
	}

	MessageBox(hWnd, "読み込み可能モデル数を超えています", "警告！", MB_ICONWARNING);
	return E_FAIL;
}

//-----------------------------------------------------------------------------
//プレイヤーのセット処理
//-----------------------------------------------------------------------------

void SetPlayer(Player Player)
{
	g_Player = Player;



	g_Player.rotDest.y = D3DX_PI;
	g_Player.rot.y = D3DX_PI;
	g_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.PlayerState = PLAYER_NEUTRAL;
	g_MotionPlayer.nNowRebirthMotion = PLAYER_NEUTRAL;
	//モーションの初期化とキーのセット変更
	ChangeMotion(0, 1);




	int nNumVix;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

						//モデルのサイズの比較用初期値
	g_Player.vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	g_Player.vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//頂点数の取得
	nNumVix = g_PartsPattern[0].pMesh->GetNumVertices();

	//頂点フォーマット取得
	sizeFVF = D3DXGetFVFVertexSize(g_PartsPattern[0].pMesh->GetFVF());

	//頂点ロック
	g_PartsPattern[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//すべての頂点POSの取得
	for (int nCntVtx = 0; nCntVtx < nNumVix; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Player.vtxMax.x < vtx.x)
		{//X
			g_Player.vtxMax.x = vtx.x;
		}
		if (g_Player.vtxMin.x > vtx.x)
		{
			g_Player.vtxMin.x = vtx.x;
		}

		if (g_Player.vtxMax.y < vtx.y)
		{//Y
			g_Player.vtxMax.y = vtx.y;
		}
		if (g_Player.vtxMin.y > vtx.y)
		{
			g_Player.vtxMin.y = vtx.y;
		}

		if (g_Player.vtxMax.z < vtx.z)
		{//Z
			g_Player.vtxMax.z = vtx.z;
		}
		if (g_Player.vtxMin.z > vtx.z)
		{
			g_Player.vtxMin.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	g_Player.vtxMax *= SCALE_DOWN;
	g_Player.vtxMin *= SCALE_DOWN;


	//頂点アンロックa
	g_PartsPattern[0].pMesh->UnlockVertexBuffer();
}

//-----------------------------------------------------------------------------
//モーション再生処理
//-----------------------------------------------------------------------------

void MotionsetPlayer(void)
{
	int nMotion = g_MotionPlayer.nNowRebirthMotion;
	int nKey = g_MotionPlayer.nNowRebirthKeySet;
	int nFrame = g_Player.Motion[nMotion].nFrame[nMotion];
	int nNumKey = g_Player.Motion[nMotion].nNumKey;

	if (nFrame <= 0)
	{//テキスト設定フレーム数が０以下だった時
		nFrame = 1;
	}


	//モーション再生（全パーツ）D3DXVec3Normalize
	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		if (g_Player.Parts[nCnt].bUse)
		{
			D3DXVECTOR3 move, rot;


			move = (g_Player.Parts[nCnt].posMotionset[nMotion][nKey] - g_Player.Parts[nCnt].posMotionset[nMotion][((nKey - 1) + nNumKey) % nNumKey]) / (float)g_Player.Motion[nMotion].nFrame[nKey];
			//POSの再生（ローカル座標）
			g_Player.Parts[nCnt].pos += move;

			rot = (g_Player.Parts[nCnt].rotMotionset[nMotion][nKey] - g_Player.Parts[nCnt].rotMotionset[nMotion][((nKey - 1) + nNumKey) % nNumKey]) / (float)g_Player.Motion[nMotion].nFrame[nKey];

			//ROTの再生
			g_Player.Parts[nCnt].rot += rot;
		}
	}


	//フレームの加算
	g_MotionPlayer.nFrameCnt++;

	if (g_Player.Motion[nMotion].nFrame[nKey] <= g_MotionPlayer.nFrameCnt)
	{//フレーム数が設定の値を超えたら

	 //モーションの初期化とキーのセット変更
		ChangeMotion(nMotion, nKey);

		//再生中のキー数の加算
		g_MotionPlayer.nNowRebirthKeySet++;
		//フレームの初期化
		g_MotionPlayer.nFrameCnt = 0;

		if (g_Player.Motion[nMotion].nNumKey <= g_MotionPlayer.nNowRebirthKeySet)
		{//再生中のキー数が設定の値を超えたら
			if (g_Player.Motion[nMotion].nLoop == 1)
			{
				g_MotionPlayer.nNowRebirthKeySet = 0;

				//モーションの初期化とキーのセット変更
				ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
			}
			else if (nMotion == PLAYER_HAVE)
			{
				g_MotionPlayer.nNowRebirthKeySet = 0;
				g_MotionPlayer.nNowRebirthMotion = 1;

				//モーションの初期化とキーのセット変更
				//ChangeMotion(g_MotionPlayer.nNowRebirthMotion, g_MotionPlayer.nNowRebirthKeySet);
			}
			else
			{//現在再生中のモーションからランモーションに変更
				g_MotionPlayer.nNowRebirthKeySet = 0;
				g_MotionPlayer.nNowRebirthMotion = 1;
				//モーションの初期化とキーのセット変更
				ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//モーションの初期化とキーのセット変更
//-----------------------------------------------------------------------------
void ChangeMotion(int nMotion, int nKey)
{
	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		if (g_Player.Parts[nCnt].bUse)
		{
			//g_Player.Parts[nCnt].pos = g_Player.Parts[nCnt].posMotionset[nMotion][nKey];
			g_Player.Parts[nCnt].rot = g_Player.Parts[nCnt].rotMotionset[nMotion][nKey];

		}
	}


}

//-----------------------------------------------------------------------------
//プレイヤーの位置の参照
//-----------------------------------------------------------------------------

D3DXVECTOR3 GetPosPlayer(void)
{
	return g_PlayerPos;
}