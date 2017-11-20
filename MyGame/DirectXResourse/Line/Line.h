//
//線
//ItoMotoya
//2017/10/16
//参考資料:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once

#include "..//DirectXResourse.h"

#include <CommonStates.h>
#include <Effects.h>
#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


class Line : public DirectXResourse
{
protected:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	DirectX::CommonStates* m_states;//ステータス
	DirectX::BasicEffect* m_effect;//エフェクト
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;//頂点、ポジション、色で高速描画
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//入力レアウト

private:
	Matrix m_cameraWorld;	//カメラのワールド行列
	Matrix m_cameraView;	//カメラのビュー行列
	Matrix m_cameraProj;	//プロジェクション行列(射影行列)

	Vector3 m_startPos;	//ラインの出発点
	Vector3 m_endPos;	//ラインの到達点

public:
	Line();
	~Line();

	void Initialize();
	virtual void Update();
	virtual void Render();

public://getter

public://setter
	void SetView(Matrix CameraView) { m_cameraView = CameraView; }
	void SetProj(Matrix CameraProj) { m_cameraProj = CameraProj; }
	void SetStartPos(Vector3 startPos) { m_startPos = startPos; }
	void SetEndPos(Vector3 endPos) { m_endPos = endPos; }
	
};