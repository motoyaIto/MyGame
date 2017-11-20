//
//デバック用カメラ
//
//Motoya Ito
//2017/10/16
//参考資料:学校配布のプロジェクト
#pragma once
#include "..//Camera.h"


class DebugCamera : public Camera
{
private://静的変数
	//デフォルトのカメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

private://内部関数
	void Motion(const int& x, const int& y);//移動先の行列を計算

private:
	Vector2 m_nowAngle;		//今の回転角
	Vector2 m_afterAngle;	//回転後の回転角
	
	Vector2 m_drag;			//ドラッグされた座標
	
	Vector2 m_relativeScale;//画面の相対的スケール

	int m_scrollWheelValue;	// スクロールフォイール値

public:
	DebugCamera(int width, int height);
	~DebugCamera() override;

	void Update() override;

public://getter

public://setter
	
};
