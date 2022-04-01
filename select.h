//**************************************************
//
// Hackathon ( select.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SELECT_H_	//このマクロ定義がされてなかったら
#define _SELECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "menu.h"
#include "color.h"

//==================================================
// 構造体
//==================================================

/*↓ メニューの引数 ↓*/
typedef struct
{
	TEXTURE	texture[MAX_OPTION];	// テクスチャ
	int		nNumUse;				// 使用数
	float	fLeft;					// 左端
	float	fRight;					// 右端
	float	fTop;					// 上端
	float	fBottom;				// 下端
	float	fWidth;					// 選択肢の幅
	float	fHeight;				// 選択肢の高さ
	bool	bSort;					// 並べ方 [ true : 縦 false : 横 ]
}SelectArgument;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitSelect(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitSelect(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateSelect(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawSelect(void);

//--------------------------------------------------
// 設定
// 引数1  : SelectArgument &menu / 構造体 メニュー情報
// 返値   ; int / 何番目かのインデックス
//--------------------------------------------------
int SetSelect(const SelectArgument &menu);

//--------------------------------------------------
// セレクトの色の設定
// 引数1  : int nIdxSelect / セレクトのインデックス
// 引数2  : int nIdxOption / 選択肢のインデックス
// 引数3  : COLOR color / 色
//--------------------------------------------------
void SetColorSelect(int nIdxSelect, int nIdxOption, COLOR color);

//--------------------------------------------------
// セレクトのテクスチャの変更
// 引数1  : int nIdxSelect / セレクトのインデックス
// 引数2  : int nIdxOption / 選択肢のインデックス
// 引数3  : TEXTURE texture / テクスチャ
//--------------------------------------------------
void ChangeTextuteSelect(int nIdxSelect, int nIdxOption, TEXTURE texture);

//--------------------------------------------------
// メニューのリセット
// 引数  : int nIdx / セレクトのインデックス
//--------------------------------------------------
void ResetSelect(int nIdx);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int nIdxSelect / セレクトのインデックス
// 引数2  : int nIdxOption / 選択肢のインデックス
// 引数3  : bool bDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawSelect(int nIdxSelect, int nIdxOption, bool bDraw);

//--------------------------------------------------
// 選択肢の位置を取得
// 引数1  : int nIdxSelect / セレクトのインデックス
// 引数2  : int nIdxOption / 選択肢のインデックス
// 返値  : D3DXVECTOR3 / 選択肢の位置
//--------------------------------------------------
D3DXVECTOR3 GetPosSelect(int nIdxSelect, int nIdxOption);

//--------------------------------------------------
// 選択肢の色を取得
// 引数1  : int nIdxSelect / セレクトのインデックス
// 引数2  : int nIdxOption / 選択肢のインデックス
// 返値  : D3DXCOLOR / 選択肢の色
//--------------------------------------------------
D3DXCOLOR GetColSelect(int nIdxSelect, int nIdxOption);

#endif // !_SELECT_H_
