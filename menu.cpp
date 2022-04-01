//**************************************************
// 
// Hackathon ( menu.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "input.h"
#include "menu.h"
#include "fade.h"
#include "color.h"
#include "rectangle.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_MENU = 16;					// ���j���[�̍ő吔
const float	NORMAL_CHANGE_SPEED = 0.01f;	// �ʏ펞�̕ύX���x
const float	DECISION_CHANGE_SPEED = 0.1f;	// ���莞�̕ύX���x
const float	MIN_ALPHA = 0.5f;				// ���l�̍ŏ��l

/*�� �I���� ��*/
typedef struct
{
	D3DXVECTOR3	pos;		// �ʒu
	D3DXCOLOR	col;		// �F
	int			nIdx;		// ��`�̃C���f�b�N�X
	float		fWidth;		// ��
	float		fHeight;	// ����
}Option;

/*�� ���j���[ ��*/
typedef struct
{
	D3DXVECTOR3	pos;				// �ʒu
	D3DXCOLOR	colStart;			// �n�܂�̐F
	D3DXCOLOR	colEnd;				// �I���̐F
	D3DXCOLOR	colDefault;			// �I�΂�ĂȂ��I�����̐F
	Option		Option[MAX_OPTION];	// �I�����̏��
	int			nNumUse;			// �g�p��
	int			nIdx;				// ��`�̃C���f�b�N�X
	float		fWidth;				// ��
	float		fHeight;			// ����
	float		fInterval;			// �I�����̊Ԋu
	float		fChangeSpeed;		// �ύX���x
	bool		bFrame;				// �g�����邩�ǂ��� [ true : ���� false : ����Ȃ� ]
	bool		bDraw;				// �`�悷�邩�ǂ���
	bool		bUse;				// �g�p���Ă��邩�ǂ���
}Menu;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Menu	s_aMenu[MAX_MENU];	// ���j���[�̏��
int		s_nIdxMenu;			// �I�΂�Ă��郁�j���[�̔ԍ�
int		s_nIdxOption;		// �I�΂�Ă���I�����̔ԍ�
int		s_nTime;			// ���l�ύX�p�̎���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void ChangeColor(Menu *pMenu);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitMenu(void)
{
	s_nIdxMenu = 0;
	s_nIdxOption = 0;
	s_nTime = 0;

	// �������̃N���A
	memset(s_aMenu, 0, sizeof(s_aMenu));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitMenu(void)
{
	for (int i = 0; i < MAX_MENU; i++)
	{
		Menu *pMenu = &s_aMenu[i];

		if (!pMenu->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		if (pMenu->bFrame)
		{// �g���g���Ă���
			// �g���̂��~�߂�
			StopUseRectangle(pMenu->nIdx);
		}

		for (int j = 0; j < pMenu->nNumUse; j++)
		{
			Option *pOption = &pMenu->Option[j];

			// �g���̂��~�߂�
			StopUseRectangle(pOption->nIdx);
		}
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateMenu(void)
{
	Menu *pMenu = &s_aMenu[s_nIdxMenu];

	if (!pMenu->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}
	
	// �F�̕ύX
	ChangeColor(pMenu);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawMenu(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetMenu(const MenuArgument &menu, const FrameArgument &Frame)
{
	assert(menu.nNumUse >= 0 && menu.nNumUse < MAX_OPTION);
	
	for (int i = 0; i < MAX_MENU; i++)
	{
		Menu *pMenu = &s_aMenu[i];

		if (pMenu->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		float fPosX = menu.fLeft + ((menu.fRight - menu.fLeft) * 0.5f);
		float fPosY = menu.fTop + ((menu.fBottom - menu.fTop) * 0.5f);

		pMenu->pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		pMenu->colStart = GetColor(COLOR_WHITE);
		pMenu->colEnd = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pMenu->colDefault = GetColor(COLOR_WHITE);
		pMenu->nNumUse = menu.nNumUse;
		pMenu->fWidth = menu.fRight - menu.fLeft;
		pMenu->fHeight = menu.fBottom - menu.fTop;
		pMenu->fChangeSpeed = NORMAL_CHANGE_SPEED;
		pMenu->bFrame = Frame.bUse;
		pMenu->bDraw = true;
		pMenu->bUse = true;

		if (menu.bSort)
		{// �c
			pMenu->fInterval = pMenu->fHeight / (menu.nNumUse + 1);
		}
		else
		{// ��
			pMenu->fInterval = pMenu->fWidth / (menu.nNumUse + 1);
		}

		s_nIdxMenu = i;
		s_nIdxOption = 0;

		if (Frame.bUse)
		{// �g������
			// ��`�̐ݒ�
			pMenu->nIdx = SetRectangle(Frame.texture);

			fPosX = menu.fLeft + (pMenu->fWidth * 0.5f);
			fPosY = menu.fTop + (pMenu->fHeight * 0.5f);
			D3DXVECTOR3 pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pMenu->fWidth, pMenu->fHeight, 0.0f);

			// ��`�̈ʒu�̐ݒ�
			SetPosRectangle(pMenu->nIdx, pos, size);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(pMenu->nIdx, Frame.col);
		}

		for (int j = 0; j < pMenu->nNumUse; j++)
		{
			Option *pOption = &pMenu->Option[j];

			if (menu.bSort)
			{// �c
				pOption->pos = D3DXVECTOR3(pMenu->pos.x, menu.fTop + (pMenu->fInterval * (j + 1)), 0.0f);
			}
			else
			{// ��
				pOption->pos = D3DXVECTOR3(menu.fLeft + (pMenu->fInterval * (j + 1)), pMenu->pos.y, 0.0f);
			}

			pOption->col = GetColor(COLOR_WHITE);
			pOption->fWidth = menu.fWidth;
			pOption->fHeight = menu.fHeight;

			// ��`�̐ݒ�
			pOption->nIdx = SetRectangle(menu.texture[j]);

			D3DXVECTOR3 size = D3DXVECTOR3(menu.fWidth, menu.fHeight, 0.0f);

			// ��`�̈ʒu�̐ݒ�
			SetPosRectangle(pOption->nIdx, pOption->pos, size);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(pOption->nIdx, pOption->col);
		}

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �I�����̐F�̐ݒ�
//--------------------------------------------------
void SetColorOption(int nIdx, const D3DXCOLOR &colStart, const D3DXCOLOR &colEnd)
{
	assert(nIdx >= 0 && nIdx < MAX_MENU);

	Menu *pMenu = &s_aMenu[nIdx];

	if (!pMenu->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pMenu->colStart = colStart;
	pMenu->colEnd = colEnd;
}

//--------------------------------------------------
// �I�΂�Ă��Ȃ��I�����̐F�̐ݒ�
//--------------------------------------------------
void SetColorDefaultOption(int nIdx, const D3DXCOLOR &colDefault)
{
	assert(nIdx >= 0 && nIdx < MAX_MENU);

	Menu *pMenu = &s_aMenu[nIdx];

	if (!pMenu->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pMenu->colDefault = colDefault;

	// �I�����̐F�̏�����
	InitColorOption();
}

//--------------------------------------------------
// �I�����̐F�̏�����
//--------------------------------------------------
void InitColorOption(void)
{
	Menu *pMenu = &s_aMenu[s_nIdxMenu];

	for (int i = 0; i < pMenu->nNumUse; i++)
	{
		Option *pOption = &pMenu->Option[i];

		pOption->col = pMenu->colDefault;

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pOption->nIdx, pOption->col);
	}
}

//--------------------------------------------------
// �I�����̕ύX
//--------------------------------------------------
void ChangeOption(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_OPTION);

	s_nIdxOption = nIdx;
	s_nTime = 0;
}

//--------------------------------------------------
// �I�����̌���
//--------------------------------------------------
void DecisionOption(void)
{
	s_aMenu[s_nIdxMenu].fChangeSpeed = DECISION_CHANGE_SPEED;
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void ResetMenu(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_MENU);

	s_nIdxMenu = 0;
	s_nIdxOption = 0;
	s_nTime = 0;
	
	Menu *pMenu = &s_aMenu[nIdx];

	if (!pMenu->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	if (pMenu->bFrame)
	{// �g���g���Ă���
		// �g���̂��~�߂�
		StopUseRectangle(pMenu->nIdx);
	}

	for (int i = 0; i < pMenu->nNumUse; i++)
	{
		Option *pOption = &pMenu->Option[i];

		// �g���̂��~�߂�
		StopUseRectangle(pOption->nIdx);
	}

	pMenu->bUse = false;
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawMenu(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_MENU);

	Menu *pMenu = &s_aMenu[nIdx];

	if (!pMenu->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	if (pMenu->bFrame)
	{// �g���g���Ă���
		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pMenu->nIdx, bDraw);
	}

	for (int i = 0; i < pMenu->nNumUse; i++)
	{
		Option *pOption = &pMenu->Option[i];

		// ��`�̕`�悷�邩�ǂ���
		SetDrawRectangle(pOption->nIdx, bDraw);

		pOption->col = GetColor(COLOR_WHITE);
	}

	pMenu->bDraw = bDraw;

	pMenu->fChangeSpeed = NORMAL_CHANGE_SPEED;
	s_nIdxOption = 0;
	s_nTime = 0;
}

namespace
{
//--------------------------------------------------
// �F�̕ύX
//--------------------------------------------------
void ChangeColor(Menu *pMenu)
{
	s_nTime++;

	Option *pOption = &pMenu->Option[s_nIdxOption];

	float fCurve = CosCurve(s_nTime, pMenu->fChangeSpeed);
	pOption->col.r = Curve(fCurve, pMenu->colStart.r, pMenu->colEnd.r);
	pOption->col.g = Curve(fCurve, pMenu->colStart.g, pMenu->colEnd.g);
	pOption->col.b = Curve(fCurve, pMenu->colStart.b, pMenu->colEnd.b);
	pOption->col.a = Curve(fCurve, pMenu->colStart.a, pMenu->colEnd.a);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(pOption->nIdx, pOption->col);
}
}// namespace�͂����܂�
