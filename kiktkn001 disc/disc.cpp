//-------------------------------------
//
//�f�B�X�N�̏���[disc.cpp]
//Author:���c�喲
//
//-------------------------------------
#include "camera.h"
#include "Input.h"
#include "disc.h"
#include "goal.h"

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshDisc = NULL;					//���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatDisc = NULL;				//���_�o�b�t�@�ւ̃|�C���^
DWORD g_nNumMatDisc= 0;
static Disc g_Disc[MAX_DISC];
static PlayerHaveDisc player;

//�f�B�X�N�̏���������
void InitDisc(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\�f�B�X�N.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDisc,
		NULL,
		&g_nNumMatDisc,
		&g_pMeshDisc);

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshDisc->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshDisc->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshDisc->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
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

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshDisc->UnlockVertexBuffer();

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		g_Disc[nCntDisc].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏�����
		g_Disc[nCntDisc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��̏�����
		g_Disc[nCntDisc].size = D3DXVECTOR3(g_Disc[nCntDisc].vtxMaxDisc.x - g_Disc[nCntDisc].vtxMinDisc.x, 0.0f, g_Disc[nCntDisc].vtxMaxDisc.z - g_Disc[nCntDisc].vtxMinDisc.z);
		g_Disc[nCntDisc].rotDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Disc[nCntDisc].rotDestDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].vtxMinDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].vtxMaxDisc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Disc[nCntDisc].bUse = false;									//�g���Ă��邩�ǂ���
		g_Disc[nCntDisc].bGoal = false;									//�S�[���������ǂ���
		g_Disc[nCntDisc].nGoal = 0;										//�ǂ����ɃS�[��������
	}
}

//�f�B�X�N�̏I������
void UninitDisc(void)
{
	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		//���b�V���̔j��
		if (g_pMeshDisc != NULL)
		{
			g_pMeshDisc->Release();
			g_pMeshDisc = NULL;
		}
	}
	//�}�e���A���̔j��
	if (g_pBuffMatDisc != NULL)
	{
		g_pBuffMatDisc->Release();
		g_pBuffMatDisc = NULL;
	}
}

//�f�B�X�N�̍X�V����
void UpdateDisc(void)
{
	Camera * pCamera = GetCamera();

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		switch (player)
		{
		case E_PLAYER_1:
			if (g_Disc[nCntDisc].bUse == true)
			{
				//��
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
				//��
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
				//��
				else if (GetKeyboardPress(DIK_LEFT) == true)
				{
					g_Disc[nCntDisc].move.x -= sinf(D3DX_PI * 0.5f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z -= cosf(D3DX_PI * 0.5f) * MAX_SPEED;
				}
				//�E
				else if (GetKeyboardPress(DIK_RIGHT) == true)
				{
					g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.5f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.5f) * MAX_SPEED;
				}
			}

			break;

		case E_PLAYER_2:
			if (g_Disc[nCntDisc].bUse == true)
			{
				//��
				if (GetKeyboardPress(DIK_W) == true)
				{
					if (GetKeyboardPress(DIK_D) == true)
					{
						g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.25f) * MAX_SPEED;
						g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.25f) * MAX_SPEED;
					}
					else if (GetKeyboardPress(DIK_A) == true)
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
				//��
				else if (GetKeyboardPress(DIK_S) == true)
				{
					if (GetKeyboardPress(DIK_D) == true)
					{
						g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.75f) * MAX_SPEED;
						g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.75f) * MAX_SPEED;
					}
					else if (GetKeyboardPress(DIK_A) == true)
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
				//��
				else if (GetKeyboardPress(DIK_A) == true)
				{
					g_Disc[nCntDisc].move.x -= sinf(D3DX_PI * 0.5f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z -= cosf(D3DX_PI * 0.5f) * MAX_SPEED;
				}
				//�E
				else if (GetKeyboardPress(DIK_D) == true)
				{
					g_Disc[nCntDisc].move.x += sinf(D3DX_PI * 0.5f) * MAX_SPEED;
					g_Disc[nCntDisc].move.z += cosf(D3DX_PI * 0.5f) * MAX_SPEED;
				}

				break;
			}
		}

		//�p�x�̐��K��
		if (g_Disc[nCntDisc].rotDestDisc.y - g_Disc[nCntDisc].rotDisc.y > D3DX_PI)
		{
			g_Disc[nCntDisc].rotDestDisc.y = g_Disc[nCntDisc].rotDestDisc.y - D3DX_PI * 2;
		}
		else if (g_Disc[nCntDisc].rotDestDisc.y - g_Disc[nCntDisc].rotDisc.y < -D3DX_PI)
		{
			g_Disc[nCntDisc].rotDestDisc.y = g_Disc[nCntDisc].rotDestDisc.y + D3DX_PI * 2;
		}

		g_Disc[nCntDisc].rotDisc += (g_Disc[nCntDisc].rotDestDisc - g_Disc[nCntDisc].rotDisc) * 0.08f;

		//�p�x�̐��K��
		if (g_Disc[nCntDisc].rotDisc.y > D3DX_PI)
		{
			g_Disc[nCntDisc].rotDisc.y = g_Disc[nCntDisc].rotDisc.y - D3DX_PI * 2;
		}
		else if (g_Disc[nCntDisc].rotDisc.y < -D3DX_PI)
		{
			g_Disc[nCntDisc].rotDisc.y = g_Disc[nCntDisc].rotDisc.y + D3DX_PI * 2;
		}

		//�O��̈ʒu��ۑ�
		g_Disc[nCntDisc].posOld = g_Disc[nCntDisc].pos;

		//�ʒu���X�V
		g_Disc[nCntDisc].pos.x += g_Disc[nCntDisc].move.x;
		g_Disc[nCntDisc].pos.y += g_Disc[nCntDisc].move.y;
		g_Disc[nCntDisc].pos.z += g_Disc[nCntDisc].move.z;

		//bool bGoal = CollitionGoal(&g_Disc[nCntDisc].pos, &g_Disc[nCntDisc].posOld, g_Disc[nCntDisc].size);

		//if (bGoal == true)
		//{
		//	g_Disc[nCntDisc].bUse = false;
		//	g_Disc[nCntDisc].bGoal = true;
		//	g_Disc[nCntDisc].nGoal = 2;
		//}

		//�S�[���̂����蔻��
		if (g_Disc[nCntDisc].pos.x >= 600.0f)
		{
			g_Disc[nCntDisc].bUse = false;
			g_Disc[nCntDisc].bGoal = true;
			g_Disc[nCntDisc].nGoal = 2;
		}
		else if (g_Disc[nCntDisc].pos.x <= -600.0f)
		{
			g_Disc[nCntDisc].bUse = false;
			g_Disc[nCntDisc].bGoal = true;
			g_Disc[nCntDisc].nGoal = 1;
		}

		//�ǂ̓����蔻��
		if (g_Disc[nCntDisc].pos.z >= 320.0f)
		{
			g_Disc[nCntDisc].pos.z = 320.0f;
			g_Disc[nCntDisc].move.z *= -1;
		}
		else if (g_Disc[nCntDisc].pos.z <= -320.0f)
		{
			g_Disc[nCntDisc].pos.z = -320.0f;
			g_Disc[nCntDisc].move.z *= -1;
		}
	}
}

