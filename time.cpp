//**************************************************
//
// Hackathon ( time.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "time.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "fan.h"
#include "answer.h"
#include "game.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	ONE_SECOND = 60;	// 1�b
const float	TIME_SIZE = 21.5f;	// �^�C���̃T�C�Y
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxTime;		// ���̔z��̃C���f�b�N�X
int	s_nTime;		// �^�C��
int	s_nSecond;		// 1�b���v��
int	s_nDrawTime;	// �`���������^�C��
D3DXCOLOR s_col;
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTime(void)
{
	s_nTime = 0;
	s_nSecond = 0;
	s_nIdxTime = 0;
	s_nDrawTime = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(TIME_SIZE, TIME_SIZE, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, TIME_SIZE * 0.5f, 0.0f);

	pos.x += DigitNumber(s_nTime) * (TIME_SIZE * 0.5f);

	// �~�`�̐ݒ�
	s_nIdxTime = SetFan(TEXTURE_NONE);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTime(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxTime);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTime(void)
{
	if (GetGameState() != GAMESTATE_PLAYER)
	{
		// �~�`��`�悷�邩�ǂ���
		SetDrawFan(s_nIdxTime, false);

		return;
	}

	if (GetAnswer())
	{// �ő�l
		// �~�`��`�悷�邩�ǂ���
		SetDrawFan(s_nIdxTime, false);

		return;
	}

	// �~�`��`�悷�邩�ǂ���
	SetDrawFan(s_nIdxTime, true);

	s_nSecond++;

	if ((s_nSecond % s_nDrawTime) == 0)
	{
		AddDrawFan(s_nIdxTime, -1);
	}

	if ((s_nSecond % ONE_SECOND) == 0)
	{// 1�b����
		// ���Z
		AddTime(-1);

		switch (s_nTime)
		{
		case 5:
			s_col = GetColor(COLOR_GREEN);
			break;
		case 4:
		case 3:
			s_col = GetColor(COLOR_YELLOW);
			break;
		case 2:
		case 1:
			s_col = GetColor(COLOR_RED);
			break;
		default:
			break;
		}

		s_col.a = 0.5f;

		// �~�`�̐F�̐ݒ�
		SetColorFan(s_nIdxTime, s_col);

		if (s_nTime <= 0)
		{// �������Ԃ�����
			// ���[�h�̕ύX
			ChangeMode(MODE_RESULT);
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTime(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetTime(int nTime)
{
	s_nTime = nTime;
	s_nDrawTime = (nTime * ONE_SECOND) / 100;
	s_nSecond = 0;

	// ���Z�b�g
	ResetDrawFan(s_nIdxTime);

	s_col = GetColor(COLOR_GREEN);

	s_col.a = 0.5f;

	// �~�`�̐F�̐ݒ�
	SetColorFan(s_nIdxTime, s_col);
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void SetPosTime(D3DXVECTOR3 pos)
{
	// �ʒu�̐ݒ�
	SetRotationPosFan(s_nIdxTime, pos, D3DX_PI, TIME_SIZE, false);
}

//--------------------------------------------------
// ���Z
// ����  : int nValue / ���Z����l
//--------------------------------------------------
void AddTime(int nValue)
{
	s_nTime += nValue;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetTime(void)
{
	return s_nTime;
}
