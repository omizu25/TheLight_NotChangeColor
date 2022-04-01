//**************************************************
// 
// Hackathon ( rectangle.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RECTANGLE_H_	//���̃}�N����`������ĂȂ�������
#define _RECTANGLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRectangle(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRectangle(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRectangle(void);

//--------------------------------------------------
// �ݒ�
// ����  : TEXTURE texture / �񋓌^ ���
//--------------------------------------------------
int SetRectangle(TEXTURE texture);

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
// ����  : LPDIRECT3DTEXTURE9 pTexture / �e�N�X�`��
//--------------------------------------------------
int SetRectangleWithTex(LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// �g���̂��~�߂�
// ����  : int nIdx / �C���f�b�N�X
//--------------------------------------------------
void StopUseRectangle(int nIdx);

//--------------------------------------------------
// �ʒu�̐ݒ�
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3 &pos / ���S�̈ʒu
// ����3  : D3DXVECTOR3 &size / �T�C�Y
//--------------------------------------------------
void SetPosRectangle(int nIdx, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

//--------------------------------------------------
// ��]����ʒu�̐ݒ�
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3 &pos / ���S�̈ʒu
// ����3  : float fRot / ����
// ����4  : float fWidth / ��
// ����5  : float fHeight / ����
//--------------------------------------------------
void SetRotationPosRectangle(int nIdx, const D3DXVECTOR3 &pos, float fRot, float fWidth, float fHeight);

//--------------------------------------------------
// �F�̐ݒ�
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : D3DXCOLOR &color / �F
//--------------------------------------------------
void SetColorRectangle(int nIdx, const D3DXCOLOR &color);

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR2 &texU / x = ���[, y = �E�[
// ����3  : D3DXVECTOR2 &texV / x = ��[, y = ���[
//--------------------------------------------------
void SetTexRectangle(int nIdx, const D3DXVECTOR2 &texU, const D3DXVECTOR2 &texV);

//--------------------------------------------------
// �`�悷�邩�ǂ���
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : bool bDraw / �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawRectangle(int nIdx, bool bDraw);

//--------------------------------------------------
// ���Z�������邩�ǂ���
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : bool bDraw / ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddRectangle(int nIdx, bool bAdd);

//--------------------------------------------------
// �e�N�X�`���̕ύX
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : TEXTURE texture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangle(int nIdx, TEXTURE texture);

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
// ����1  : int nIdx / �C���f�b�N�X
// ����2  : TEXTURE texture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangleWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// ���_�o�b�t�@�̎擾
// ����  : int nIdx / �C���f�b�N�X
// �Ԓl  : LPDIRECT3DVERTEXBUFFER9 / ���_�o�b�t�@
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle(int nIdx);

#endif // !_RECTANGLE_H_
