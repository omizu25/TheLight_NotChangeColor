//=============================================================================
//
// ���͏��� [input.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------

#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")//���͏����ɕK�v�i�W���C�p�b�g�j

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------

#include "main.h"

//----------------------------------------------------------------------------
//�񋓌^
//----------------------------------------------------------------------------

//�L�[���(�W���C�p�b�h)
typedef enum
{
	JOYKEY_CROSS_UP = 0,		//�\���{�^����
	JOYKEY_CROSS_DOWN,			//�\���{�^����
	JOYKEY_CROSS_LEFT,			//�\���{�^����
	JOYKEY_CROSS_RIGHT,			//�\���{�^���E
	JOYKEY_START,				//�X�^�[�g�{�^��
	JOYKEY_BACK,				//�o�b�N�{�^��
	JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
	JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
	JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
	JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
	JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
	JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
	JOYKEY_A,					//A�{�^��
	JOYKEY_B,					//B�{�^��
	JOYKEY_X,					//X�{�^��
	JOYKEY_Y,					//Y�{�^��
	JOYKEY_STICK_UP = 0,		//��	(8�����X�e�B�b�N)
	JOYKEY_STICK_UP_RIGHT,		//�E��	(8�����X�e�B�b�N)
	JOYKEY_STICK_RIGHT,			//�E	(8�����X�e�B�b�N)
	JOYKEY_STICK_DOWN_RIGHT,	//�E��	(8�����X�e�B�b�N)
	JOYKEY_STICK_DOWN,			//��	(8�����X�e�B�b�N)
	JOYKEY_STICK_DOWN_LEFT,		//����	(8�����X�e�B�b�N)
	JOYKEY_STICK_LEFT,			//��	(8�����X�e�B�b�N)
	JOYKEY_STICK_UP_LEFT,		//����	(8�����X�e�B�b�N)
	JOYKEY_MAX
}JOYKEY;

//�X�e�B�b�N����(�W���C�p�b�h)
typedef enum
{
	JOYKEY_RIGHT_STICK = 0,
	JOYKEY_LEFT_STICK,
	JOYKEY_RIGHT_LEFT_MAX
}JOYKEY_RIGHT_LEFT;

//�ړ��n�̃L�[�܂Ƃ�
typedef enum
{
	MOVE_KEY_UP = 0,		//��L�[
	MOVE_KEY_DOWN,			//���L�[
	MOVE_KEY_RIGHT,			//�E�L�[
	MOVE_KEY_LEFT,			//���L�[
	MOVE_KEY_MAX
}MOVE_KEY;

//�L�[�^�C�v
typedef enum
{
	FUNCTION_KEY_DESISION = 0,		//����L�[
	FUNCTION_KEY_PAUSE,				//�|�[�Y�L�[
	FUNCTION_KEY_MAX
}FUNCTION_KEY;

//���C�g�̐F�I���L�[
typedef enum
{
	LIGHT_KEY_RED = 0,			//�ԃL�[
	LIGHT_KEY_GREEN,			//�΃L�[
	LIGHT_KEY_BLUE,				//�L�[
	LIGHT_KEY_YELLOW,			//���L�[
	LIGHT_KEY_MAX
}LIGHT_KEY;

//----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//----------------------------------------------------------------------------

//���͏����̃v���g�^�C�v�錾

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
void UninitInput(void);									//���͏����S���̏I������
void UpdateInput(void);									//���͏����S���̍X�V����

														//�v���g�^�C�v�錾�L�[�{�[�h
bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�v���X����
bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�g���K�[����
bool GetKeyboardAllPress(void);							//�L�[�{�[�h�S�L�[�v���X����
bool GetKeyboardAllTrigger(void);						//�L�[�{�[�h�S�L�[�g���K�[����

//�v���g�^�C�v�錾�W���C�p�b�g
bool GetJoypadPress(JOYKEY Key, int nPlayer);													//�W���C�p�b�h�v���X����
bool GetJoypadTrigger(JOYKEY Key, int nPlayer);													//�W���C�p�b�h�g���K�[����
D3DXVECTOR3 GetJoypadStick(JOYKEY_RIGHT_LEFT RightLeft, int nPlayer);							//�W���C�p�b�h�X�e�B�b�N����
int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);												//�W���C�p�b�h�g���K�[�y�_������
bool GetJoypadStickPress(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key, int nPlayer);			//�W���C�p�b�h�X�e�B�b�N�v���X�W����
bool GetJoypadStickTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key, int nPlayer);			//�W���C�p�b�h�X�e�B�b�N�g���K�[�W����			
bool GetJoypadStickAllTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key);					//�W���C�p�b�h�X�e�B�b�N�g���K�[�W�����̑S�v���C���[�̑Ώ�
bool GetJoypadAllTrigger(JOYKEY Key);															//�W���C�p�b�h�g���K�[�̑S�v���C���[�̑Ώ�

bool GetMoveKeyPress(MOVE_KEY Key);									//�ړ��n�̃L�[�܂Ƃ�
bool GetMoveKeyTrigger(MOVE_KEY Key);								//�ړ��n�̃L�[�܂Ƃ߃g���K�[
bool GetFunctionKeyTrigger(FUNCTION_KEY Key);						//�@�\�n�̃L�[�܂Ƃ�
bool GetLightKeyPress(LIGHT_KEY Key);									//���C�g�̐F�I���L�[�̃v���X
bool GetLightKeyTrigger(LIGHT_KEY Key);									//���C�g�̐F�I���L�[�̃g���K�[

#endif