//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "fade.h"
#include "result.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXTURE	(3)		//�g�p����e�N�X�`���̖���

//=============================================================================
// �X�^�e�B�b�N�ϐ�
//=============================================================================
static LPDIRECT3DTEXTURE9 s_pTexture[MAX_TEXTURE] = { NULL };		//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;					//���_�o�b�t�@�ւ̃|�C���^
static TITLE s_Title[MAX_TEXTURE];									//�\����
static int s_MenuSelect;											//�|�[�Y�I��p�̕ϐ�
static int s_MenuCol;												//���j���[�J���[�ύX�p�̕ϐ�

//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{
	//�|���S���̏���������
	InitPolygon();

	InitResult();

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title000.png",
		&s_pTexture[0]);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title001.png",
		&s_pTexture[1]);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title002.png",
		&s_pTexture[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//�ϐ��̏�����
	s_MenuSelect = 0;

	//�\���̂̏�����
	s_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -300.0f, 0.0f);
	s_Title[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_Title[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//���_���W�̏�����
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̏�����
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̏�����
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏�����
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^��4�i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	//�|���S���̏I������
	UninitPolygon();

	UninitResult();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//�e�N�X�`���̔j��
		if (s_pTexture[i] != NULL)
		{
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (s_pVtxBuff != NULL)
		{
			s_pVtxBuff->Release();
			s_pVtxBuff = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	//�J�����̍X�V����
	UpdateCamera();

	//�J�����̎������񏈗�
	RotateCamera();

	//�|���S���̍X�V����
	UpdatePolygon();

	//���j���[�Z���N�g����
	MenuSelect();

	//�e�N�X�`���X�V����
	TextureUpdate();

	//���C�g�̍X�V����
	UpdateLight();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	//�J�����̐ݒ菈��
	SetCamera();

	//�|���S���̕`�揈��
	DrawPolygon();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_pTexture[i]);

		//�|���S���̕`�揈��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		//�|���S���̌`
			4 * i,						//���_�̊J�n�ꏊ
			2);							//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// �J�����������񏈗�
//=============================================================================
void RotateCamera(void)
{
	//�J�����̏����擾
	Camera *pCamera = GetCamera();

	//�J��������
	pCamera->rot.y -= 0.007f;
	pCamera->posV.x = pCamera->posR.x - sinf(pCamera->rot.y) * pCamera->fDistance;
	pCamera->posV.z = pCamera->posR.z - cosf(pCamera->rot.y) * pCamera->fDistance;
}

//=============================================================================
// �e�N�X�`��,���_���X�V����
//=============================================================================
void TextureUpdate(void)
{
	//�ړ��ʐݒ�
	if (s_Title[0].pos.y < 230.0f)
	{
		s_Title[0].move.y = 5.0f;
	}
	else
	{
		s_Title[0].move.y = 0.0f;
	}

	//�ʒu�X�V
	s_Title[0].pos += s_Title[0].move;

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(s_Title[0].pos.x - 350.0f, s_Title[0].pos.y - 150.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(s_Title[0].pos.x + 350.0f, s_Title[0].pos.y - 150.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(s_Title[0].pos.x - 350.0f, s_Title[0].pos.y + 150.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(s_Title[0].pos.x + 350.0f, s_Title[0].pos.y + 150.5f, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 / 2 - 150.0f, 600.0f - 45.5f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 / 2 + 150.0f, 600.0f - 45.5f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 / 2 - 150.0f, 600.0f + 45.5f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 / 2 + 150.0f, 600.0f + 45.5f, 0.0f);

	pVtx[8].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 2 / 2 + 90.0f) - 180.0f, 600.0f - 45.5f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 2 / 2 + 90.0f) + 180.0f, 600.0f - 45.5f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 2 / 2 + 90.0f) - 180.0f, 600.0f + 45.5f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 2 / 2 + 90.0f) + 180.0f, 600.0f + 45.5f, 0.0f);

	//���_�J���[�̍X�V
	if (s_MenuSelect == 0)
	{
		pVtx[4].col = s_Title[1].col;
		pVtx[5].col = s_Title[1].col;
		pVtx[6].col = s_Title[1].col;
		pVtx[7].col = s_Title[1].col;

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else if (s_MenuSelect == 1)
	{
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[8].col = s_Title[1].col;
		pVtx[9].col = s_Title[1].col;
		pVtx[10].col = s_Title[1].col;
		pVtx[11].col = s_Title[1].col;
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//=============================================================================
// ���j���[�Z���N�g����
//=============================================================================
void MenuSelect(void)
{
	//�t�F�[�h�̏����擾
	FADE pFade = GetFade();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_A))
		{//W�L�[�����͂��ꂽ�Ƃ�
			s_MenuSelect--;
			if (s_MenuSelect < 0)
			{
				s_MenuSelect = 1;
			}
		}
		else if (GetKeyboardTrigger(DIK_D))
		{//S�L�[�����͂��ꂽ�Ƃ�
			s_MenuSelect++;
			if (s_MenuSelect >= 2)
			{
				s_MenuSelect = 0;
			}
		}
	}

	//���j���[�I���Ńt�F�[�h�ڍs
	switch (s_MenuSelect)
	{
	case 0:
		if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE)
		{
			//���[�h�̃Z�b�g����
			SetFade(MODE_GAME);
			break;
		}
	case 1:
		if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE)
		{
			//���[�h�̃Z�b�g����
			SetFade(MODE_TUTORIAL);
			break;
		}
	}

	//�J���[�X�C�b�`
	if (s_Title[1].col.b >= 1.0f)
	{
		s_MenuCol = 1;
	}
	else if (s_Title[1].col.b <= 0.0f)
	{
		s_MenuCol = 2;
	}

	//�J���[�̕ύX
	if (s_MenuCol == 1)
	{
		s_Title[1].col.b -= 0.02f;
	}
	else
	{
		s_Title[1].col.b += 0.02f;
	}
}