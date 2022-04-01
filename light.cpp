//**************************************************
//
// Hackathon ( light.cpp )
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
#include "time.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_LIGHT = 16;			// ���C�g�̍ő吔
const int	MAX_TIME = 90;			// �^�C���̍ő�l
const int	REPEAT_TIME = 30;		// �^�C���̌J��Ԃ�
const float	LIGHT_SIZE = 50.0f;		// ���C�g�̃T�C�Y
const float	LEARN_WIDTH = 120.0f;	// �o����̕�
const float	LEARN_HEIGHT = 80.0f;	// �o����̍���

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
int		s_nNowLight;					// ���C�g�̌��ݐ�
int		s_nMaxLight;					// ���C�g�̍ő吔
int		s_nIdxLearn;					// �o����̋�`�̃C���f�b�N�X
int		s_nIdxSelect;					// ���j���[�̔z��̃C���f�b�N�X
int		s_nIdxFrame;					// �g�̔z��̃C���f�b�N�X
int		s_nTime;						// �^�C��
int		s_nIdxColor[MAX_LIGHT];			// �F�̔ԍ�
bool	s_bMax;							// �����؂���
COLOR	s_aColor[LIGHT_COLOR_MAX];		// ���C�g�̐F
TEXTURE	s_aTexture[LIGHT_COLOR_MAX];	// �e�N�X�`��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void ResetDrawLight(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitLight(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;
	s_aTexture[LIGHT_COLOR_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_COLOR_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_COLOR_BLUE] = TEXTURE_Blue;
	s_aTexture[LIGHT_COLOR_YELLOW] = TEXTURE_Yellow;

	s_nNowLight = 0;
	s_nMaxLight = 1;

	{// �o����
		// ��`�̐ݒ�
		s_nIdxLearn = SetRectangle(TEXTURE_Learn);

		D3DXVECTOR3 size = D3DXVECTOR3(LEARN_WIDTH, LEARN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(LEARN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.35f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxLearn, pos, size);
	}

	{// �g
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = LEARN_WIDTH;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
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

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = LEARN_WIDTH;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
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

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		s_nIdxColor[i] = IntRandam(LIGHT_COLOR_MAX, 0);

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
	}

	// ���}���u
	s_nIdxColor[0] = IntRandam(LIGHT_COLOR_MAX, 0);

	// �Z���N�g�̃e�N�X�`���̐ݒ�
	ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[s_nIdxColor[0]]);

	// �`��̃��Z�b�g
	ResetDrawLight();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitLight(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxLearn);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateLight(void)
{
	switch (GetGameState())
	{
	case GAMESTATE_SAMPLE:	// ���{���
		s_nTime++;

		if (s_nTime % REPEAT_TIME != 0)
		{
			return;
		}

		if (s_nNowLight < s_nMaxLight)
		{
			s_bMax = false;
			s_nNowLight++;
			
			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nNowLight - 1), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[s_nNowLight - 1]]));
			
			// �`��̃��Z�b�g
			ResetDrawLight();
		}
		else
		{// �����؂���
			if (s_bMax)
			{
				if (s_nTime >= MAX_TIME)
				{
					for (int i = 0; i < MAX_LIGHT; i++)
					{
						// �Z���N�g�̕`�悷�邩�ǂ���
						SetDrawSelect(s_nIdxSelect, i, false);
					}

					for (int i = 0; i < s_nNowLight; i++)
					{
						// �Z���N�g�̕`�悷�邩�ǂ���
						SetDrawSelect(s_nIdxFrame, i, true);
					}

					// �Q�[����Ԃ̐ݒ�
					SetGameState(GAMESTATE_PLAYER);

					// ��`�̐F�̐ݒ�
					SetColorRectangle(s_nIdxLearn, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

					// �����̐F�̐ݒ�
					SetColorPushPlayer(GetColor(COLOR_WHITE));
					
					// �g�̐ݒ�
					SetFramePlayer(0);
				}
			}
			else
			{
				s_nTime = 0;
				s_bMax = true;
			}
		}
		break;

	case GAMESTATE_RESET:	// ���Z�b�g���
		s_nNowLight = 0;
		s_nMaxLight++;
		s_nTime = 0;

		if (s_nMaxLight > MAX_LIGHT)
		{
			// ���[�h�̕ύX
			ChangeMode(MODE_RESULT);
		}

		for (int i = s_nMaxLight - 1; i < MAX_LIGHT; i++)
		{
			s_nIdxColor[i] = IntRandam(LIGHT_COLOR_MAX, 0);

			// �Z���N�g�̃e�N�X�`���̐ݒ�
			ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
		}

		// �`��̃��Z�b�g
		ResetDrawLight();

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdxLearn, GetColor(COLOR_WHITE));

		break;

	case GAMESTATE_PLAYER:	// �v���C���[���
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
void DrawLight(void)
{
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetLight(void)
{
	return s_nMaxLight;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
int GetColorLight(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// �`��̐ݒ�
//--------------------------------------------------
void SetDrawLight(int nNowLight)
{
	// �Z���N�g�̕`�悷�邩�ǂ���
	SetDrawSelect(s_nIdxSelect, nNowLight, true);

	// �G�t�F�N�g�̐ݒ�
	SetEffect(GetPosSelect(s_nIdxSelect, nNowLight), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[nNowLight]]));
}

//--------------------------------------------------
// �Ԉ����
//--------------------------------------------------
void MistakeLight(void)
{
	for (int i = (GetPlayer() + 1); i < s_nMaxLight; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, true);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(GetPosSelect(s_nIdxSelect, i), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[i]]));
	}
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawLight(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < s_nNowLight; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, true);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	s_bMax = false;
}
}// namespace�͂����܂�
