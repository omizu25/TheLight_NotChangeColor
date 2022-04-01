//=============================================================================
//
// ���͏��� [jobiusinput.cpp]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------

#include "input.h"
#include "game.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------

#define NUM_KEY_MAX		(256)	//�L�[�̍ő吔�i�L�[�{�[�h�j
#define PLAYER_MAX		(4)		//�v���C���[�̍ő�l��

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------

//�L�[�{�[�h
LPDIRECTINPUT8 g_pInput = NULL;						//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;			//���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];				//�L�[�{�[�h�̃g���K�[���

//�W���C�p�b�h
XINPUT_STATE g_JoyKeyState[PLAYER_MAX];				//�W���C�p�b�g�̃v���X���
XINPUT_STATE g_JoyKeyStateTrigger[PLAYER_MAX];		//�W���C�p�b�g�̃g���K�[���
D3DXVECTOR3 g_JoyStickPos[PLAYER_MAX];				//�W���C�X�e�B�b�N�̌X��
JOYKEY g_OldJoyKeyStick[PLAYER_MAX][JOYKEY_RIGHT_LEFT_MAX];			//�O��̃X�e�B�b�N�̈ʒu
FUNCTION_KEY g_OldFunctionKey;										//�O��̋@�\�L�[�̏��
LIGHT_KEY g_OldLightKey = LIGHT_KEY_MAX;							//�O��̃��C�g�̃L�[�̏��
MOVE_KEY g_OldMoveKey;

int g_nKeyCnt;

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//�L�[�{�[�h
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//������
void UninitKeyboard(void);								//�I������
void UpdateKeyboard(void);								//�X�V����

														//�W���C�p�b�h
HRESULT InitJoypad(void);								//������
void UninitJoypad(void);								//�I������
void UpdateJoypad(void);								//�X�V����

//*************************************************************************************
//���͏����S��
//*************************************************************************************

//���͏����S���̏�����
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	g_nKeyCnt = 0;

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	
	//�W���C�p�b�h������
	InitJoypad();

	return S_OK;
}

//���͏����S���̏I������
void UninitInput(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�h�I������
	UninitJoypad();
}

//���͏����S���̍X�V����
void UpdateInput(void)
{
	if (GetEnablePause())
	{
		g_nKeyCnt = 20;
	}

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�h�X�V����
	UpdateJoypad();

	g_nKeyCnt--;
}


//*****************************************************************************
//�L�[�{�[�h���͏���
//*****************************************************************************

//�L�[�{�[�h����������
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//�L�[�{�[�h�̏I������
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̕���
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//�L�[�{�[�h�̍X�V����
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//�L�[�{�[�h�̃v���X�����擾
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃g���K�[�����擾
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̑S�L�[�v���X�����擾
bool GetKeyboardAllPress(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardPress(nCntKey))
		{
			return true;
		}
	}
	return false;
}

//�L�[�{�[�h�̑S�L�[�g���K�[�����擾
bool GetKeyboardAllTrigger(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardTrigger(nCntKey))
		{
			return true;
		}
	}
	return false;
}

//*************************************************************************************
//�W���C�p�b�h���͏���
//*************************************************************************************

//�W���C�p�b�h�̏�����
HRESULT InitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�������[�̃N���A
		memset(&g_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&g_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));
	}
	return S_OK;
}

//�W���C�p�b�h�̏I��
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//�W���C�p�b�h�̍X�V
void UpdateJoypad(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		//�W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			g_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~g_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons; //�g���K�[����ۑ�
			g_JoyKeyState[nCnt] = JoyKeyState[nCnt];  //�v���X����
		}
	}
}

