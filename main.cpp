//**************************************************
// 
// Hackathon ( main.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "mode.h"
#include "sound.h"
#include "game.h"

#include <stdio.h>

//==================================================
// ��`
//==================================================
namespace
{
const char	*CLASS_NAME = "windowClass";		// �E�C���h�E�N���X�̖��O
const char	*WINDOW_NAME = "���������l���_";	// �E�C���h�E�̖��O (�L���v�V�����ɕ\��)
}

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3D9			s_pD3D = NULL;			// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9	s_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT			s_pFont = NULL;			// �t�H���g�ւ̃|�C���^
int					s_nCountFPS = 0;		// FPS�J�E���^
bool				s_bDebug = true;		// �f�o�b�O�\�������邩 [�\��  : true ��\��  : false]
}// namespace�͂����܂�

//==================================================
// �v���g�^�C�v�錾
//==================================================
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
static void Uninit(void);
static void Update(void);
static void Draw(void);
static void DrawDebug(void);

//--------------------------------------------------
// main�֐�
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{// �E�C���h�E�N���X�̍\����
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�C���h�E�̃X�^�C��
		WindowProc,							// �E�C���h�E�v���V�[�W��
		0,									// �O�ɂ��� (�ʏ�͎g�p���Ȃ�)
		0,									// �O�ɂ��� (�ʏ�͎g�p���Ȃ�)
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	HWND hWnd;											// �E�C���h�E�n���h�� (���ʎq)
	MSG msg;											// ���b�Z�[�W���i�[����ϐ�
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};	// ��ʃT�C�Y�̍\����
	DWORD dwCurrentTime;								// ���ݎ���
	DWORD dwExecLastTime;								// �Ō�ɏ�����������
	DWORD dwFrameCount;									// �t���[���J�E���g
	DWORD dwFPSLastTime;								// �Ō��FPS���v�Z��������

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�C���h�E���쐬
	hWnd = CreateWindowEx(
		0,							// �g���E�C���h�E�X�^�C��
		CLASS_NAME,					// �E�C���h�E�X�^�C���̖��O
		WINDOW_NAME,				// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�C���h�E�̍���X���W
		CW_USEDEFAULT,				// �@�@�V�@�@�̍���Y���W
		(rect.right - rect.left),	// �@�@�V�@�@�̕�
		(rect.bottom - rect.top),	// �@�@�V�@�@�̍���
		NULL,						// �e�E�C���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�C���h�E�쐬�f�[�^

	// ������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// �����������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;				// ����������
	dwExecLastTime = timeGetTime();	// ���ݎ������擾 (�ۑ�)
	dwFrameCount = 0;				// ����������
	dwFPSLastTime = timeGetTime();	// ���ݎ������擾 (�ۑ�)

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈���X�V

	while (1)
	{// ���b�Z�[�W���[�v
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	// ���z���b�Z�[�W�𕶎��̃��b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();	// ���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS�̌v�Z
				s_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	// FPS���v������������ۑ�

				dwFrameCount = 0;				// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60����1�b�o��
				dwExecLastTime = dwCurrentTime;	// �����J�n�̎���[���ݎ���]��ۑ�

				// �X�V
				Update();

				// �`��
				Draw();

				dwFrameCount++;	// �t���[���J�E���g�����Z
			}
		}
	}
	
	// �I��
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//--------------------------------------------------
// �E�C���h�E�v���V�[�W��
//--------------------------------------------------
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�C���h�E�j���̃��b�Z�[�W
		// WM_QOIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]�L�[�������ꂽ
			// �E�C���h�E��j������ (WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// �K��̏�����Ԃ�
}

//--------------------------------------------------
// ������
//--------------------------------------------------
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (s_pD3D == NULL)
	{// �J���Ȃ��������p�̊m�F
		return E_FAIL;
	}

	if (FAILED(s_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{// ���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A)
	if (FAILED(s_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&s_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(s_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&s_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(s_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&s_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	s_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	s_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	s_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	s_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �摜�����������Ă��Y��ɂ���
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �摜��傫�����Ă��Y��ɂ���
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`����U�̌J��Ԃ�����ݒ�
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`����V�̌J��Ԃ�����ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �|���S���ƃe�N�X�`���̃����܂���
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �P�ڂ̐F�̓e�N�X�`���̐F
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�ڂ̐F�͌��݂̐F

	// �f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(
		s_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &s_pFont);

	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �T�E���h�̏�����
	InitSound(hWnd);

	// �t�F�[�h�̏�����
	InitFade();

	// ���[�h�̏�����
	InitMode();

	// ���[�h�̕ύX
	ChangeMode(MODE_TITLE);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
static void Uninit(void)
{
	// �T�E���h�̏I��
	UninitSound();

	// ���͏����̏I��
	UninitInput();

	// ���[�h�̏I��
	UninitMode();

	if (s_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̉��
		s_pFont->Release();
		s_pFont = NULL;
	}

	if (s_pD3DDevice != NULL)
	{// Direct3D�f�o�C�X�̉��
		s_pD3DDevice->Release();
		s_pD3DDevice = NULL;
	}

	if (s_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̉��
		s_pD3D->Release();
		s_pD3D = NULL;
	}
}

//--------------------------------------------------
// �X�V
//-------------------------------------------------- 
static void Update(void)
{
	// ���͏����̍X�V
	UpdateInput();

	// ���[�h�̍X�V
	UpdateMode();

	// �t�F�[�h�̍X�V
	UpdateFade();

	// ���[�h�̐ݒ�
	SetMode();

 #ifdef  _DEBUG

	if (GetKeyboardTrigger(DIK_F1) || GetJoypadTrigger(JOYKEY_BACK,0))
	{// F1�L�[�������ꂽ
		s_bDebug = !s_bDebug;
	}

 #endif //  _DEBUG

}

//--------------------------------------------------
// �`��
//--------------------------------------------------
static void Draw(void)
{
	// ��ʃN���A(�o�b�O�o�b�t�@��Z�o�b�t�@�̃N���A)
	s_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// �`��J�n
	if (SUCCEEDED(s_pD3DDevice->BeginScene()))
	{// �`��J�n�����������ꍇ
		// ���[�h�̕`��
		DrawMode();

		// �t�F�[�h�̕`��
		DrawFade();

 #ifdef  _DEBUG

		if (s_bDebug)
		{// �\������H
			// �f�o�b�O�̕\��
			DrawDebug();
		}

 #endif //  _DEBUG

		// �`��I��
		s_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	s_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//--------------------------------------------------
// �f�o�C�X�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return s_pD3DDevice;
}

//--------------------------------------------------
// �f�o�b�O�̕\��
//--------------------------------------------------
static void DrawDebug(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[4096];
	int nLength = 0;

	/* ��������̑���� */

	sprintf(&aStr[nLength], "FPS  : %3d\n\n", s_nCountFPS);
	nLength = (int)strlen(&aStr[0]);

	sprintf(&aStr[nLength], "%3d\n\n", GetGameState());
	nLength = (int)strlen(&aStr[0]);

	// �e�L�X�g�̕`��
	s_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.25f, 0.75f, 1.0f, 1.0f));
}
