//=============================================================================
//
// ���f������ [model.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------

#include "player.h"
#include "camera.h"
#include "input.h"
#include "calculation.h"
#include "polygon.h"
#include "disc.h"
#include "collision.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------

#define ANGLE_DAMPING_COEFFICIENT	(0.07f)					//�p�x�̌����W��
#define SCALE_DOWN					(1.0f)					//�X�P�[���T�C�Y�̕ύX
#define ANCHOR_POINT_MAX			(120)					//�J�����̈ړ��_
#define GRAVITY_MAX					(3.0f)					//�d��
#define ACCELERATION_MAX			(1.0f)					//�����̌��E
#define PLAYER_SPEED				(7.0f)


//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------

//���[�V�����Đ����ɕK�v�ȏ��\����
typedef struct
{
	int nFrameCnt;					//���݂̃t���[����
	int nNowRebirthKeySet;			//�Đ����̃L�[�Z�b�g�ԍ�
	int nNowRebirthMotion;			//�Đ����̃��[�V�����ԍ�
}PlayerMotionData;

//���f���p�^�[���\����
typedef struct
{
	LPD3DXMESH pMesh = NULL;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;		//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat = 0;					//�}�e���A�����̐�
	bool bUse;							//�g�p���Ă��邩�ǂ���
}PlayerPartsPattern;

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------

D3DXMATRIX g_PlayerPartsmtxWorld[PARENT_MAX];				//���[���h�}�g���b�N�X(�v���C���[�p�[�c)
PlayerPartsPattern g_PartsPattern[PARENT_MAX];				//���f���p�^�[���\����
Player g_Player;											//�v���C���[�̍\����
char g_sPlayerModelFilename[PARENT_MAX][256];				//�t�@�C����
PlayerMotionData g_MotionPlayer;							//���[�V�����ɕK�v�ȃf�[�^�\����
float g_fDeceleration;										//�v���C���[�ړ��ʂ̌��������i�Q�[�����p�j
D3DXVECTOR3 g_PlayerPos;									//�Q�[�����̉��ړ��Ȃǂ���邽�߂�POS
int g_nLineNmn = 0;

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------

void PlayerMove(void);
void MotionsetPlayer(void);
void ChangeMotion(int nMotion, int nKey);

//*****************************************************************************
//�v���C���[�̏�����
//*****************************************************************************

void InitPlayer(void)
{
	//�v���C���[�ɕK�v�ȑS���[���h�}�g���b�N�X�̏�����
	ZeroMemory(&g_PlayerPartsmtxWorld, sizeof(g_PlayerPartsmtxWorld));
	//�v���C���[�̍\���̂̏�����
	ZeroMemory(&g_PartsPattern, sizeof(g_PartsPattern));
	ZeroMemory(&g_Player, sizeof(g_Player));
	//���[�V�����ɕK�v�ȃf�[�^�\���̂̏�����
	ZeroMemory(&g_MotionPlayer, sizeof(g_MotionPlayer));
	//POS������
	ZeroMemory(&g_PlayerPos, sizeof(g_PlayerPos));

	//�v���C���[�ړ��ʂ̌��������̏�����
	g_fDeceleration = 0.0f;
}

//*****************************************************************************
//�v���C���[�̏I������
//*****************************************************************************

void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		//���b�V���̔j��
		if (g_PartsPattern[nCnt].pMesh != NULL)
		{
			g_PartsPattern[nCnt].pMesh->Release();
			g_PartsPattern[nCnt].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_PartsPattern[nCnt].pBuffMat != NULL)
		{
			g_PartsPattern[nCnt].pBuffMat->Release();
			g_PartsPattern[nCnt].pBuffMat = NULL;
		}

	}
}

//*****************************************************************************
//�v���C���[�̍X�V����
//*****************************************************************************

void UpdatePlayer(void)
{
	//�J�����̏��̎擾�i�|�C���^�j
	Camera *pCamera = GetCamera();

	//�v���C���[�̈ړ�
	PlayerMove();

	//�f�B�X�N�̏��̎擾
	Disc *pDisc = GetDisc();
	//������
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
	{//�E�L�[�������ꂽ
		g_Player.bDiscHave = false;
		pDisc[g_Player.nNumDisc].move.x *= - 1.0f;
	}

	//���[�V����
	if (g_MotionPlayer.nNowRebirthMotion == g_Player.PlayerState)
	{
		MotionsetPlayer();
	}
}

