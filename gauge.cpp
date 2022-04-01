//**************************************************
//
// Hackathon ( gauge.cpp )
// Author  : katsuki mizuki
//
//**************************************************
//==================================================
// �C���N���[�h
//==================================================
#include "gauge.h"
#include "rectangle.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_GAUGE = 256;		// �Q�[�W�̍ő吔
const float	CHANGE_RATIO = 0.15f;	// �ύX�̊���

typedef struct
{
	D3DXVECTOR3	pos;			// �ʒu
	int			nIdx;			// ��`�̃C���f�b�N�X
	float		fWidth;			// ��
	float		fHeight;		// ����
	float		fWidthDest;		// �ړI�̕�
	float		fHeightDest;	// �ړI�̍���
	GAUGE		gauge;			// ���S�̈ʒu
	bool		bUse;			// �g�p���Ă��邩�ǂ���
}Gauge;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
Gauge	s_gauge[MAX_GAUGE];	// �Q�[�W�̏��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void PosEdge(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &size, GAUGE gauge);
void ChangeLength(float *fLength, float fLengthDest);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGauge(void)
{
	// �������̃N���A
	memset(s_gauge, 0, sizeof(s_gauge));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGauge(void)
{
	for (int i = 0; i < MAX_GAUGE; i++)
	{
		Gauge *pGauge = &s_gauge[i];

		if (!pGauge->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		// �g���̂��~�߂�
		StopUseRectangle(pGauge->nIdx);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGauge(void)
{
	for (int i = 0; i < MAX_GAUGE; i++)
	{
		Gauge *pGauge = &s_gauge[i];

		if (!pGauge->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		// �����̕ύX
		ChangeLength(&pGauge->fWidth, pGauge->fWidthDest);
		ChangeLength(&pGauge->fHeight, pGauge->fHeightDest);

		D3DXVECTOR3 size = D3DXVECTOR3(pGauge->fWidth, pGauge->fHeight, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �ʒu��[�ɂ��炷
		PosEdge(&pos, pGauge->pos, size, pGauge->gauge);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(pGauge->nIdx, pos, size);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGauge(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetGauge(const D3DXVECTOR3 &posStart, const D3DXCOLOR &col, float fWidth, float fHeight, GAUGE gauge)
{
	for (int i = 0; i < MAX_GAUGE; i++)
	{
		Gauge *pGauge = &s_gauge[i];

		if (pGauge->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pGauge->pos = posStart;
		pGauge->fWidth = fWidth;
		pGauge->fHeight = fHeight;
		pGauge->fWidthDest = fWidth;
		pGauge->fHeightDest = fHeight;
		pGauge->gauge = gauge;
		pGauge->bUse = true;

		// ��`�̐ݒ�
		pGauge->nIdx = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(fWidth, fHeight, 0.0f);
		D3DXVECTOR3 posOut = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �ʒu��[�ɂ��炷
		PosEdge(&posOut, posStart, size, gauge);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(pGauge->nIdx, posOut, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pGauge->nIdx, col);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void ChangeGauge(int nIdx, float fWidth, float fHeight)
{
	assert(nIdx >= 0 && nIdx < MAX_GAUGE);

	Gauge *pGauge = &s_gauge[nIdx];

	if (!pGauge->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pGauge->fWidthDest = fWidth;
	pGauge->fHeightDest = fHeight;
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void SetSizeGauge(int nIdx, float fWidth, float fHeight)
{
	assert(nIdx >= 0 && nIdx < MAX_GAUGE);

	Gauge *pGauge = &s_gauge[nIdx];

	if (!pGauge->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pGauge->fWidth = fWidth;
	pGauge->fHeight = fHeight;
	pGauge->fWidthDest = fWidth;
	pGauge->fHeightDest = fHeight;
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void SetColorGauge(int nIdx, const D3DXCOLOR &color)
{
	assert(nIdx >= 0 && nIdx < MAX_GAUGE);

	Gauge *pGauge = &s_gauge[nIdx];

	if (!pGauge->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	// ��`�̐F�̐ݒ�
	SetColorRectangle(pGauge->nIdx, color);
}

namespace
{
//--------------------------------------------------
// �ʒu��[�ɂ��炷
//--------------------------------------------------
void PosEdge(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &size, GAUGE gauge)
{
	switch (gauge)
	{
	case GAUGE_TOP:		// ��
		*pPosOut = D3DXVECTOR3(posStart.x, posStart.y + (size.y * 0.5f), 0.0f);
		break;

	case GAUGE_BOTTOM:	// ��
		*pPosOut = D3DXVECTOR3(posStart.x, posStart.y - (size.y * 0.5f), 0.0f);
		break;

	case GAUGE_LEFT:	// ��
		*pPosOut = D3DXVECTOR3(posStart.x + (size.x * 0.5f), posStart.y, 0.0f);
		break;

	case GAUGE_RIGHT:	// �E
		*pPosOut = D3DXVECTOR3(posStart.x - (size.x * 0.5f), posStart.y, 0.0f);
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void ChangeLength(float *fLength, float fLengthDest)
{
	if (*fLength == fLengthDest)
	{// �ړI�̒����ƌ��݂̒���������
		return;
	}

	float fDiff = fLengthDest - *fLength;
	float fChange = fDiff * CHANGE_RATIO;

	if ((fChange <= CHANGE_RATIO) && (fChange >= -CHANGE_RATIO))
	{// �ύX�l�������l�ȉ�
		*fLength = fLengthDest;
	}
	else
	{// �ύX�l�������l���傫
		*fLength += fChange;
	}
}
}// namespace�͂����܂�
