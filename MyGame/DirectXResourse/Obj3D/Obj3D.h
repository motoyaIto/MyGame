//
//3D描画
//itomotoya
//2017.08.09

#pragma once

#include <memory>

#include <CommonStates.h>
#include <Effects.h>
#include <Model.h>

#include <SimpleMath.h>

#include "..//DirectXResourse.h"
#include "..//..//Camera//Camera.h"

class Obj3D : public DirectXResourse
{
private:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Quaternion = DirectX::SimpleMath::Quaternion;

private:
	static std::unique_ptr<DirectX::CommonStates> m_states;//汎用描画ステート
	static std::unique_ptr<DirectX::EffectFactory> m_factory;//エフェクトファクトリ

	static Camera* m_camera;//カメラ

private:
	std::unique_ptr<DirectX::Model> m_model;//3Dモデル
	DirectX::ModelMesh::Collection* m_meshes;//メッシュデータ

	Vector3 m_scale;		//大きさ
	Quaternion m_rotationQ;	//回転(クオータニオン)
	Vector3 m_rotationO;	//回転(オイラー角)
	Vector3 m_translation;	//移動距離
	Matrix m_world;			//ワールド座標

	Obj3D* m_parent;		//親の行列
	
	
	
public:
	static void InitializeStatic(static Camera* camera);

public:
	Obj3D();
	~Obj3D();

	

	void UpdateQ();//クォータニオンで計算するときのアップデート
	void UpdateO();//オイラー角で計算するときのアップデート

	void Render();

	void LoadModel(const wchar_t* fileName);//モデルの読み込み

public://getter
	Quaternion& GetRotationQ() { return m_rotationQ; }
	Vector3& GetTranslation() { return m_translation; }
	Matrix& GetWorld() { return m_world; }
	Obj3D* GetPart() { return m_parent; }
	Vector3& GetScale(){ return m_scale; }

	Vector3& GetRotationO() { return m_rotationO; }
	DirectX::ModelMesh::Collection& GetMeshes() { return *m_meshes; }

public://setter
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetTranslation(Vector3 translation) { m_translation = translation; }
	void SetRotationQ(Quaternion rotationQ) { m_rotationQ = rotationQ; }
	void SetPart(Obj3D* parent) { m_parent = parent; }

	void SetWorld(Matrix world) { m_world = world; }
	void SetRotationO(Vector3 rotation) { m_rotationO = rotation; }

};