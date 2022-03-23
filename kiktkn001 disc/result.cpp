//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "result.h"
#include "particle.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEXTURE	(14)		//使用するテクスチャの枚数

//=============================================================================
// スタティック変数
//=============================================================================
static LPDIRECT3DTEXTURE9 s_pTexture[MAX_TEXTURE] = {NULL};		//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;				//頂点バッファへのポインタ
static bool bUseResult;											//リザルトを使用してるか

//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{
	//パーティクルの初期化
	InitParticle();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//変数の初期化
	bUseResult = false;

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/勝者.png",
		&s_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/敗者.png",
		&s_pTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/win.png",
		&s_pTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/lose.png",
		&s_pTexture[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ZeroPoint.png",
		&s_pTexture[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/OnePoint.png",
		&s_pTexture[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TwoPoint.png",
		&s_pTexture[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETCOUNT.png",
		&s_pTexture[7]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ThreePoint.png",
		&s_pTexture[8]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/勝者1P.png",
		&s_pTexture[9]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/勝者2P.png",
		&s_pTexture[10]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/敗者1P.png",
		&s_pTexture[11]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/敗者2P.png",
		&s_pTexture[12]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ情報の初期化
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データを4つ進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	//パーティクルの終了処理
	UninitParticle();

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//テクスチャの破棄
		if (s_pTexture[i] != NULL)
		{
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}

		//頂点バッファの破棄
		if (s_pVtxBuff != NULL)
		{
			s_pVtxBuff->Release();
			s_pVtxBuff = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	//パーティクルの更新処理
	UpdateParticle();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	//パーティクルの描画処理
	DrawParticle();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_pTexture[i]);

		//ポリゴンの描画処理
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		//ポリゴンの形
			4 * i,						//頂点の開始場所
			2);							//プリミティブの数
	}
}

//=============================================================================
// リザルトセット処理
//=============================================================================
void SetResult(int nSetCount1, int nSetCount2)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (bUseResult == false)
	{//使用していなければ実行
		//変数の設定
		bUseResult = true;

		if (nSetCount1 > nSetCount2)
		{//1Pが勝利した場合
			//頂点座標の設定
			pVtx[36].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[37].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[38].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[39].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[48].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[49].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[50].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[51].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[8].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[28].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[29].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[30].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f + 70.0f, 0.0f);
			pVtx[31].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f + 70.0f, 0.0f);

			for (int i = 0; i < 200; i++)
			{
				//パーティクルのセット処理
				SetParticle(D3DXVECTOR3(350.0f, 750.0f, 0.0f), 1);
			}
		}

		else if (nSetCount1 < nSetCount2)
		{//2Pが勝利した場合
			//頂点座標の設定
			pVtx[40].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[41].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[42].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[43].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[44].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[45].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[46].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[47].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[8].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[28].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[29].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[30].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f + 70.0f, 0.0f);
			pVtx[31].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f + 70.0f, 0.0f);

			for (int i = 0; i < 200; i++)
			{
				//パーティクルのセット処理
				SetParticle(D3DXVECTOR3(1000.0f, 750.0f, 0.0f), 1);
			}
		}

		else if (nSetCount1 == nSetCount2)
		{//1Pと2Pが同点だった場合 ※バグ修正中
		 //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[4].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[8].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(775.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(975.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[12].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f - 50.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(275.0f - 50.0f, 150.0f + 50.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(475.0f + 50.0f, 150.0f + 50.0f, 0.0f);

			pVtx[28].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[29].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f - 70.0f, 0.0f);
			pVtx[30].pos = D3DXVECTOR3(475.0f - 50.0f, 600.0f + 70.0f, 0.0f);
			pVtx[31].pos = D3DXVECTOR3(775.0f + 50.0f, 600.0f + 70.0f, 0.0f);
		}
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();

	//セットカウントのセット処理
	SetCount(nSetCount1, D3DXVECTOR3(275.0f, 600.0f, 0.0f));
	SetCount(nSetCount2, D3DXVECTOR3(975.0f, 600.0f, 0.0f));
}

//=============================================================================
// セットカウントセット処理
//=============================================================================
void SetCount(int nSetCount, D3DXVECTOR3 pos)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//変数宣言
	D3DXVECTOR3 nCountPos = pos;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nSetCount == 0)
	{//セットカウントが0だった場合実行
		//頂点座標の設定
		pVtx[16].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	else if (nSetCount == 1)
	{//セットカウントが1だった場合実行
		//頂点座標の設定
		pVtx[20].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[21].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[22].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[23].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	else if (nSetCount == 2)
	{//セットカウントが2だった場合実行
	  //頂点座標の設定
		pVtx[24].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[25].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[26].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[27].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	else if (nSetCount == 3)
	{//セットカウントが3だった場合実行
	  //頂点座標の設定
		pVtx[32].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[33].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[34].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[35].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}