//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "result.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXTURE	(8)		//�g�p����e�N�X�`���̖���

//=============================================================================
// �X�^�e�B�b�N�ϐ�
//=============================================================================
static LPDIRECT3DTEXTURE9 g_pTexture[MAX_TEXTURE] = {NULL};		//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
static bool bUseResult;											//���U���g���g�p���Ă邩

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//�ϐ��̏�����
	bUseResult = false;

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/����.png",
		&g_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/�s��.png",
		&g_pTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/win.png",
		&g_pTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/lose.png",
		&g_pTexture[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ZeroPoint.png",
		&g_pTexture[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/OnePoint.png",
		&g_pTexture[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TwoPoint.png",
		&g_pTexture[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETCOUNT.png",
		&g_pTexture[7]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����̏�����
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^��4�i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuff != NULL)
		{
			g_pVtxBuff->Release();
			g_pVtxBuff = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture[i]);

		//�|���S���̕`�揈��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		//�|���S���̌`
			4 * i,						//���_�̊J�n�ꏊ
			2);							//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// ���U���g�Z�b�g����
//=============================================================================
void SetResult(int nSetCount1, int nSetCount2)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (bUseResult == false)
	{ //�g�p���Ă��Ȃ���Ύ��s
		//�ϐ��̐ݒ�
		bUseResult = true;

		if (nSetCount1 > nSetCount2)
		{ //1P�����������ꍇ
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(275.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(475.0f + 50.0f, 350.0f + 150.0f, 0.0f);

			pVtx[4].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f - 150.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(775.0f - 50.0f, 350.0f + 150.0f, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(975.0f + 50.0f, 350.0f + 150.0f, 0.0f);

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
		}

		else if (nSetCount1 < nSetCount2)
		{ //2P�����������ꍇ
			//���_���W�̐ݒ�
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

	//�Z�b�g�J�E���g�̃Z�b�g����
	SetCount(nSetCount1, D3DXVECTOR3(275.0f, 600.0f, 0.0f));
	SetCount(nSetCount2, D3DXVECTOR3(975.0f, 600.0f, 0.0f));
}

//=============================================================================
// �Z�b�g�J�E���g�Z�b�g����
//=============================================================================
void SetCount(int nSetCount, D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//�ϐ��錾
	D3DXVECTOR3 nCountPos = pos;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nSetCount == 0)
	{ //�Z�b�g�J�E���g��0�������ꍇ���s
		//���_���W�̐ݒ�
		pVtx[16].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	else if (nSetCount == 1)
	{ //�Z�b�g�J�E���g��1�������ꍇ���s
		//���_���W�̐ݒ�
		pVtx[20].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[21].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[22].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[23].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	else if (nSetCount == 2)
	{ //�Z�b�g�J�E���g��2�������ꍇ���s
	  //���_���W�̐ݒ�
		pVtx[24].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[25].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y - 70.0f, 0.0f);
		pVtx[26].pos = D3DXVECTOR3(nCountPos.x - 50.0f, nCountPos.y + 70.0f, 0.0f);
		pVtx[27].pos = D3DXVECTOR3(nCountPos.x + 50.0f, nCountPos.y + 70.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();
}