//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,	// �^�C�g��
	SOUND_LABEL_BGM_GAME,		// �Q�[��
	SOUND_LABEL_BGM_RESULT,		// ���U���g
	SOUND_LABEL_SE_ENTER,		// ���艹
	SOUND_LABEL_SE_SELECT,		// �I����
	SOUND_LABEL_SE_MISS,	// �~�X��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
