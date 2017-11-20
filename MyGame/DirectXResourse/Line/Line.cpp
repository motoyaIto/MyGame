//
//線
//ItoMotoya
//2017/10/16
//参考資料:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#include "Line.h"

#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Line::Line()
{
	this->Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Line::~Line()
{
	delete m_states;//ステータス
	delete m_effect;//エフェクト
}

/// <summary>
/// 初期化
/// </summary>
void Line::Initialize()
{
	//デバイス依存の初期化=======================================================================
	m_states = new DirectX::CommonStates( m_d3dDevice.Get());

	m_effect = new DirectX::BasicEffect(m_d3dDevice.Get());
	m_effect->SetVertexColorEnabled(true);//頂点の色を有効にする

	//入力レイアウトの作成============================================================================
	void const* shaderByteCode;
	size_t byteCodeLength;

	//頂点シェーダの機械コードを取得
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//入力レイアウトに関連付ける
	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements
		, VertexPositionColor::InputElementCount
		, shaderByteCode, byteCodeLength
		, m_inputLayout.ReleaseAndGetAddressOf());

	//頂点のポジションと色を初期化=========================================================
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());


	//初期単位行列の取得
	m_cameraWorld = DirectX::SimpleMath::Matrix::Identity;
}

/// <summary>
/// 更新
/// </summary>
void Line::Update()
{
	m_cameraWorld = m_cameraView * m_cameraProj ;
}

/// <summary>
/// 描画
/// </summary>
void Line::Render()
{
	//第一引数でブレンド方法を確定(ノーマルブレンド)
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	//深度ステンシル(深度バッファー、ステンシルバッファー)
	m_d3dContext->OMSetDepthStencilState(m_states->DepthRead(), 0);
	//サーフェイス上にレンダリング
	m_d3dContext->RSSetState(m_states->CullNone());

	//カメラのワールド行列をセットする
	m_effect->SetWorld(m_cameraWorld);
	//エフェクトを適用
	m_effect->Apply(m_d3dContext.Get());
	//入力レイアウトの適用
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_batch->Begin();

	VertexPositionColor v1(m_startPos, Colors::White);//開始地点
	VertexPositionColor v2(m_endPos, Colors::White);//終了地点
	m_batch->DrawLine(v1, v2);//描画


	m_batch->End();
}
