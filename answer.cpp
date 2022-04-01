//**************************************************
//
// Hackathon ( answer.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "answer.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "mode.h"
#include "light.h"
#include "player.h"
#include "game.h"
#include "bg.h"
#include "sound.h"
#include "ui.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 120;	// �^�C���̍ő�l
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
bool	s_bMax;		// �ő�ɂȂ������ǂ���
bool	s_bAnswer;	// �����Ă邩�ǂ���
int		s_nTime;	// �^�C��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitAnswer(void)
{
	s_nTime = 0;
	s_bMax = false;
	s_bAnswer = false;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitAnswer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateAnswer(void)
{
	if (s_bMax)
	{// �ő�l�ɂȂ���
		s_nTime++;

		if (s_nTime >= MAX_TIME)
		{// ���Ԃ�����
			if (s_bAnswer)
			{// ����
				s_bMax = false;
				s_nTime = 0;
				s_bAnswer = true;

				// �Q�[����Ԃ̐ݒ�
				SetGameState(GAMESTATE_RESET);

				// ��`�̐F�̐ݒ�
				SetColorRectangle(GetIdxBG(0), GetColor(COLOR_WHITE));

				// �Q�[�W��UI�̕ύX
				ChangeGaugeUI();

				// �����̐F�̐ݒ�
				SetColorPushPlayer(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
			else
			{// �s����
				s_bMax = true;
				s_nTime = 0;
				s_bAnswer = false;

				// ���[�h�̕ύX
				ChangeMode(MODE_RESULT);
			}
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawAnswer(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetAnswer(int nNowLight)
{
	if (GetColorLight(nNowLight) == GetColorPlayer(nNowLight))
	{// ����
		if ((GetPlayer() + 1) >= GetLight())
		{// �ő�ɂȂ���
			s_bMax = true;
			s_nTime = 0;
			s_bAnswer = true;
		}
	}
	else
	{// �s����
		PlaySound(SOUND_LABEL_SE_MISS);
		s_nTime = 0;
		s_bMax = true;
		s_bAnswer = false;

		// �Ԉ����
		MistakeLight();
	}
}

//--------------------------------------------------
// �擾
// �Ԓl  : bool / �ő�l�ɂȂ������ǂ���
//--------------------------------------------------
bool GetAnswer(void)
{
	return s_bMax;
}