//�f�B�X�N�̕`�揈��
void DrawDisc(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntDisc = 0; nCntDisc < MAX_DISC; nCntDisc++)
	{
		if (g_Disc[nCntDisc].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Disc[nCntDisc].mtxWorldDisc);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Disc[nCntDisc].rotDisc.y, g_Disc[nCntDisc].rotDisc.x, g_Disc[nCntDisc].rotDisc.z);
			D3DXMatrixMultiply(&g_Disc[nCntDisc].mtxWorldDisc, &g_Disc[nCntDisc].mtxWorldDisc, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Disc[nCntDisc].pos.x, g_Disc[nCntDisc].pos.y, g_Disc[nCntDisc].pos.z);
			D3DXMatrixMultiply(&g_Disc[nCntDisc].mtxWorldDisc, &g_Disc[nCntDisc].mtxWorldDisc, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Disc[nCntDisc].mtxWorldDisc);

			//���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL *)g_pBuffMatDisc->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�f�B�X�N�p�[�c�̕`��
				g_pMeshDisc->DrawSubset(nCntMat);
			}
			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void SetDisc(PlayerHaveDisc player)
{
	for (int nCnt = 0; nCnt < MAX_DISC; nCnt++)
	{
		switch (player)
		{
		case E_PLAYER_1:
			if (g_Disc[nCnt].bUse == false)
			{
				g_Disc[nCnt].pos = D3DXVECTOR3(-300.0f, 0.0f, 0.0f);
				g_Disc[nCnt].bUse = true;
				g_Disc[nCnt].bGoal = false;
				g_Disc[nCnt].nGoal = 0;
			}

			break;

		case E_PLAYER_2:
			if (g_Disc[nCnt].bUse == false)
			{
				g_Disc[nCnt].pos = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
				g_Disc[nCnt].bUse = true;
				g_Disc[nCnt].bGoal = false;
				g_Disc[nCnt].nGoal = 0;
			}
			break;
		}
	}
}

Disc * GetDisc(void)
{
	return &g_Disc[0];	//��ԍŏ��������Ă����܂���G�̏��������܂��̈Ӗ�
}