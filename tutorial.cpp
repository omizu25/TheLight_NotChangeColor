//**************************************************
//
// Hackathon ( tutorial.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "tutorial.h"
#include "rectangle.h"
#include "texture.h"
#include "input.h"
#include "mode.h"
#include "game.h"
#include "sound.h"
#include "ui.h"
#include "bg.h"
#include "gauge.h"
#include "effect.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 900;	// �^�C���̍ő�l
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_nIdx;		// �w�i�̋�`�̃C���f�b�N�X
int		s_nTime;	// �^�C��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitTutorial(void)
{
	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W��UI�̐ݒ�
	SetGaugeUI();

	// �w�i�̏�����
	InitBG();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���̔w�i�̏�����
	InitMoonBG();

	// ��`�̐ݒ�
	s_nIdx = SetRectangle(TEXTURE_TITLE_GamePopup);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdx, pos, size);

	s_nTime = 0;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTutorial(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdx);

	// �Q�[�W�̏I��
	UninitGauge();

	// �w�i�̏I��
	UninitBG();

	// �G�t�F�N�g�̏I��
	UninitEffect();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTutorial(void)
{
	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{// �w��̒l���z����
		// ���[�h�̕ύX
		ChangeMode(MODE_GAME);
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		// ���[�h�̕ύX
		ChangeMode(MODE_GAME);
		
		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ENTER);
	}

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
void DrawTutorial(void)
{
	// ��`�̕`��
	DrawRectangle();
}
