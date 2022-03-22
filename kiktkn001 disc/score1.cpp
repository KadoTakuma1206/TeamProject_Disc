#include"score1.h"

//マクロ定義
#define NUM_SCORE (6)		//桁数
#define SCORE_SIZE	20

//グローバル変数
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;					//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = NULL;				//頂点バッファへのポインタ
static D3DXVECTOR3 g_posScore;									//スコアの位置

static int g_nScore;											//スコアの値

//=========================
//スコアの初期化処理
//=========================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTexture);

	g_posScore = D3DXVECTOR3(25.0f, 30.0f, 0.0f);			//位置を初期化する
	g_nScore = 0;											//値を初期化する
	int nCntScore;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		(sizeof(VERTEX_2D) * 4 * NUM_SCORE),		//4つで画像一個分
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuff -> Lock(0, 0, (void**)&pVtx, 0);

	//スコアの情報の初期化
	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);

		g_posScore += D3DXVECTOR3(37.5f, 0.0f, 0.0f);

		//RHWの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロックする
	g_pVtxBuff -> Unlock();

	
}

//===================
//スコアの終了処理
//===================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTexture != NULL)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//====================
//スコアの更新処理
//====================
void UpdateScore(void)
{

}

//====================
//スコアの描画処理
//====================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
//	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntScore * 4,				//描画する最初の頂点インデックス
			2);							//プリミティブ（ポリゴン）の数
	}
}

//========================
//スコアのセット処理
//========================
void SetScore(int nScore)
{
	int nCntScore;
	int aPosTexU[6];	//各桁の数字を格納

	g_nScore = nScore;

	aPosTexU[0] = (g_nScore % 1000000) / 100000;
	aPosTexU[1] = (g_nScore % 100000) / 10000;
	aPosTexU[2] = (g_nScore % 10000) / 1000;
	aPosTexU[3] = (g_nScore % 1000) / 100;
	aPosTexU[4] = (g_nScore % 100) / 10;
	aPosTexU[5] = (g_nScore % 10) / 1;

	VERTEX_2D*pVtx; //頂点へのポインタ	
	
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	g_pVtxBuff->Unlock();

}

//======================
//スコアの加算処理
//======================
void AddScore(int nValse)
{
	int aPosTexU[6]; //各桁の数字を格納

	g_nScore += nValse;

	aPosTexU[0] = (g_nScore % 1000000) / 100000;
	aPosTexU[1] = (g_nScore % 100000) / 10000;
	aPosTexU[2] = (g_nScore % 10000) / 1000;
	aPosTexU[3] = (g_nScore % 1000) / 100;
	aPosTexU[4] = (g_nScore % 100) / 10;
	aPosTexU[5] = (g_nScore % 10) / 1;

	VERTEX_2D*pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	g_pVtxBuff->Unlock();
}

//======================
//スコアの減算処理
//======================
void SubScore(int nValse)
{
	int aPosTexU[6]; //各桁の数字を格納

	g_nScore -= nValse;

	//これしないと0以下のスコアが表記されてしまう！！
	if (g_nScore <= 0)
	{
		g_nScore = 0;
	}

	aPosTexU[0] = (g_nScore % 1000000) / 100000;
	aPosTexU[1] = (g_nScore % 100000) / 10000;
	aPosTexU[2] = (g_nScore % 10000) / 1000;
	aPosTexU[3] = (g_nScore % 1000) / 100;
	aPosTexU[4] = (g_nScore % 100) / 10;
	aPosTexU[5] = (g_nScore % 10) / 1;

	VERTEX_2D*pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntScore] + 0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	g_pVtxBuff->Unlock();
}

//==================
//スコアの取得
//==================
int GetScore(void)
{
	return g_nScore;
}