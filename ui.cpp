//**************************************************
//
// Hackathon ( ui.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "ui.h"
#include "rectangle.h"
#include "fan.h"
#include "texture.h"
#include "mode.h"
#include "color.h"
#include "sound.h"
#include "gauge.h"
#include "light.h"
#include "utility.h"
#include "effect.h"

//==================================================
// ��`
//==================================================
namespace
{
const float	MAX_ALPHA_GRAY = 0.6f;		// �D�F�̃Q�[�W�̃��l�̍ő�l
const float	MAX_ALPHA_YELLOW = 1.0f;	// ���F�̃Q�[�W�̃��l�̍ő�l
const float	MIN_ALPHA_GRAY = 0.3f;		// �D�F�̃Q�[�W�̃��l�̍ŏ��l
const float	MIN_ALPHA_YELLOW = 0.3f;	// ���F�̃Q�[�W�̃��l�̍ŏ��l
const D3DXVECTOR3 MOON_POS(140.5f, 90.5f, 0.0f);	// ���̍��W
const int MOONEFFECT_TIME = 45;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_nTimeMoon;			// ���̃G�t�F�N�g�̃^�C��
int		s_nTimeGauge;			// �Q�[�W�̃^�C��
int		s_nIdxGaugeGray;		// �D�F�̃Q�[�W�̔z��̃C���f�b�N�X
int		s_nIdxGaugeYellow;		// ���F�̃Q�[�W�̔z��̃C���f�b�N�X
float	s_fAlphaGaugeGray;		// �D�F�̃Q�[�W�̃��l
float	s_fAlphaGaugeYellow;	// ���F�̃Q�[�W�̃��l
}// namespace�͂����܂�

//--------------------------------------------------
// �Q�[�W�̐ݒ�
//--------------------------------------------------
void SetGaugeUI(void)
{
	s_nTimeGauge = 0;
	s_nTimeMoon = 0;
	s_fAlphaGaugeGray = MIN_ALPHA_GRAY;
	s_fAlphaGaugeYellow = MIN_ALPHA_YELLOW;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f);

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = s_fAlphaGaugeGray;

	// �Q�[�W�̐ݒ�
	s_nIdxGaugeGray = SetGauge(pos, col, SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);

	if ((GetMode() == MODE_TITLE) || (GetMode() == MODE_TUTORIAL))
	{// �^�C�g���A�`���[�g���A��
		return;
	}

	col = GetColor(COLOR_YELLOW);
	col.a = s_fAlphaGaugeYellow;

	float fWidth = 0.0f;

	if (GetMode() != MODE_GAME)
	{// �Q�[������Ȃ�
		fWidth = (GetLight() - 1) * (SCREEN_WIDTH / 16.0f);
	}

	// �Q�[�W�̐ݒ�
	s_nIdxGaugeYellow = SetGauge(pos, col, fWidth, SCREEN_HEIGHT, GAUGE_LEFT);
}

//--------------------------------------------------
// �Q�[�W�̍X�V
//--------------------------------------------------
void UpdateGaugeUI(void)
{
	s_nTimeGauge++;

	{// ���l�̕ύX
		float fCurve = CosCurve(s_nTimeGauge, 0.01f);
		s_fAlphaGaugeGray = Curve(fCurve, MAX_ALPHA_GRAY, MIN_ALPHA_GRAY);
		s_fAlphaGaugeYellow = Curve(fCurve, MAX_ALPHA_YELLOW, MIN_ALPHA_YELLOW);
	}

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = s_fAlphaGaugeGray;

	// �Q�[�W�̐F�̐ݒ�(�D�F)
	SetColorGauge(s_nIdxGaugeGray, col);

	if ((GetMode() == MODE_TITLE) || (GetMode() == MODE_TUTORIAL))
	{// �^�C�g���A�`���[�g���A��
		return;
	}

	col = GetColor(COLOR_YELLOW);
	col.a = s_fAlphaGaugeYellow;

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nIdxGaugeYellow, col);
}

//--------------------------------------------------
// �Q�[�W�̕ύX
//--------------------------------------------------
void ChangeGaugeUI(void)
{
	// �Q�[�W�̃T�C�Y�̐ݒ�
	SetSizeGauge(s_nIdxGaugeYellow, GetLight() * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT);
}

//--------------------------------------------------
// ���̃G�t�F�N�g�̍X�V
//--------------------------------------------------
void UpdateEffectMoonUI(void)
{
	if (s_nTimeMoon % MOONEFFECT_TIME == 0)
	{
		// �F�̐ݒ�
		D3DXCOLOR col = GetColor(COLOR_WHITE);
		col.b = 0.1f;

		// �G�t�F�N�g�̐ݒ�
		SetEffect(MOON_POS, EFFECT_TYPE_003, col);
	}

	s_nTimeMoon++;
}