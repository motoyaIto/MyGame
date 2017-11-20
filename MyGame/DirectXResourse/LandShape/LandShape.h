//
//地形と三角形のあたり判定
//motoyaitou 
//2017/08/21
//
//https://github.com/sfujisawa2017/GameEngineTKGS3/blob/master/GameEngineTK/LandShape.h
#pragma once

#include "..//DirectXResourse.h"

#include <map>
#include <SimpleMath.h>

#include "..//Obj3D//Obj3D.h"
#include "..//..//Camera//Camera.h"
#include "..//..//HitDecision//HitDecision.h"


// 共用データ初期化用構造体
struct LandShapeCommonDef
{
	// デバイス(DirectX11)
	ID3D11Device* pDevice;
	// デバイスコンテキスト(DirectX11)
	ID3D11DeviceContext* pDeviceContext;
	// カメラ
	Camera* pCamera;

	LandShapeCommonDef()
	{
		pDevice = nullptr;
		pDeviceContext = nullptr;
		pCamera = nullptr;
	}
};

// 共用データ
class LandShapeCommon
{
	// LandShapeクラスからメンバ変数にアクセスできるようにする
	friend class LandShape;
public:
	// デバッグ表示用の最大頂点数
	static const size_t BatchSize = 6144;
	// コンストラクタ
	LandShapeCommon(LandShapeCommonDef def);
	// デストラクタ
	~LandShapeCommon();
protected:
	// 共通カメラ
	Camera* m_pCamera;
	// コモンステートへのポインタ
	std::unique_ptr<DirectX::CommonStates>	m_pStates;
	// エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory>	m_pEffectFactory;
	// ベーシックエフェクトへのポインタ
	std::unique_ptr<DirectX::BasicEffect>	m_pEffect;
	// プリミティブバッチへのポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_pPrimitiveBatch;
	// 入力レイアウトへのポインタ
	ID3D11InputLayout*	m_pInputLayout;
	// デバイスコンテキストへのポインタ
	ID3D11DeviceContext*	m_pDeviceContext;
};


// 地形当たり
class LandShape
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;
	using Quaternion = DirectX::SimpleMath::Quaternion;

public:
	// エフェクトファクトリ生成
	static void InitializeCommon(LandShapeCommonDef def);

	// コンストラクタ
	LandShape();
	// 初期化
	void Initialize(const std::wstring& filename_bin, const std::wstring& filename_cmo);
	// ワールド行列の計算
	void Update();
	// デバッグ描画
	void Draw();
	// ライティングカット
	void DisableLighting();

	bool IntersectSphere(const Sphere& sphere, Vector3* reject);
	bool IntersectSegment(const Segment& segment, Vector3* inter);

public://setter
	void SetTrans(const Vector3& trans) { m_Obj.SetTranslation(trans); }
	void SetRotationQ(const Quaternion& rotationQ) { m_Obj.SetRotationQ(rotationQ); }
	void SetRotationO(const Vector3& rot) { m_Obj.SetRotationO(rot); }
	void SetScale(float scale) { m_Obj.SetScale(Vector3(scale)); }
	void SetLocalWorld(const Matrix& mat) { m_Obj.SetWorld(mat); }

	const Vector3& GetTrans() { return m_Obj.GetTranslation(); }
	const Quaternion& GetRotationQ() { return m_Obj.GetRotationQ(); }
	const Vector3& GetRotationO() { return m_Obj.GetRotationO(); }
	float GetScale() { return m_Obj.GetScale().x; }
	const Matrix& GetLocalWorld() { return m_Obj.GetWorld(); }

protected:
	// 共通データ
	static std::unique_ptr<LandShapeCommon> s_pCommon;
	// 地形当たりデータマップ
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> s_dataarray;

	// 表示オブジェクト
	Obj3D m_Obj;
	// 地形当たりデータ
	const LandShapeData* m_pData;
	// ワールド→モデル行列
	DirectX::SimpleMath::Matrix m_WorldLocal;
};