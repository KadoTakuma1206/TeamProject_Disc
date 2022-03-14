//-------------------------------------
//
//ディスクの処理[disc.cpp]
//Author:梶田大夢
//
//-------------------------------------
#include "camera.h"
#include "Input.h"
#include "disc.h"

//グローバル変数
LPD3DXMESH g_pMeshDisc = NULL;
LPD3DXBUFFER g_pBuffMatDisc = NULL;				//頂点バッファへのポインタ
DWORD g_nNumMatDisc= 0;
Disc g_Disc[MAX_DISC];

//ディスクの初期化処理
void InitDisc(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\ディスク.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDisc,
		NULL,
		&g_nNumMatDisc,
		&g_pMeshDisc);

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		g_Disc[nCntDisc].posDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置の初期化
		g_Disc[nCntDisc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動の初期化
		g_Disc[nCntDisc].size = D3DXVECTOR3(g_Disc[nCntDisc].vtxMaxDisc.x - g_Disc[nCntDisc].vtxMinDisc.x, 0.0f, g_Disc[nCntDisc].vtxMaxDisc.z - g_Disc[nCntDisc].vtxMinDisc.z);
		g_Disc[nCntDisc].rotDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向きの初期化
		g_Disc[nCntDisc].rotDestDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].vtxMinDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].vtxMaxDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].buseDisc = true;									//使われているかどうか
	}

	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE * pVtxBuff;		//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshDisc->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshDisc->GetFVF());

	//頂点バッファをロック
	g_pMeshDisc->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
		{
			//x
			if (vtx.x < g_Disc[nCntDisc].vtxMinDisc.x)
			{
				g_Disc[nCntDisc].vtxMinDisc.x = vtx.x;
			}

			if (vtx.x > g_Disc[nCntDisc].vtxMaxDisc.x)
			{
				g_Disc[nCntDisc].vtxMaxDisc.x = vtx.x;
			}

			//y
			if (vtx.y < g_Disc[nCntDisc].vtxMinDisc.y)
			{
				g_Disc[nCntDisc].vtxMinDisc.y = vtx.y;
			}

			if (vtx.y > g_Disc[nCntDisc].vtxMaxDisc.y)
			{
				g_Disc[nCntDisc].vtxMaxDisc.y = vtx.y;
			}

			//z
			if (vtx.z < g_Disc[nCntDisc].vtxMinDisc.z)
			{
				g_Disc[nCntDisc].vtxMinDisc.z = vtx.z;
			}

			if (vtx.z > g_Disc[nCntDisc].vtxMaxDisc.z)
			{
				g_Disc[nCntDisc].vtxMaxDisc.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
	}

	//頂点バッファのアンロック
	g_pMeshDisc->UnlockVertexBuffer();
}

//ディスクの終了処理
void UninitDisc(void)
{
	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		//メッシュの破棄
		if (g_pMeshDisc != NULL)
		{
			g_pMeshDisc->Release();
			g_pMeshDisc = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatDisc != NULL)
		{
			g_pBuffMatDisc->Release();
			g_pBuffMatDisc = NULL;
		}
	}
}