//�W���C�p�b�h�̃v���X����
bool GetJoypadPress(JOYKEY Key, int nPlayer)
{
	return (g_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//�W���C�p�b�h�̃g���K�[����
bool GetJoypadTrigger(JOYKEY Key, int nPlayer)
{
	return (g_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//�W���C�p�b�g�i�X�e�B�b�N�v���X�j����
D3DXVECTOR3 GetJoypadStick(JOYKEY_RIGHT_LEFT RightLeft, int nPlayer)
{
	switch (RightLeft)
	{
	case JOYKEY_LEFT_STICK:
		g_JoyStickPos[nPlayer] = D3DXVECTOR3(g_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -g_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		g_JoyStickPos[nPlayer] = D3DXVECTOR3(g_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -g_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return g_JoyStickPos[nPlayer];
}

//�W���C�p�b�g�i�g���K�[�y�_���j����
int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = g_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = g_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//�W���C�p�b�h�X�e�B�b�N�v���X�W����
bool GetJoypadStickPress(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key, int nPlayer)
{
	D3DXVECTOR3 pos = GetJoypadStick(RightLeft, nPlayer);	//���݂̌X���̎擾
	pos.y *= -1.0f;//Y�𕪂���₷�����邽�߂Ɂ{�|�𔽓]

	if (pos.y > 0.5f
		&& JOYKEY_STICK_UP == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& pos.y > 0.5f
		&& JOYKEY_STICK_UP_RIGHT == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& JOYKEY_STICK_RIGHT == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& pos.y < -0.5f
		&& JOYKEY_STICK_DOWN_RIGHT == Key)
	{
		return true;
	}
	else if (pos.y < -0.5f
		&& JOYKEY_STICK_DOWN == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& pos.y < -0.5f
		&& JOYKEY_STICK_DOWN_LEFT == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& JOYKEY_STICK_LEFT == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& pos.y > 0.5f
		&& JOYKEY_STICK_UP_LEFT == Key)
	{
		return true;
	}
	return false;
}

//�W���C�p�b�h�X�e�B�b�N�g���K�[�W����
bool GetJoypadStickTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key, int nPlayer)
{
	if (GetJoypadStickPress(RightLeft, Key, nPlayer)
		&& Key != g_OldJoyKeyStick[nPlayer][RightLeft])
	{
		g_OldJoyKeyStick[nPlayer][RightLeft] = Key;
		return true;
	}
	else if (GetJoypadStickPress(RightLeft, Key, nPlayer)
		&& Key == g_OldJoyKeyStick[nPlayer][RightLeft])
	{
		return false;
	}
	else if (!GetJoypadStickPress(RightLeft, Key, nPlayer)
		&& Key != g_OldJoyKeyStick[nPlayer][RightLeft])
	{
		return false;
	}

	g_OldJoyKeyStick[nPlayer][RightLeft] = JOYKEY_MAX;
	return false;
}

//�W���C�p�b�h�X�e�B�b�N�g���K�[�W�����̑S�v���C���[�̑Ώ�
bool GetJoypadStickAllTrigger(JOYKEY_RIGHT_LEFT RightLeft, JOYKEY Key)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (GetJoypadStickTrigger(RightLeft, Key, nCnt))
		{
			return true;
		}
	}
	return false;
}

//�W���C�p�b�h�g���K�[�̑S�v���C���[�̑Ώ�
bool GetJoypadAllTrigger(JOYKEY Key)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (GetJoypadTrigger(Key, nCnt))
		{
			return true;
		}
	}
	return false;
}

//�ړ��n�̃L�[�܂Ƃ߃v���X
bool GetMoveKeyPress(MOVE_KEY Key)
{
	if (Key == MOVE_KEY_UP)
	{
		if (GetJoypadStickPress(JOYKEY_LEFT_STICK, JOYKEY_STICK_UP, 0)
			|| GetJoypadStickPress(JOYKEY_RIGHT_STICK, JOYKEY_STICK_UP, 0)
			|| GetJoypadPress(JOYKEY_CROSS_UP, 0)
			|| GetKeyboardPress(DIK_W)
			|| GetKeyboardPress(DIK_UP))
		{
			return true;
		}
	}
	else if (Key == MOVE_KEY_DOWN)
	{
		if (GetJoypadStickPress(JOYKEY_LEFT_STICK, JOYKEY_STICK_DOWN, 0)
			|| GetJoypadStickPress(JOYKEY_RIGHT_STICK, JOYKEY_STICK_DOWN, 0)
			|| GetJoypadPress(JOYKEY_CROSS_DOWN, 0)
			|| GetKeyboardPress(DIK_S)
			|| GetKeyboardPress(DIK_DOWN))
		{
			return true;
		}
	}
	else if (Key == MOVE_KEY_LEFT)
	{
		if (GetJoypadStickPress(JOYKEY_LEFT_STICK, JOYKEY_STICK_LEFT, 0)
			|| GetJoypadStickPress(JOYKEY_RIGHT_STICK, JOYKEY_STICK_LEFT, 0)
			|| GetJoypadPress(JOYKEY_CROSS_LEFT, 0)
			|| GetKeyboardPress(DIK_A)
			|| GetKeyboardPress(DIK_LEFT))
		{
			return true;
		}
	}
	else if (Key == MOVE_KEY_RIGHT)
	{
		if (GetJoypadStickPress(JOYKEY_LEFT_STICK, JOYKEY_STICK_RIGHT, 0)
			|| GetJoypadStickPress(JOYKEY_RIGHT_STICK, JOYKEY_STICK_RIGHT, 0)
			|| GetJoypadPress(JOYKEY_CROSS_RIGHT, 0)
			|| GetKeyboardPress(DIK_D)
			|| GetKeyboardPress(DIK_RIGHT))
		{
			return true;
		}
	}

	return false;
}

//�@�\�n�̃L�[�܂Ƃ�
bool GetFunctionKeyTrigger(FUNCTION_KEY Key)
{
	if (Key == FUNCTION_KEY_DESISION)
	{
		if (GetJoypadPress(JOYKEY_A, 0) || GetJoypadPress(JOYKEY_B, 0)
			|| GetKeyboardPress(DIK_SPACE)
			|| GetKeyboardPress(DIK_RETURN))
		{
			if (g_OldFunctionKey != Key)
			{
				g_OldFunctionKey = Key;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else if (Key == FUNCTION_KEY_PAUSE)
	{
		if (GetJoypadPress(JOYKEY_START, 0)
			|| GetKeyboardPress(DIK_P))
		{
			if (g_OldFunctionKey != Key)
			{
				g_OldFunctionKey = Key;
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	g_OldFunctionKey = FUNCTION_KEY_MAX;
	return false;
}

//���C�g�̐F�I���L�[�̃v���X
bool GetLightKeyPress(LIGHT_KEY Key)
{
	if (Key == LIGHT_KEY_RED
		&& (GetMoveKeyPress(MOVE_KEY_RIGHT) || GetJoypadPress(JOYKEY_B, 0)))
	{
		return true;
	}
	else if (Key == LIGHT_KEY_GREEN
		&& (GetMoveKeyPress(MOVE_KEY_DOWN) || GetJoypadPress(JOYKEY_A, 0)))
	{
		return true;
	}
	else if (Key == LIGHT_KEY_BLUE
		&& (GetMoveKeyPress(MOVE_KEY_LEFT) || GetJoypadPress(JOYKEY_X, 0)))
	{
		return true;
	}
	else if (Key == LIGHT_KEY_YELLOW
		&& (GetMoveKeyPress(MOVE_KEY_UP) || GetJoypadPress(JOYKEY_Y, 0)))
	{
		return true;
	}
	return false;
}

//���C�g�̐F�I���L�[�̃g���K�[
bool GetLightKeyTrigger(LIGHT_KEY Key)
{
	if (g_nKeyCnt > 0)
	{
		return false;
	}

	if (!GetLightKeyPress(Key)
		&& g_OldLightKey != Key)
	{
		return false;
	}
	else if (GetLightKeyPress(Key)
		&& g_OldLightKey == Key)
	{
		return false;
	}
	else if (GetLightKeyPress(Key)
		&& g_OldLightKey == LIGHT_KEY_MAX)
	{
		g_OldLightKey = Key;
		return true;
	}
	else if (GetLightKeyPress(Key)
		&& g_OldLightKey != Key)
	{
		return false;
	}

	g_OldLightKey = LIGHT_KEY_MAX;							//�O��̃��C�g�̃L�[�̏��̃��Z�b�g
	return false;
}

//�ړ��n�̃L�[�܂Ƃ߃g���K�[
bool GetMoveKeyTrigger(MOVE_KEY Key)
{
	if (GetMoveKeyPress(Key)
		&& g_OldMoveKey == Key)
	{
		return false;
	}
	else if (GetMoveKeyPress(Key)
		&& g_OldMoveKey == MOVE_KEY_MAX)
	{
		g_OldMoveKey = Key;
		return true;
	}
	else if (GetMoveKeyPress(g_OldMoveKey))
	{
		return false;
	}

	g_OldMoveKey = MOVE_KEY_MAX;							//�O��̃��C�g�̃L�[�̏��̃��Z�b�g
	return false;
}