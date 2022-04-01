//=========================================
// 
// �p�[�e�B�N���̃w�b�_�[�t�@�C��
// Author YudaKaito
// 
//=========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//-----------------------------------------
// include
//-----------------------------------------

//------------------------------------
// ����ʒu�̗񋓌^�̒�`
//------------------------------------
typedef enum
{
	EFFECT_TYPE_000 = 0,		// �v���C���[�̒���
	EFFECT_TYPE_001,			// �v���C���[�̈ړ�
	EFFECT_TYPE_002,			// �v���C���[�̈ړ�
	EFFECT_TYPE_003,			// �v���C���[�̈ړ�
	MAX_EFFECT_TYPE
}EFFECT_TYPE;

//-----------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, EFFECT_TYPE type, D3DXCOLOR col);

#endif // _EFFECT_H_
