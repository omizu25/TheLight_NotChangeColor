//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "menu.h"
#include "mode.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "cursor.h"
#include "gauge.h"
#include "utility.h"
#include "effect.h"
#include "bg.h"
#include "ui.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// �^�C�g���̕�
const float	TITLE_HEIGHT = 600.0f;	// �^�C�g���̍���
const float	MENU_WIDTH = 300.0f;	// ���j���[�̕�
const float	MENU_HEIGHT = 80.0f;	// ���j���[�̍���
const float	CURSOR_SIZE = 50.0f;	// �J�[�\���̃T�C�Y

typedef enum
{
	MENU_GAME = 0,	// �Q�[��
	MENU_MAX
}MENU;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxLogo;			// ���S�̋�`�̃C���f�b�N�X
int	s_nSelectMenu;		// �I�΂�Ă��郁�j���[
int	s_nIdxMenu;			// ���j���[�̔z��̃C���f�b�N�X
int	s_nIdxCursor;		// �J�[�\���̔z��̃C���f�b�N�X
int	s_nGaugeIdxGray;	// �Q�[�W�̃C���f�b�N�X�̕ۊ�
float s_fGaugeAlpha;	// ���݂̃Q�[�W�̃A���t�@�l
int	s_nTime;			// �^�C��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Input(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTitle(void)
{
	// �T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);

	s_nSelectMenu = 0;
	s_nTime = 0;
	s_fGaugeAlpha = 0.3f;

	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W��UI�̐ݒ�
	SetGaugeUI();
	
	// �w�i
	InitBG();

	// �G�t�F�N�g
	InitEffect();

	// ���̔w�i�̏�����
	InitMoonBG();

	{// ���S
		// ��`�̐ݒ�
		s_nIdxLogo = SetRectangle(TEXTURE_TITLE_LOGO);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxLogo, pos, size);
	}

	{// ���j���[
		// ���j���[�̏�����
		InitMenu();

		MenuArgument menu;
		menu.nNumUse = MENU_MAX;
		menu.fLeft = SCREEN_WIDTH * 0.55f;
		menu.fRight = SCREEN_WIDTH * 0.95f;
		menu.fTop = 0.0f;
		menu.fBottom = SCREEN_HEIGHT;
		menu.fWidth = MENU_WIDTH;
		menu.fHeight = MENU_HEIGHT;
		menu.bSort = true;

		menu.texture[MENU_GAME] = TEXTURE_TITLE_UI;

		FrameArgument Frame;
		Frame.bUse = true;
		Frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		Frame.texture = TEXTURE_NONE;

		// ���j���[�̐ݒ�
		s_nIdxMenu = SetMenu(menu, Frame);

		// �I�����̐F�̐ݒ�
		SetColorOption(s_nIdxMenu, GetColor(COLOR_WHITE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// �I�΂�Ă��Ȃ��I�����̐F�̐ݒ�
		SetColorDefaultOption(s_nIdxMenu, GetColor(COLOR_WHITE));
	}

	{// �J�[�\��
		// �J�[�\��������
		InitCursor();

		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.65f;
		cursor.fTop = 0.0f;
		cursor.fBottom = SCREEN_HEIGHT;
		cursor.fWidth = CURSOR_SIZE;
		cursor.fHeight = CURSOR_SIZE;
		cursor.texture = TEXTURE_Cursor_Right;
		cursor.nSelect = s_nSelectMenu;
		cursor.bRotation = false;

		// �J�[�\���̐ݒ�
		s_nIdxCursor = SetCursor(cursor);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTitle(void)
{
	//�T�E���h��~
	StopSound();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();

	// �G�t�F�N�g
	UninitEffect();

	// �w�i
	UninitBG();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxLogo);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTitle(void)
{
	// ����
	Input();

	// ���j���[�̍X�V
	UpdateMenu();

	// �J�[�\���̍X�V
	UpdateCursor();

	s_nTime++;

	// �Q�[�W��UI�̍X�V
	UpdateGaugeUI();

	// �G�t�F�N�g
	UpdateEffect();

	// ���̃G�t�F�N�g�̍X�V
	UpdateEffectMoonUI();

	{
		D3DXVECTOR3 pos(SCREEN_WIDTH * 0.4f + FloatRandam(100.0f, -100.0f), SCREEN_HEIGHT * 0.4f + FloatRandam(20.0f, -20.0f), 0.0f);
		D3DXCOLOR col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);

		col.b = 0.1f;

		if (s_nTime % 65 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
	}

	{
		D3DXVECTOR3 pos(SCREEN_WIDTH * 0.15f + FloatRandam(100.0f, -100.0f), SCREEN_HEIGHT * 0.6f + FloatRandam(20.0f, -20.0f), 0.0f);
		D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		col.b = 0.1f;

		if (s_nTime % 75 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTitle(void)
{
	// ��`�̕`��
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// ����
//--------------------------------------------------
void Input(void)
{
	if (GetFade() != FADE_NONE)
	{// �t�F�[�h���Ă���
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		switch (s_nSelectMenu)
		{
		case MENU_GAME:	// �Q�[��
			ChangeMode(MODE_TUTORIAL);
			break;

		default:
			assert(false);
			break;
		}

		// �I�����̌���
		DecisionOption();

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ENTER);
	}
}
}// namespace�͂����܂�
