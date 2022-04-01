//**************************************************
//
// Hackathon ( ranking.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "ranking.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "input.h"
#include "utility.h"
#include "score.h"
#include <stdio.h>
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_RANKING = 1;						// �����L���O�̍ő吔
const float	RANKING_WIDTH = 70.0f;					// �����L���O�̕�
const float	RANKING_HEIGHT = 150.0f;				// �����L���O�̍���
const char *TEXT_NAME = "data/TEXT/Ranking.txt";	// �e�L�X�g��

}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdxRanking;	// ��`�̃C���f�b�N�X
int	s_nRanking;		// �����L���O
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRanking(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.68f, SCREEN_HEIGHT * 0.5f, 0.0f);

	// ���̐ݒ�
	s_nIdxRanking = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nRanking, DigitNumber(s_nRanking), false);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRanking(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxRanking);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateRanking(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRanking(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetRanking(void)
{
	int aSave[MAX_RANKING + 1];

	aSave[0] = s_nRanking;

	// �X�R�A�̎擾
	aSave[MAX_RANKING] = GetScore();

	for (int i = 0; i < MAX_RANKING; i++)
	{
		int nMax = aSave[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax < aSave[j])
			{//���肪�傫����������
				nMax = aSave[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (nMax == aSave[j])
			{//�ő�l��T���Č��
				aSave[j] = aSave[i];
				aSave[i] = nMax;
				break;
			}
		}
	}

	s_nRanking = aSave[0];

	// ���̕ύX
	s_nIdxRanking = ChangeNumber(s_nIdxRanking, s_nRanking);
}

//--------------------------------------------------
// ���[�h
//--------------------------------------------------
void LoadRanking(void)
{
	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(TEXT_NAME, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &s_nRanking);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);

		s_nRanking = 0;
	}
}

//--------------------------------------------------
// �Z�[�u
//--------------------------------------------------
void SaveRanking(void)
{
	FILE *pFile = NULL;	// �t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(TEXT_NAME, "w");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fprintf(pFile, "%d\n\n", s_nRanking);
	
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}
