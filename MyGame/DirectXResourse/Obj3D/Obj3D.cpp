//
//3D描画
//itomotoya
//2017.08.09

#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;//汎用描画ステート
std::unique_ptr<DirectX::EffectFactory> Obj3D::m_factory;//エフェクトファクトリ

Camera* Obj3D::m_camera;//カメラ

void Obj3D::InitializeStatic(Camera * camera)
{
	m_camera = camera;
}


Obj3D::Obj3D()
	//: m_model(nullptr)
	: m_scale(Vector3::Zero)
	, m_rotationQ(Quaternion::Identity)
	, m_rotationO(Vector3::Zero)
	, m_translation(Vector3::Zero)
	, m_world(Matrix::Identity)

	, m_parent(nullptr)
	
{
	
	// 汎用描画ステート
		m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	//エフェクトファクトリを作成
	m_factory = std::make_unique<DirectX::EffectFactory>(m_d3dDevice.Get());
	//テクスチャの読み込みパス設定
	m_factory->SetDirectory(L"Resources");
}



Obj3D::~Obj3D()
{
	delete m_parent;
}


void Obj3D::UpdateQ()
{
	//行列の計算======================================================
	//スケールの行列を作成
	Matrix scalemat = Matrix::CreateScale(m_scale);

	//回転行列
	Matrix rotmat;

	//クオータニオン行列の作成
	rotmat = Matrix::CreateFromQuaternion(m_rotationQ);

	//平行行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//ワールド行列を計算する
	m_world = scalemat * transmat* rotmat;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3D::UpdateO()
{
	//スケールの行列を作成
	Matrix scalemat = Matrix::CreateScale(m_scale);

	//回転行列
	Matrix rotmat;

	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotationO.z);
	Matrix rotmatX = Matrix::CreateRotationX(m_rotationO.x);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotationO.y);
	rotmat = rotmatZ * rotmatX * rotmatY;

	/*Matrix Trotmat;

	rotmatZ = Matrix::CreateRotationZ(0);
	rotmatX = Matrix::CreateRotationX(180);
	rotmatY = Matrix::CreateRotationY(0);
	Trotmat = rotmatZ * rotmatX * rotmatY;*/

	//平行行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//ワールド行列を計算する
	m_world = scalemat * rotmat * transmat;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3D::Render()
{
	assert(m_camera);//カメラがあるかの確認

	if (m_model)
	{
		//3Dモデルの描画
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());
	}
}

/// <summary>
/// モデルの読み込み
/// </summary>
/// <param name="fileName">ファイル名</param>
void Obj3D::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);

	//メッシュの塊を取得
	m_meshes = &m_model->meshes;
}