//ディスクの更新処理
void UpdateDisc(void)
{
	Camera * pCamera = GetCamera();

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		if (g_Disc[nCntDisc].buseDisc == true)
		{
			//上
			if (GetKeyboardPress(DIK_UP) == true)
			{
				if (GetKeyboardPress(DIK_RIGHT) == true)
				{
					g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.25f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.25f) * MAX_SPEED;
				}
				else if (GetKeyboardPress(DIK_LEFT) == true)
				{
					g_Disc[nCntDisc].move.x -= sinf(D3DX_PI * 0.75f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z -= cosf(D3DX_PI * 0.75f) * MAX_SPEED;
				}
				else
				{
					g_Disc[nCntDisc].move.x += sinf(pCamera->rot.y) * MAX_SPEED;
					g_Disc[nCntDisc].move.z += cosf(pCamera->rot.y) * MAX_SPEED;
				}
			}
			//下
			else if (GetKeyboardPress(DIK_DOWN) == true)
			{
				if (GetKeyboardPress(DIK_RIGHT) == true)
				{
					g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.75f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.75f) * MAX_SPEED;
				}
				else if (GetKeyboardPress(DIK_LEFT) == true)
				{
					g_Disc[nCntDisc].move.x -= sinf(D3DX_PI * 0.25f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z -= cosf(D3DX_PI * 0.25f) * MAX_SPEED;
				}
				else
				{
					g_Disc[nCntDisc].move.x -= sinf(pCamera->rot.y) * MAX_SPEED;
					g_Disc[nCntDisc].move.z -= cosf(pCamera->rot.y) * MAX_SPEED;
				}
			}
			//左
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_Disc[nCntDisc].move.x -= sinf(D3DX_PI * 0.5f) * MAX_SPEED;
				g_Disc[nCntDisc].move.z -= cosf(D3DX_PI * 0.5f) * MAX_SPEED;
			}
			//右
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{
				g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.5f) * MAX_SPEED;
				g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.5f) * MAX_SPEED;
			}

			//角度の正規化
			if (g_Disc[nCntDisc].rotDestDisc.y - g_Disc[nCntDisc].rotDisc.y > D3DX_PI)
			{
				g_Disc[nCntDisc].rotDestDisc.y = g_Disc[nCntDisc].rotDestDisc.y - D3DX_PI * 2;
			}
			else if (g_Disc[nCntDisc].rotDestDisc.y - g_Disc[nCntDisc].rotDisc.y < -D3DX_PI)
			{
				g_Disc[nCntDisc].rotDestDisc.y = g_Disc[nCntDisc].rotDestDisc.y + D3DX_PI * 2;
			}

			g_Disc[nCntDisc].rotDisc += (g_Disc[nCntDisc].rotDestDisc - g_Disc[nCntDisc].rotDisc) * 0.08f;

			//角度の正規化
			if (g_Disc[nCntDisc].rotDisc.y > D3DX_PI)
			{
				g_Disc[nCntDisc].rotDisc.y = g_Disc[nCntDisc].rotDisc.y - D3DX_PI * 2;
			}
			else if (g_Disc[nCntDisc].rotDisc.y < -D3DX_PI)
			{
				g_Disc[nCntDisc].rotDisc.y = g_Disc[nCntDisc].rotDisc.y + D3DX_PI * 2;
			}

			//前回の位置を保存
			g_Disc[nCntDisc].posOld = g_Disc[nCntDisc].posDisc;

			//位置を更新
			g_Disc[nCntDisc].posDisc.x += g_Disc[nCntDisc].move.x;
			g_Disc[nCntDisc].posDisc.y += g_Disc[nCntDisc].move.y;
			g_Disc[nCntDisc].posDisc.z += g_Disc[nCntDisc].move.z;

			//移動量を更新(減衰させる)
			//g_Disc[nCntDisc].move.x += (0.0f - g_Disc[nCntDisc].move.x) * 0.1f;
			//g_Disc[nCntDisc].move.z += (0.0f - g_Disc[nCntDisc].move.z) * 0.1f;

			//壁のあたり判定
			if (g_Disc[nCntDisc].posDisc.x >= 600.0f)
			{
				g_Disc[nCntDisc].posDisc.x = 600.0f;
				g_Disc[nCntDisc].move.x *= -1;
			}
			else if (g_Disc[nCntDisc].posDisc.x <= -600.0f)
			{
				g_Disc[nCntDisc].posDisc.x = -600.0f;
				g_Disc[nCntDisc].move.x *= -1;

			}

			if (g_Disc[nCntDisc].posDisc.z >= 320.0f)
			{
				g_Disc[nCntDisc].posDisc.z = 320.0f;
				g_Disc[nCntDisc].move.z *= -1;
			}
			else if (g_Disc[nCntDisc].posDisc.z <= -320.0f)
			{
				g_Disc[nCntDisc].posDisc.z = -320.0f;
				g_Disc[nCntDisc].move.z *= -1;
			}
		}
	}
}

//ディスクの描画処理
void DrawDisc(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL * pMat;				//マテリアルデータへのポインタ

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		if (g_Disc[nCntDisc].buseDisc == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Disc[nCntDisc].mtxWorldDisc);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Disc[nCntDisc].rotDisc.y, g_Disc[nCntDisc].rotDisc.x, g_Disc[nCntDisc].rotDisc.z);
			D3DXMatrixMultiply(&g_Disc[nCntDisc].mtxWorldDisc, &g_Disc[nCntDisc].mtxWorldDisc, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Disc[nCntDisc].posDisc.x, g_Disc[nCntDisc].posDisc.y, g_Disc[nCntDisc].posDisc.z);
			D3DXMatrixMultiply(&g_Disc[nCntDisc].mtxWorldDisc, &g_Disc[nCntDisc].mtxWorldDisc, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Disc[nCntDisc].mtxWorldDisc);

			//現在のマテリアルを保持
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL *)g_pBuffMatDisc->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//ディスクパーツの描画
				g_pMeshDisc->DrawSubset(nCntMat);
			}
			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

Disc * GetDisc(void)
{
	return &g_Disc[0];	//一番最初からやってあげますよ敵の情報をあげますの意味
}