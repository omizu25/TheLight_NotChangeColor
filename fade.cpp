//**************************************************
//
// Hackathon ( fade.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "fade.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	ALPHA_CHANGE = 0.07f;	// �t�F�[�h�̃��l�̕ω���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;	// ���_�o�b�t�@�̃|�C���^
FADE					s_fade;				// ���̃t�F�[�h
float					s_fAlpha;			// �|���S��(�t�F�[�h)�̃��l
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitFade(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	s_fAlpha = 0.0f;	// �����|���S��(�s����)�ɂ��Ă���
	s_fade = FADE_NONE;	// �������ĂȂ����

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = SCREEN_WIDTH * 0.5f;
	float fHeight = SCREEN_HEIGHT * 0.5f;

	D3DXVECTOR3 pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(+fWidth, -fHeight, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth, +fHeight, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(+fWidth, +fHeight, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitFade(void)
{
	if (s_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̔j��
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateFade(void)
{
	if (s_fade == FADE_NONE)
	{// �t�F�[�h���ĂȂ�
		return;
	}

	switch (s_fade)
	{
	case FADE_OUT:	// �t�F�[�h�A�E�g���
		s_fAlpha += ALPHA_CHANGE;	// �|���S����s�����ɂ��Ă���

		if (s_fAlpha >= 1.0f)
		{// �s�����ɂȂ���
			s_fAlpha = 1.0f;
			s_fade = FADE_IN;	// �t�F�[�h�C����Ԃ�
		}
		break;

	case FADE_IN:	// �t�F�[�h�C�����
		s_fAlpha -= ALPHA_CHANGE;	// �|���S���𓧖��ɂ��Ă���

		if (s_fAlpha <= 0.0f)
		{// �����ɂȂ���
			s_fAlpha = 0.0f;
			s_fade = FADE_NONE;	// �������Ă��Ȃ���Ԃ�
		}
		break;

	case FADE_NONE:	// �������ĂȂ����
	default:
		assert(false);
		break;
	}

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ菈��
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);

	// ���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawFade(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);						// �v���~�e�B�u(�|���S��)��
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void StartFadeOut(void)
{
	s_fade = FADE_OUT;	// �t�F�[�h�A�E�g��Ԃ�
	s_fAlpha = 0.0f;	// �����|���S��(�s����)�ɂ��Ă���
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
FADE GetFade(void)
{
	return s_fade;
}