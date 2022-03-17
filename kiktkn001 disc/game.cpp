//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
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
// �X�^�e�B�b�N�ϐ�
//=============================================================================
static bool g_bPause = false;		//�|�[�Y�����ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	//�����̏�����
	srand((unsigned int)time(0));

	//�v���C���[������
	InitPlayer();

	//���[�h�����i�v���C���[�j
	LoadSetPlayer();

	//�|���S���̏���������
	InitPolygon();

	//�r���{�[�h�̏���������
	InitBillboard();

	//�S�[���̏���������
	InitGoal();

	//�f�B�X�N�̏���������
	InitDisc();

	//�f�B�X�N�̐ݒ�
	SetDisc(E_PLAYER_1);
	//SetDisc(E_PLAYER_2);

	//�f�B�X�N�̈ʒu�������I�ɕς���
	SetDiscPos(0, D3DXVECTOR3(500.0f, 0.0f, 0.0f));

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//���U���g�̏���������
	InitResult();

	//�|�[�Y��ʂ̏���������
	InitPause();		

	//�|�[�Y����
	g_bPause = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	//�|���S���̏I������
	UninitPolygon();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�f�B�X�N�̏I������
	UninitDisc();

	//�S�[���̏I������
	UninitGoal();

	//�v���C���[�I������
	UninitPlayer();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//���U���g�̏I������
	UninitResult();

	//�|�[�Y��ʂ̏I������
	UninitPause();		
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	//�|�[�Y���̎擾
	PAUSE *pPause = GetPause();

	if (GetKeyboardTrigger(DIK_P) == true && g_bPause == false)
	{//�|�[�Y�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;		//true�Ȃ�false,false�Ȃ�true �O�����Z�q
	}

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
	}

	if (g_bPause == false /*&& nTimer != 0*/)
	{//�|�[�Y���łȂ����
		//�|���S���̍X�V����
		UpdatePolygon();

		//�f�B�X�N�̍X�V����
		UpdateDisc();

		//�S�[���̍X�V����
		UpdateGoal();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�r���{�[�h�̍X�V����
		UpdatePlayer();

		//�J�����̍X�V����
		UpdateCamera();

		//���C�g�̍X�V����
		UpdateLight();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	//�J�����̐ݒ菈��
	SetCamera();

	//�|���S���̕`�揈��
	DrawPolygon();

	//�f�B�X�N�̕`�揈��
	DrawDisc();

	//�S�[���̕`��
	DrawGoal();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�r���{�[�h�̕`�揈��
	DrawBillboard();

	//���U���g�̕`�揈��
	DrawResult();

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//=============================================================================
// �|�[�Y�̗L�������ݒ�
//=============================================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}