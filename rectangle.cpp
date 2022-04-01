//**************************************************
// 
// Hackathon ( rectangle.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle.h"
#include "color.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_RECTANGLE = 1024;	// ��`�̍ő吔
const int	NUM_VERTEX = 4;			// ���_�̐�
const int	NUM_POLYGON = 2;		// �|���S���̐�

typedef struct
{
	LPDIRECT3DTEXTURE9		pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;	// ���_�o�b�t�@
	bool					bUse;		// �g�p���Ă��邩�ǂ���
	bool					bDraw;		// �`�悷�邩�ǂ���
	bool					bAdd;		// ���Z�������邩�ǂ���
}MyRectangle;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
MyRectangle	s_aRectangle[MAX_RECTANGLE];	// ��`�̏��
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRectangle(void)
{
	// �������̃N���A
	memset(s_aRectangle, 0, sizeof(s_aRectangle));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRectangle(void)
{
	for (int i = 0; i < MAX_RECTANGLE; i++)
	{
		MyRectangle *pRectangle = &s_aRectangle[i];

		if (pRectangle->pVtxBuff != NULL)
		{// ���_�o�b�t�@�̉��
			pRectangle->pVtxBuff->Release();
			pRectangle->pVtxBuff = NULL;
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRectangle(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_RECTANGLE; i++)
	{
		MyRectangle *pRectangle = &s_aRectangle[i];

		if (!pRectangle->bUse || !pRectangle->bDraw)
		{// �g�p���Ă��Ȃ��A�`�悷�邵�Ȃ�
			continue;
		}

		/*�� �g�p���Ă���A�`�悷�� ��*/

		if (pRectangle->bAdd)
		{// ���Z��������
			// �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, pRectangle->pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pRectangle->pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			0,							// �`�悷��ŏ��̒��_�C���f�b�N�X
			NUM_POLYGON);				// �v���~�e�B�u(�|���S��)��

		// �e�N�X�`���̉���
		pDevice->SetTexture(0, NULL);

		if (pRectangle->bAdd)
		{// ���Z��������
			// �����_�[�X�e�[�g�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetRectangle(TEXTURE texture)
{
	// �ݒ� [ �e�N�X�`������ ]
	return SetRectangleWithTex(GetTexture(texture));
}

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
//--------------------------------------------------
int SetRectangleWithTex(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int i = 0; i < MAX_RECTANGLE; i++)
	{
		MyRectangle *pRectangle = &s_aRectangle[i];

		if (pRectangle->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pRectangle->pTexture = pTexture;
		pRectangle->bUse = true;
		pRectangle->bDraw = true;
		pRectangle->bAdd = false;

		// ���_�o�b�t�@�̐���
		GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_2D) * NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pRectangle->pVtxBuff,
			NULL);

		VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

		// ���_�������b�N���A���_���ւ̃|�C���^���擾
		pRectangle->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�o�b�t�@���A�����b�N����
		pRectangle->pVtxBuff->Unlock();

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �ʒu�̐ݒ�
		SetPosRectangle(i, pos, size);

		//�F�̐ݒ�
		SetColorRectangle(i, GetColor(COLOR_WHITE));

		D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
		D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		SetTexRectangle(i, texU, texV);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �g�p����߂�
//--------------------------------------------------
void StopUseRectangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	pRectangle->bUse = false;

	if (pRectangle->pVtxBuff != NULL)
	{// ���_�o�b�t�@�̉��
		pRectangle->pVtxBuff->Release();
		pRectangle->pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void SetPosRectangle(int nIdx, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = size.x * 0.5f;
	float fHeight = size.y * 0.5f;

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(+fWidth, -fHeight, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth, +fHeight, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(+fWidth, +fHeight, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// ��]����ʒu�̐ݒ�
//--------------------------------------------------
void SetRotationPosRectangle(int nIdx, const D3DXVECTOR3 &pos, float fRot, float fWidth, float fHeight)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXMATRIX mtx, mtxTrans;

	// ��]�̔��f
	D3DXMatrixRotationZ(&mtx, -fRot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	D3DXVECTOR3 pVtxpos[NUM_VERTEX];

	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;

	pVtxpos[0] = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0.0f);
	pVtxpos[1] = D3DXVECTOR3(+fHalfWidth, -fHalfHeight, 0.0f);
	pVtxpos[2] = D3DXVECTOR3(-fHalfWidth, +fHalfHeight, 0.0f);
	pVtxpos[3] = D3DXVECTOR3(+fHalfWidth, +fHalfHeight, 0.0f);
	
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxpos[i], &mtx);
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void SetColorRectangle(int nIdx, const D3DXCOLOR &color)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void SetTexRectangle(int nIdx, const D3DXVECTOR2 &texU, const D3DXVECTOR2 &texV)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(texU.x, texV.x);
	pVtx[1].tex = D3DXVECTOR2(texU.y, texV.x);
	pVtx[2].tex = D3DXVECTOR2(texU.x, texV.y);
	pVtx[3].tex = D3DXVECTOR2(texU.y, texV.y);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawRectangle(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle->bDraw = bDraw;
}

//--------------------------------------------------
// ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddRectangle(int nIdx, bool bAdd)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle->bAdd = bAdd;
}

//--------------------------------------------------
// �e�N�X�`���̕ύX
//--------------------------------------------------
void ChangeTextureRectangle(int nIdx, TEXTURE texture)
{
	// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
	ChangeTextureRectangleWithTex(nIdx, GetTexture(texture));
}

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
//--------------------------------------------------
void ChangeTextureRectangleWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle->pTexture = pTexture;
}

//--------------------------------------------------
// ���_�o�b�t�@���擾
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// �g�p���Ă��Ȃ�
		return NULL;
	}

	/*�� �g�p���Ă��� ��*/

	return s_aRectangle[nIdx].pVtxBuff;
}
