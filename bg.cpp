//**************************************************
//
// Hackathon ( bg.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "bg.h"
#include "rectangle.h"
#include "input.h"
#include "color.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_BG = 3;	// �w�i�̍ő�l
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxBG[MAX_BG];	// �w�i�̋�`�̃C���f�b�N�X
int	s_nIdxMoon;			// ���̋�`�̃C���f�b�N�X
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitBG(void)
{
	TEXTURE aTexture[MAX_BG];

	aTexture[0] = TEXTURE_BG_2;
	aTexture[1] = TEXTURE_BG_1;
	aTexture[2] = TEXTURE_BG_0;

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for (int i = 0; i < MAX_BG; i++)
	{
		// ��`�̐ݒ�
		s_nIdxBG[i] = SetRectangle(aTexture[i]);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxBG[i], pos, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitBG(void)
{
	for (int i = 0; i < MAX_BG; i++)
	{
		// �g���̂��~�߂�
		StopUseRectangle(s_nIdxBG[i]);
	}

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxMoon);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateBG(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawBG(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetIdxBG(int nIdxBG)
{
	assert(nIdxBG >= 0 && nIdxBG < MAX_BG);

	return s_nIdxBG[nIdxBG];
}

//--------------------------------------------------
// ���̏�����
//--------------------------------------------------
void InitMoonBG(void)
{
	// ��`�̐ݒ�
	s_nIdxMoon = SetRectangle(TEXTURE_BG_MOON);

	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdxMoon, pos, size);
}