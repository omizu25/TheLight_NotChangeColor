//**************************************************
// 
// Hackathon ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// �萔
//==================================================
namespace
{
const char *s_FileName[] =
{// �e�N�X�`���̃p�X	
	"data/TEXTURE/Cursor_Right.png",				// �J�[�\��
	"data/TEXTURE/Title.png",						// �^�C�g�����S
	"data/TEXTURE/Hackathon_TitleUI.png",			// ����
	"data/TEXTURE/Hackathon_GamePopup.png",			// �`���[�g���A��
	"data/TEXTURE/Hackathon_ReturnToGame.png",		// �Q�[���ɖ߂�
	"data/TEXTURE/Hackathon_BackToTitle.png",		// �^�C�g���ɖ߂�
	"data/TEXTURE/Hackathon_Ring.png",				// ���C�g�̘g
	"data/TEXTURE/Bg000.png",						// ��
	"data/TEXTURE/Bg001.png",						// ��
	"data/TEXTURE/Bg002.png",						// �w�i
	"data/TEXTURE/BgMoon.png",						// ��
	"data/TEXTURE/end.png",							// ��߂�
	"data/TEXTURE/play.png",						// �V��
	"data/TEXTURE/Learn.png",						// �o����
	"data/TEXTURE/Push.png",						// ����
	"data/TEXTURE/Hackathon_Direction_Red.png",		// ��
	"data/TEXTURE/Hackathon_Direction_Green.png",	// ��
	"data/TEXTURE/Hackathon_Direction_Blue.png",	// ��
	"data/TEXTURE/Hackathon_Direction_Yellow.png",	// ���F
	"data/TEXTURE/effect/effect_000.png",			// �G�t�F�N�g
	"data/TEXTURE/effect/effect_001.jpg",			// �G�t�F�N�g
	"data/TEXTURE/effect/effect_003.jpg",			// �G�t�F�N�g
	"data/TEXTURE/Number_Neon.png",					// �i���o�[�摜(�l�I��)
	"data/TEXTURE/Method_of_operation_white.png",	// �������
	"data/TEXTURE/Hackathon_YourScore.png",			// ���ȃX�R�A
	"data/TEXTURE/Hackathon_BestScore.png",			// �x�X�g�X�R�A
};
}// namespace�͂����܂�

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespace�͂����܂�

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture)
{
	if (texture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(texture >= 0 && texture < TEXTURE_MAX);

	return s_pTexture[texture];
}