//*****************************************************************************
//�v���C���[�̕`�揈��
//*****************************************************************************

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRootFirst;			//�匳�̐e�̐e���[���h�}�g���b�N�X
	D3DXMATRIX mtxRoot;					//�匳�̐e�̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�̃}�g���b�N�X

										//���[���h�}�g���b�N�X�̏������i�匳�̐e�̐e�j
	D3DXMatrixIdentity(&mtxRootFirst);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&mtxRootFirst, &mtxRootFirst, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_PlayerPos.x, g_PlayerPos.y, g_PlayerPos.z);
	D3DXMatrixMultiply(&mtxRootFirst, &mtxRootFirst, &mtxTrans);

	//���[���h�}�g���b�N�X�̏������i�匳�̐e�j
	D3DXMatrixIdentity(&mtxRoot);

	D3DXMatrixScaling(&mtxRot,
		SCALE_DOWN, SCALE_DOWN, SCALE_DOWN);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRot);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxTrans);

	//���f���̃}�g���b�N�X�@���@�e�̃��[���h�}�g���b�N�X
	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRootFirst);

	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		if (g_Player.Parts[nCnt].bUse)
		{
			D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
			D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

											//���[���h�}�g���b�N�X�̏������i�q�j
			D3DXMatrixIdentity(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex]);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Player.Parts[nCnt].rot.y, g_Player.Parts[nCnt].rot.x, g_Player.Parts[nCnt].rot.z);

			D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxRot);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTrans, g_Player.Parts[nCnt].pos.x, g_Player.Parts[nCnt].pos.y, g_Player.Parts[nCnt].pos.z);
			D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxTrans);

			if (g_Player.Parts[nCnt].nParent < 0)
			{
				//���f���̃}�g���b�N�X�@���@�e�̃��[���h�}�g���b�N�X
				D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &mtxRoot);
			}
			else
			{
				//���f���̃}�g���b�N�X�@���@�e�̃��[���h�}�g���b�N�X
				D3DXMatrixMultiply(&g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex], &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nParent]);
			}

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_PlayerPartsmtxWorld[g_Player.Parts[nCnt].nIndex]);

			//���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_PartsPattern[g_Player.Parts[nCnt].nIndex].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_PartsPattern[g_Player.Parts[nCnt].nIndex].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f���p�[�c�̕`��
				g_PartsPattern[g_Player.Parts[nCnt].nIndex].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------------------
