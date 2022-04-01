//**************************************************
//
// Hackathon ( pause.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "menu.h"
#include "game.h"
#include "mode.h"
#include "texture.h"
#include "cursor.h"
#include "sound.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float		MENU_WIDTH = 350.0f;					// ���j���[�̕�
const float		MENU_HEIGHT = 125.0f;					// ���j���[�̍���
const float		MENU_LEFT = SCREEN_WIDTH * 0.3f;		// ���j���[�̍��[
const float		MENU_RIGHT = SCREEN_WIDTH * 0.7f;		// ���j���[�̉E�[
const float		MENU_TOP = SCREEN_HEIGHT * 0.35f;		// ���j���[�̏�[
const float		MENU_BOTTOM = SCREEN_HEIGHT * 0.85f;	// ���j���[�̉��[
const D3DXCOLOR	BG_COLOR(0.0f, 0.0f, 0.0f, 0.6f);		// �w�i�̐F
const D3DXCOLOR	FRAME_COLOR(0.5f, 0.5f, 1.0f, 1.0f);	// �t���[���̐F
const float		CURSOR_SIZE = 50.0f;					// �J�[�\���̃T�C�Y

typedef enum
{
	MENU_GAME = 0,	// �Q�[��
	MENU_TITLE,		// �^�C�g��
	MENU_MAX
}MENU;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nSelectMenu;	// �I�΂�Ă��郁�j���[
int	s_nIdxMenu;		// �g���Ă��郁�j���[�̔ԍ�
int	s_nIdxCursor;	// �J�[�\���̔z��̃C���f�b�N�X
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
void InitPause(void)
{
	s_nSelectMenu = 0;

	{// ���j���[
		MenuArgument menu;
		menu.nNumUse = MENU_MAX;
		menu.fLeft = MENU_LEFT;
		menu.fRight = MENU_RIGHT;
		menu.fTop = MENU_TOP;
		menu.fBottom = MENU_BOTTOM;
		menu.fWidth = MENU_WIDTH;
		menu.fHeight = MENU_HEIGHT;
		menu.bSort = true;

		menu.texture[MENU_GAME] = TEXTURE_BackToTitle;
		menu.texture[MENU_TITLE] = TEXTURE_ReturnToGame;

		FrameArgument Frame;
		Frame.bUse = true;
		Frame.col = FRAME_COLOR;
		Frame.texture = TEXTURE_NONE;

		// ���j���[�̐ݒ�
		s_nIdxMenu = SetMenu(menu, Frame);
	}

	{// �J�[�\��
		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.345f;
		cursor.fTop = MENU_TOP;
		cursor.fBottom = MENU_BOTTOM;
		cursor.fWidth = CURSOR_SIZE;
		cursor.fHeight = CURSOR_SIZE;
		cursor.texture = TEXTURE_Cursor_Right;
		cursor.nSelect = s_nSelectMenu;
		cursor.bRotation = false;

		// �J�[�\���̐ݒ�
		s_nIdxCursor = SetCursor(cursor);
	}

	// ���j���[�̕`�悷�邩�ǂ���
	SetDrawMenu(s_nIdxMenu, false);

	// �J�[�\���̕`�悷�邩�ǂ���
	SetDrawCursor(s_nIdxCursor, false);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPause(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePause(void)
{
	// ����
	Input();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPause(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetPause(void)
{
	// ���j���[�̕`�悷�邩�ǂ���
	SetDrawMenu(s_nIdxMenu, true);

	// �J�[�\���̕`�悷�邩�ǂ���
	SetDrawCursor(s_nIdxCursor, true);

	s_nSelectMenu = 0;

	// �I�����̐F�̏�����
	InitColorOption();

	// �I�����̕ύX
	ChangeOption(s_nSelectMenu);

	// �I�����̐F�̏�����
	InitColorOption();

	// �ʒu�̕ύX
	ChangePosCursor(s_nIdxCursor, s_nSelectMenu);
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void ResetPause(void)
{
	// ���j���[�̕`�悷�邩�ǂ���
	SetDrawMenu(s_nIdxMenu, false);

	// �J�[�\���̕`�悷�邩�ǂ���
	SetDrawCursor(s_nIdxCursor, false);

	// �I�����̐F�̏�����
	InitColorOption();
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

	if (GetMoveKeyTrigger(MOVE_KEY_UP))
	{// W�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu - 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetMoveKeyTrigger(MOVE_KEY_DOWN))
	{// S�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu + 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		switch (s_nSelectMenu)
		{
		case MENU_GAME:		// �Q�[��
			// �|�[�Y�̗L�������ݒ�
			SetEnablePause(false);

			// ���Z�b�g
			ResetPause();
			break;

		case MENU_TITLE:	// �^�C�g��
			ChangeMode(MODE_TITLE);
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
