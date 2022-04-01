//**************************************************
//
// Hackathon ( select.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SELECT_H_	//���̃}�N����`������ĂȂ�������
#define _SELECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "texture.h"
#include "menu.h"
#include "color.h"

//==================================================
// �\����
//==================================================

/*�� ���j���[�̈��� ��*/
typedef struct
{
	TEXTURE	texture[MAX_OPTION];	// �e�N�X�`��
	int		nNumUse;				// �g�p��
	float	fLeft;					// ���[
	float	fRight;					// �E�[
	float	fTop;					// ��[
	float	fBottom;				// ���[
	float	fWidth;					// �I�����̕�
	float	fHeight;				// �I�����̍���
	bool	bSort;					// ���ו� [ true : �c false : �� ]
}SelectArgument;

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitSelect(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitSelect(void);

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateSelect(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawSelect(void);

//--------------------------------------------------
// �ݒ�
// ����1  : SelectArgument &menu / �\���� ���j���[���
// �Ԓl   ; int / ���Ԗڂ��̃C���f�b�N�X
//--------------------------------------------------
int SetSelect(const SelectArgument &menu);

//--------------------------------------------------
// �Z���N�g�̐F�̐ݒ�
// ����1  : int nIdxSelect / �Z���N�g�̃C���f�b�N�X
// ����2  : int nIdxOption / �I�����̃C���f�b�N�X
// ����3  : COLOR color / �F
//--------------------------------------------------
void SetColorSelect(int nIdxSelect, int nIdxOption, COLOR color);

//--------------------------------------------------
// �Z���N�g�̃e�N�X�`���̕ύX
// ����1  : int nIdxSelect / �Z���N�g�̃C���f�b�N�X
// ����2  : int nIdxOption / �I�����̃C���f�b�N�X
// ����3  : TEXTURE texture / �e�N�X�`��
//--------------------------------------------------
void ChangeTextuteSelect(int nIdxSelect, int nIdxOption, TEXTURE texture);

//--------------------------------------------------
// ���j���[�̃��Z�b�g
// ����  : int nIdx / �Z���N�g�̃C���f�b�N�X
//--------------------------------------------------
void ResetSelect(int nIdx);

//--------------------------------------------------
// �`�悷�邩�ǂ���
// ����1  : int nIdxSelect / �Z���N�g�̃C���f�b�N�X
// ����2  : int nIdxOption / �I�����̃C���f�b�N�X
// ����3  : bool bDraw / �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawSelect(int nIdxSelect, int nIdxOption, bool bDraw);

//--------------------------------------------------
// �I�����̈ʒu���擾
// ����1  : int nIdxSelect / �Z���N�g�̃C���f�b�N�X
// ����2  : int nIdxOption / �I�����̃C���f�b�N�X
// �Ԓl  : D3DXVECTOR3 / �I�����̈ʒu
//--------------------------------------------------
D3DXVECTOR3 GetPosSelect(int nIdxSelect, int nIdxOption);

//--------------------------------------------------
// �I�����̐F���擾
// ����1  : int nIdxSelect / �Z���N�g�̃C���f�b�N�X
// ����2  : int nIdxOption / �I�����̃C���f�b�N�X
// �Ԓl  : D3DXCOLOR / �I�����̐F
//--------------------------------------------------
D3DXCOLOR GetColSelect(int nIdxSelect, int nIdxOption);

#endif // !_SELECT_H_