//�v���C���[�̈ړ�
//-----------------------------------------------------------------------------
void PlayerMove(void)
{
	//�ߋ��̈ʒu�̕ۑ�
	g_Player.posOld = g_PlayerPos + g_Player.pos;

	//�J�����̏��̎擾�i�|�C���^�j
	Camera *pCamera = GetCamera();

	//���_�ړ�
	g_Player.PlayerState = PLAYER_RUN;
	g_MotionPlayer.nNowRebirthMotion = PLAYER_RUN;
	if (GetKeyboardPress(DIK_W))
	{//��L�[�������ꂽ
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
	{//���L�[�������ꂽ
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
	{//���L�[�������ꂽ
		g_Player.rotDest.y = D3DX_PI * 0.5f + pCamera->rot.y;
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * g_Player.fMove;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * g_Player.fMove;
	}
	else if (GetKeyboardPress(DIK_D))
	{//�E�L�[�������ꂽ
		g_Player.rotDest.y = D3DX_PI * -0.5f + pCamera->rot.y;
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * g_Player.fMove;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * g_Player.fMove;
	}
	else
	{
		ZeroMemory(&g_Player.move, sizeof(g_Player.move));
		
			g_Player.PlayerState = PLAYER_NEUTRAL;
			g_MotionPlayer.nNowRebirthMotion = PLAYER_NEUTRAL;
			//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
			//ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
		
	}

	//rot���K�萔��蒴�����Ƃ��̕␳����
	g_Player.rot.y += Normalization(g_Player.rotDest.y/*�ړI�̊p�x*/ - g_Player.rot.y/*���݂̊p�x*/)
		* ANGLE_DAMPING_COEFFICIENT;

	//rot���K�萔��蒴�����Ƃ��̕␳
	g_Player.rot.y = Normalization(g_Player.rot.y);

	//�v���C���[POS�̍X�V
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

	//�v���C���[�̓��̂�POS�X�V(�W�����v����)
	g_Player.pos.y -= (70.0f - g_Player.pos.y) * 0.1f;
	

	//��������
	if (g_fDeceleration < 0.9f)
	{
		g_fDeceleration += (ACCELERATION_MAX - g_fDeceleration) * 0.01f;
	}

	//��
	if (g_Player.pos.y <= 0.0f)
	{
		g_Player.pos.y = 0.0f;
	}
}

//-----------------------------------------------------------------------------
//�v���C���[���̎擾�i�|�C���^�j
//-----------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_Player;
}

//-----------------------------------------------------------------------------
//�v���C���[���̎擾�i�|�C���^�ł͂Ȃ��j
//-----------------------------------------------------------------------------
Player GetPlayerData(void)
{
	return g_Player;
}

//-----------------------------------------------------------------------------
//���f���^�C�v�ǂݍ��ݏ���
//-----------------------------------------------------------------------------

HRESULT LoadPlayerPattern(HWND hWnd, char *sXFilePath)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntPatn = 0; nCntPatn < PARENT_MAX; nCntPatn++)
	{
		if (!g_PartsPattern[nCntPatn].bUse)
		{

			//X�t�@�C���̓ǂݍ���
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

	MessageBox(hWnd, "�ǂݍ��݉\���f�����𒴂��Ă��܂�", "�x���I", MB_ICONWARNING);
	return E_FAIL;
}

//-----------------------------------------------------------------------------
//�v���C���[�̃Z�b�g����
//-----------------------------------------------------------------------------

void SetPlayer(Player Player)
{
	g_Player = Player;



	g_Player.rotDest.y = D3DX_PI;
	g_Player.rot.y = D3DX_PI;
	g_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.PlayerState = PLAYER_NEUTRAL;
	g_MotionPlayer.nNowRebirthMotion = PLAYER_NEUTRAL;
	//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
	ChangeMotion(0, 1);




	int nNumVix;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

						//���f���̃T�C�Y�̔�r�p�����l
	g_Player.vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	g_Player.vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//���_���̎擾
	nNumVix = g_PartsPattern[0].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�擾
	sizeFVF = D3DXGetFVFVertexSize(g_PartsPattern[0].pMesh->GetFVF());

	//���_���b�N
	g_PartsPattern[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���ׂĂ̒��_POS�̎擾
	for (int nCntVtx = 0; nCntVtx < nNumVix; nCntVtx++)
	{
		//���_���W�̑��
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

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	g_Player.vtxMax *= SCALE_DOWN;
	g_Player.vtxMin *= SCALE_DOWN;


	//���_�A�����b�Na
	g_PartsPattern[0].pMesh->UnlockVertexBuffer();
}

//-----------------------------------------------------------------------------
//���[�V�����Đ�����
//-----------------------------------------------------------------------------

void MotionsetPlayer(void)
{
	int nMotion = g_MotionPlayer.nNowRebirthMotion;
	int nKey = g_MotionPlayer.nNowRebirthKeySet;
	int nFrame = g_Player.Motion[nMotion].nFrame[nMotion];
	int nNumKey = g_Player.Motion[nMotion].nNumKey;

	if (nFrame <= 0)
	{//�e�L�X�g�ݒ�t���[�������O�ȉ���������
		nFrame = 1;
	}


	//���[�V�����Đ��i�S�p�[�c�jD3DXVec3Normalize
	for (int nCnt = 0; nCnt < PARENT_MAX; nCnt++)
	{
		if (g_Player.Parts[nCnt].bUse)
		{
			D3DXVECTOR3 move, rot;


			move = (g_Player.Parts[nCnt].posMotionset[nMotion][nKey] - g_Player.Parts[nCnt].posMotionset[nMotion][((nKey - 1) + nNumKey) % nNumKey]) / (float)g_Player.Motion[nMotion].nFrame[nKey];
			//POS�̍Đ��i���[�J�����W�j
			g_Player.Parts[nCnt].pos += move;

			rot = (g_Player.Parts[nCnt].rotMotionset[nMotion][nKey] - g_Player.Parts[nCnt].rotMotionset[nMotion][((nKey - 1) + nNumKey) % nNumKey]) / (float)g_Player.Motion[nMotion].nFrame[nKey];

			//ROT�̍Đ�
			g_Player.Parts[nCnt].rot += rot;
		}
	}


	//�t���[���̉��Z
	g_MotionPlayer.nFrameCnt++;

	if (g_Player.Motion[nMotion].nFrame[nKey] <= g_MotionPlayer.nFrameCnt)
	{//�t���[�������ݒ�̒l�𒴂�����

	 //���[�V�����̏������ƃL�[�̃Z�b�g�ύX
		ChangeMotion(nMotion, nKey);

		//�Đ����̃L�[���̉��Z
		g_MotionPlayer.nNowRebirthKeySet++;
		//�t���[���̏�����
		g_MotionPlayer.nFrameCnt = 0;

		if (g_Player.Motion[nMotion].nNumKey <= g_MotionPlayer.nNowRebirthKeySet)
		{//�Đ����̃L�[�����ݒ�̒l�𒴂�����
			if (g_Player.Motion[nMotion].nLoop == 1)
			{
				g_MotionPlayer.nNowRebirthKeySet = 0;

				//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
				ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
			}
			else if (nMotion == PLAYER_HAVE)
			{
				g_MotionPlayer.nNowRebirthKeySet = 0;
				g_MotionPlayer.nNowRebirthMotion = 1;

				//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
				//ChangeMotion(g_MotionPlayer.nNowRebirthMotion, g_MotionPlayer.nNowRebirthKeySet);
			}
			else
			{//���ݍĐ����̃��[�V�������烉�����[�V�����ɕύX
				g_MotionPlayer.nNowRebirthKeySet = 0;
				g_MotionPlayer.nNowRebirthMotion = 1;
				//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
				ChangeMotion(g_MotionPlayer.nNowRebirthMotion, 1);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//���[�V�����̏������ƃL�[�̃Z�b�g�ύX
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
//�v���C���[�̈ʒu�̎Q��
//-----------------------------------------------------------------------------

D3DXVECTOR3 GetPosPlayer(void)
{
	return g_PlayerPos;
}