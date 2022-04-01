//**************************************************
//
// Hackathon ( player.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"
#include "answer.h"
#include "time.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 5;			// �^�C���̍ő�l
const int	MAX_LIGHT = 16;			// ���C�g�̍ő吔
const float	LIGHT_SIZE = 50.0f;		// ���C�g�̃T�C�Y
const float	PUSH_WIDTH = 120.0f;	// �����̕�
const float	PUSH_HEIGHT = 80.0f;	// �����̍���

typedef enum
{
	LIGHT_COLOR_RED = 0,	// ��
	LIGHT_COLOR_GREEN,		// ��
	LIGHT_COLOR_BLUE,		// ��
	LIGHT_COLOR_YELLOW,		// ���F
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
COLOR	s_aColor[LIGHT_COLOR_MAX];		// ���C�g�̐F
int		s_nPlayer;						// ���C�g�̌��݂̐�
int		s_nIdxPush;						// �����̋�`�̃C���f�b�N�X
int		s_nIdxSelect;					// ���j���[�̔z��̃C���f�b�N�X
int		s_nIdxFrame;					// �g�̔z��̃C���f�b�N�X
int		s_nIdxColor[MAX_LIGHT];			// �F�̔ԍ�
TEXTURE	s_aTexture[LIGHT_COLOR_MAX];	// �e�N�X�`��
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�֐��v���g�^�C�v�錾
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;
	s_aTexture[LIGHT_COLOR_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_COLOR_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_COLOR_BLUE] = TEXTURE_Blue;
	s_aTexture[LIGHT_COLOR_YELLOW] = TEXTURE_Yellow;

	s_nPlayer = 0;

	{// ����
		// ��`�̐ݒ�
		s_nIdxPush = SetRectangle(TEXTURE_Push);

		D3DXVECTOR3 size = D3DXVECTOR3(PUSH_WIDTH, PUSH_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(PUSH_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxPush, pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdxPush, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	{// �g
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = PUSH_WIDTH;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_Hackathon_Ring;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxFrame = SetSelect(select);
	}

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = PUSH_WIDTH;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxSelect = SetSelect(select);
	}

	// �`��̃��Z�b�g
	ResetDrawPlayer();

	// �^�C���̐ݒ�
	SetTime(MAX_TIME);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPlayer(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxPush);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePlayer(void)
{
	if (GetFade() != FADE_NONE)
	{
		return;
	}

	switch (GetGameState())
	{
	case GAMESTATE_RESET:	// ���Z�b�g���
		// �`��̃��Z�b�g
		ResetDrawPlayer();

		// �Q�[����Ԃ̐ݒ�
		SetGameState(GAMESTATE_SAMPLE);
		break;

	case GAMESTATE_PLAYER:	// �v���C���[���

		if (GetAnswer())
		{// �ő�l
			return;
		}

		if (GetLightKeyTrigger(LIGHT_KEY_RED))
		{// ��
			PlaySound(SOUND_LABEL_SE_SELECT);
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_RED;

			// �Z���N�g�̃e�N�X�`���̐ݒ�
			ChangeTextuteSelect(s_nIdxSelect, s_nPlayer, s_aTexture[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetIdxBG(0), GetColor(COLOR_RED));

			s_nPlayer++;

			// �g�̐ݒ�
			SetFramePlayer(s_nPlayer);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[s_nPlayer - 1]]));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_GREEN))
		{// ��
			PlaySound(SOUND_LABEL_SE_SELECT);
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_GREEN;

			// �Z���N�g�̃e�N�X�`���̐ݒ�
			ChangeTextuteSelect(s_nIdxSelect, s_nPlayer, s_aTexture[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetIdxBG(0), GetColor(COLOR_GREEN));

			s_nPlayer++;

			// �g�̐ݒ�
			SetFramePlayer(s_nPlayer);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[s_nPlayer - 1]]));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_BLUE))
		{// ��
			PlaySound(SOUND_LABEL_SE_SELECT);
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_BLUE;

			// �Z���N�g�̃e�N�X�`���̐ݒ�
			ChangeTextuteSelect(s_nIdxSelect, s_nPlayer, s_aTexture[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetIdxBG(0), GetColor(COLOR_BLUE));

			s_nPlayer++;

			// �g�̐ݒ�
			SetFramePlayer(s_nPlayer);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[s_nPlayer - 1]]));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_YELLOW))
		{// ���F
			PlaySound(SOUND_LABEL_SE_SELECT);
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_YELLOW;

			// �Z���N�g�̃e�N�X�`���̐ݒ�
			ChangeTextuteSelect(s_nIdxSelect, s_nPlayer, s_aTexture[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);
		
			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetIdxBG(0), GetColor(COLOR_YELLOW));

			s_nPlayer++;

			// �g�̐ݒ�
			SetFramePlayer(s_nPlayer);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[s_nPlayer - 1]]));
		}
		break;

	case GAMESTATE_SAMPLE:	// ���{���
	case GAMESTATE_NONE:	// �������Ă��Ȃ����
	case GAMESTATE_START:	// �J�n���
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPlayer(void)
{
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetPlayer(void)
{
	return s_nPlayer;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
int GetColorPlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// �g�̐ݒ�
//--------------------------------------------------
void SetFramePlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	if (GetAnswer())
	{// �ő�l
		return;
	}

	// �Z���N�g�̕`�悷�邩�ǂ���
	SetDrawSelect(s_nIdxFrame, nNowLight, true);

	// �^�C���̈ʒu�̐ݒ�
	SetPosTime(GetPosSelect(s_nIdxSelect, nNowLight));
}

//--------------------------------------------------
// �����̐F�̐ݒ�
//--------------------------------------------------
void SetColorPushPlayer(D3DXCOLOR col)
{
	// ��`�̐F�̐ݒ�
	SetColorRectangle(s_nIdxPush, col);
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	s_nPlayer = 0;
}
}// namespace�͂����܂