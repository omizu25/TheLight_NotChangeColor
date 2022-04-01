//**************************************************
// 
// Hackathon ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �񋓌^
//==================================================
typedef enum
{
	TEXTURE_Cursor_Right = 0,	// �J�[�\��
	TEXTURE_TITLE_LOGO,			// �^�C�g�����S
	TEXTURE_TITLE_UI,			// ����
	TEXTURE_TITLE_GamePopup,	// �`���[�g���A��
	TEXTURE_BackToTitle,		// �Q�[���ɖ߂�
	TEXTURE_ReturnToGame,		// �^�C�g���ɖ߂�
	TEXTURE_Hackathon_Ring,		// ���C�g�̘g
	TEXTURE_BG_0,				// ��
	TEXTURE_BG_1,				// ��
	TEXTURE_BG_2,				// �w�i
	TEXTURE_BG_MOON,			// ��
	TEXTURE_end,				// ��߂�
	TEXTURE_play,				// �V��
	TEXTURE_Learn,				// �o����
	TEXTURE_Push,				// ����
	TEXTURE_Red,				// ��
	TEXTURE_Green,				// ��
	TEXTURE_Blue,				// ��
	TEXTURE_Yellow,				// ���F
	TEXTURE_effect_000,			// �G�t�F�N�g
	TEXTURE_effect_001,			// �G�t�F�N�g
	TEXTURE_effect_002,			// �G�t�F�N�g
	TEXTURE_Number_Neon,		// �i���o�[�摜(�l�I��)
	TEXTURE_Method,				// �������
	TEXTURE_YourScore,			// ���ȃX�R�A
	TEXTURE_BestScore,			// �x�X�g�X�R�A
	TEXTURE_MAX,
	TEXTURE_NONE,				// �g�p���Ȃ�
}TEXTURE;

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void);

//--------------------------------------------------
// �擾
// ����  : TEXTURE texture / �񋓌^ ���
// �Ԓl  : LPDIRECT3DTEXTURE9 / �e�N�X�`��
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture);

#endif // !_TEXTURE_H_
