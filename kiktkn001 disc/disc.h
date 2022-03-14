//-------------------------------------
//
//���f���w�b�_�[[disc.h]
//Author:���c�喲
//
//-------------------------------------
#ifndef  _DISC_H_						//���̃}�N����`������ĂȂ�������
#define  _DISC_H_						//��d�C���N���[�h�h�~�̃}�N����`

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_DISC		(1)
#define MAX_SPEED		(1.0f)		//�ړ����x

typedef struct
{
	D3DXVECTOR3 posDisc;								//�ʒu
	D3DXVECTOR3 posOld;									//�O�̈ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 size;									//�T�C�Y
	D3DXVECTOR3 rotDisc;								//����
	D3DXVECTOR3 rotDestDisc;
	D3DXVECTOR3 vtxMinDisc;								//�ő咸�_
	D3DXVECTOR3 vtxMaxDisc;								//�ŏ����_
	bool buseDisc;										//�g���Ă��邩
	D3DXMATRIX mtxWorldDisc;							//���[���h�}�g���b�N�X
}Disc;

//�v���g�^�C�v�錾
void InitDisc(void);			//���f���̏���������
void UninitDisc(void);			//���f���̏I������
void UpdateDisc(void);			//���f���̍X�V����
void DrawDisc(void);			//���f���̕`�揈��

Disc * GetDisc(void);

#endif
