//**************************************************
// 
// Hackathon ( cursor.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "input.h"
#include "cursor.h"
#include "fade.h"
#include "color.h"
#include "rectangle.h"
#include "menu.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_CURSOR = 16;	// �J�[�\���̍ő吔
const float	ROT_SPEED = -0.15f;	// ��]���x

/*�� ���j���[ ��*/
typedef struct
{
	D3DXVECTOR3	pos;		// �ʒu
	int			nNumUse;	// �g�p��
	int			nIdx;		// ��`�̃C���f�b�N�X
	float		fRot;		// ����
	float		fTop;		// ��[
	float		fWidth;		// ��
	float		fHeight;	// ����
	float		fInterval;	// �I�����̊Ԋu
	bool		bRotation;	// ��]���邩�ǂ���
	bool		bDraw;		// �`�悷�邩�ǂ���
	bool		bUse;		// �g�p���Ă��邩�ǂ���
}Cursor;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Cursor	s_aCursor[MAX_CURSOR];	// �J�[�\���̏��
}// namespace�͂����܂�


//--------------------------------------------------
// ������
//--------------------------------------------------
void InitCursor(void)
{
	// �������̃N���A
	memset(s_aCursor, 0, sizeof(s_aCursor));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitCursor(void)
{
	for (int i = 0; i < MAX_CURSOR; i++)
	{
		Cursor *pCursor = &s_aCursor[i];

		if (!pCursor->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		// �g���̂��~�߂�
		StopUseRectangle(pCursor->nIdx);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateCursor(void)
{
	for (int i = 0; i < MAX_CURSOR; i++)
	{
		Cursor *pCursor = &s_aCursor[i];

		if (!pCursor->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		if (!pCursor->bRotation)
		{// ��]���Ȃ�
			continue;
		}

		/*�� ��]���� ��*/

		pCursor->fRot += ROT_SPEED;

		// ��`�̉�]����ʒu�̐ݒ�
		SetRotationPosRectangle(pCursor->nIdx, pCursor->pos, pCursor->fRot, pCursor->fWidth, pCursor->fHeight);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawCursor(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetCursor(const CursorArgument &cursor)
{
	assert(cursor.nNumUse >= 0 && cursor.nNumUse < MAX_CURSOR);

	for (int i = 0; i < MAX_CURSOR; i++)
	{
		Cursor *pCursor = &s_aCursor[i];

		if (pCursor->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pCursor->nNumUse = cursor.nNumUse;
		pCursor->fRot = 0.0f;
		pCursor->fInterval = (cursor.fBottom - cursor.fTop) / (cursor.nNumUse + 1);
		pCursor->pos = D3DXVECTOR3(cursor.fPosX, cursor.fTop + (pCursor->fInterval * (cursor.nSelect + 1)), 0.0f);
		pCursor->fWidth = cursor.fWidth;
		pCursor->fHeight = cursor.fHeight;
		pCursor->fTop = cursor.fTop;
		pCursor->bRotation = cursor.bRotation;
		pCursor->bDraw = true;
		pCursor->bUse = true;

		// ��`�̐ݒ�
		pCursor->nIdx = SetRectangle(cursor.texture);

		// ��`�̉�]����ʒu�̐ݒ�
		SetRotationPosRectangle(pCursor->nIdx, pCursor->pos, pCursor->fRot, cursor.fWidth, cursor.fHeight);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pCursor->nIdx, GetColor(COLOR_WHITE));

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �ʒu�̕ύX
//--------------------------------------------------
void ChangePosCursor(int nIdx, int nSelect)
{
	assert(nIdx >= 0 && nIdx < MAX_CURSOR);
	assert(nSelect >= 0 && nSelect < MAX_OPTION);

	Cursor *pCursor = &s_aCursor[nIdx];

	if (!pCursor->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pCursor->pos = D3DXVECTOR3(pCursor->pos.x, pCursor->fTop + (pCursor->fInterval * (nSelect + 1)), 0.0f);

	// ��`�̉�]����ʒu�̐ݒ�
	SetRotationPosRectangle(pCursor->nIdx, pCursor->pos, pCursor->fRot, pCursor->fWidth, pCursor->fHeight);
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void ResetCursor(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_CURSOR);

	Cursor *pCursor = &s_aCursor[nIdx];

	// �g���̂��~�߂�
	StopUseRectangle(pCursor->nIdx);
	
	pCursor->bUse = false;
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawCursor(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_CURSOR);

	Cursor *pCursor = &s_aCursor[nIdx];

	if (!pCursor->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	// ��`�̕`�悷�邩�ǂ���
	SetDrawRectangle(pCursor->nIdx, bDraw);
	
	pCursor->bDraw = bDraw;
}