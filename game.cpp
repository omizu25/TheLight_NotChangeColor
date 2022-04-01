//**************************************************
//
// FPD���� ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "sound.h"
#include "rectangle.h"
#include "fan.h"
#include "pause.h"
#include "menu.h"
#include "number.h"
#include "bg.h"
#include "cursor.h"
#include "gauge.h"
#include "effect.h"
#include "color.h"
#include "time.h"
#include "score.h"
#include "ranking.h"
#include "light.h"
#include "select.h"
#include "player.h"
#include "answer.h"
#include "tutorial.h"
#include "utility.h"
#include "ui.h"

#include <assert.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// �Q�[���̏��
int			s_nCounterState;				// ��ԊǗ��J�E���^�[
bool		s_bPause = false;				// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
int			s_nIdxMethod;					// ��������̋�`�̃C���f�b�N�X
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W��UI�̐ݒ�
	SetGaugeUI();

	// �w�i�̏�����
	InitBG();

	{// ���[��
		D3DXCOLOR col = GetColor(COLOR_GRAY);
		col.a = 0.75f;

		// �Q�[�W�̐ݒ�
		SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.35f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);

		// �Q�[�W�̐ݒ�
		SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);
	}

	// ���̏�����
	InitNumber();

	// �^�C���̏�����
	InitTime();

	// �Z���N�g�̏�����
	InitSelect();

	// ���C�g�̏�����
	InitLight();

	// �v���C���[�̏�����
	InitPlayer();

	// �A���T�[�̏�����
	InitAnswer();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���̔w�i�̏�����
	InitMoonBG();

	{// �������
		// ��`�̐ݒ�
		s_nIdxMethod = SetRectangle(TEXTURE_Method);

		D3DXVECTOR3 pos(SCREEN_WIDTH - 100.0f, 95.0f, 0.0f);
		D3DXVECTOR3 size(155.0f, 155.0f, 0.0f);

		SetPosRectangle(s_nIdxMethod, pos, size);
	}

	// ���j���[�̏�����
	InitMenu();

	// �J�[�\���̏�����
	InitCursor();

	// �|�[�Y�̏�����
	InitPause();

	// �T�E���h�J�n
	PlaySound(SOUND_LABEL_BGM_GAME);

	s_gameState = GAMESTATE_SAMPLE;	// �T���v����Ԃɐݒ�

	s_nCounterState = 0;	// �J�E���^�[�̏�����

	s_bPause = false;	// �|�[�Y����
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGame(void)
{
	// �T�E���h�̒�~
	StopSound();

	// �w�i�̏I��
	UninitBG();

	// �Q�[�W�̏I��
	UninitGauge();

	// ���̏I��
	UninitNumber();

	// �^�C���̏I��
	UninitTime();

	// �|�[�Y�̏I��
	UninitPause();

	// �Z���N�g�̏I��
	UninitSelect();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();

	// �G�t�F�N�g�̏I��
	UninitEffect();

	// ���C�g�̏I��
	UninitLight();

	// �v���C���[�̏I��
	UninitPlayer();

	// �A���T�[�̏I��
	UninitAnswer();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxMethod);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// P�L�[�������ꂽ
		if (GetFade() != FADE_NONE)
		{// �t�F�[�h���Ă�
			return;
		}

		if (GetAnswer())
		{// �ő�l�ɂȂ���
			return;
		}

		if (s_gameState == GAMESTATE_PLAYER)
		{// �ʏ��Ԃ̎�
			s_bPause = !s_bPause;

			if (s_bPause)
			{// �|�[�Y���Ă�
				// �|�[�Y�̐ݒ�
				SetPause();
			}
			else
			{// �|�[�Y���ĂȂ�
				// �|�[�Y�̃��Z�b�g
				ResetPause();
			}
		}
	}

	if (s_bPause)
	{// �|�[�Y���Ă���
		// �|�[�Y�̍X�V
		UpdatePause();

		// ���j���[�̍X�V
		UpdateMenu();

		// �J�[�\���̍X�V
		UpdateCursor();

		// �Q�[�W��UI�̍X�V
		UpdateGaugeUI();

		// ���̃G�t�F�N�g�̍X�V
		UpdateEffectMoonUI();

		// �G�t�F�N�g�̍X�V
		UpdateEffect();

		return;
	}

	// �w�i�̍X�V
	UpdateBG();

	// ���C�g�̍X�V
	UpdateLight();

	// �v���C���[�̍X�V
	UpdatePlayer();

	// �A���T�[�̍X�V
	UpdateAnswer();

	// �Q�[�W�̍X�V
	UpdateGauge();

	// �Z���N�g�̍X�V
	UpdateSelect();

	// ���j���[�̍X�V
	UpdateMenu();

	// �^�C���̍X�V
	UpdateTime();

	// �Q�[�W��UI�̍X�V
	UpdateGaugeUI();

	// ���̃G�t�F�N�g�̍X�V
	UpdateEffectMoonUI();

	// �G�t�F�N�g�̍X�V
	UpdateEffect();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGame(void)
{
	// ��`�̕`��
	DrawRectangle();

	// �~�`�̕`��
	DrawFan();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetGameState(GAMESTATE state)
{
	assert(state >= 0 && state < GAMESTATE_MAX);

	s_gameState = state;
	s_nCounterState = 0;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
GAMESTATE GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// �|�[�Y�̗L�������ݒ�
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}

//--------------------------------------------------
// �|�[�Y�̗L�������擾
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_bPause;
}
