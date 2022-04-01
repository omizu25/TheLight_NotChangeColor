//**************************************************
//
// Hackathon ( score.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "score.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "input.h"
#include "utility.h"
#include "ranking.h"
#include "light.h"

//==================================================
// ��`
//==================================================
namespace
{
const float	SCORE_WIDTH = 70.0f;	// �X�R�A�̕�
const float	SCORE_HEIGHT = 150.0f;	// �X�R�A�̍���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxScore;	// ���̔z��̃C���f�b�N�X
int	s_nScore;		// �X�R�A
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitScore(void)
{
	s_nScore = GetLight() - 1;

	D3DXVECTOR3 size = D3DXVECTOR3(SCORE_WIDTH, SCORE_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.68f, SCREEN_HEIGHT * 0.25f, 0.0f);

	// ���̐ݒ�
	s_nIdxScore = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nScore, DigitNumber(s_nScore), false);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitScore(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxScore);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateScore(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawScore(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetScore(void)
{
	return s_nScore;
}
