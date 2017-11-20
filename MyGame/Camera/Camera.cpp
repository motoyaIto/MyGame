//
//カメラの基底クラス
//
//Motoya Ito
//2017/10/16
//参考資料:学校配布のプロジェクト
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="width">画面の横のサイズ</param>
/// <param name="height">画面の縦のサイズ</param>
Camera::Camera(int width, int height)
	: m_world(Matrix::Identity)
	, m_proj(Matrix::Identity)
	, m_fovY(XMConvertToRadians(60.0f))
	, m_aspect((float)width / height)
	, m_nearclip(0.1f)
	, m_farclip(1000.0f)

	, m_view(Matrix::Identity)
	, m_eyepos(Vector3(0.0f, 0.0f, 0.0f))
	, m_refpos(Vector3(0.0f, 0.0f, 0.0f))
	, m_upvec(Vector3(0.0f, 1.0f, 0.0f))
{
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{
	//ビュー行列を作成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//プロジェクション行列
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}
