//
//�n�`�ƎO�p�`�̂����蔻��
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


// ���p�f�[�^�������p�\����
struct LandShapeCommonDef
{
	// �f�o�C�X(DirectX11)
	ID3D11Device* pDevice;
	// �f�o�C�X�R���e�L�X�g(DirectX11)
	ID3D11DeviceContext* pDeviceContext;
	// �J����
	Camera* pCamera;

	LandShapeCommonDef()
	{
		pDevice = nullptr;
		pDeviceContext = nullptr;
		pCamera = nullptr;
	}
};

// ���p�f�[�^
class LandShapeCommon
{
	// LandShape�N���X���烁���o�ϐ��ɃA�N�Z�X�ł���悤�ɂ���
	friend class LandShape;
public:
	// �f�o�b�O�\���p�̍ő咸�_��
	static const size_t BatchSize = 6144;
	// �R���X�g���N�^
	LandShapeCommon(LandShapeCommonDef def);
	// �f�X�g���N�^
	~LandShapeCommon();
protected:
	// ���ʃJ����
	Camera* m_pCamera;
	// �R�����X�e�[�g�ւ̃|�C���^
	std::unique_ptr<DirectX::CommonStates>	m_pStates;
	// �G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory>	m_pEffectFactory;
	// �x�[�V�b�N�G�t�F�N�g�ւ̃|�C���^
	std::unique_ptr<DirectX::BasicEffect>	m_pEffect;
	// �v���~�e�B�u�o�b�`�ւ̃|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_pPrimitiveBatch;
	// ���̓��C�A�E�g�ւ̃|�C���^
	ID3D11InputLayout*	m_pInputLayout;
	// �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
	ID3D11DeviceContext*	m_pDeviceContext;
};


// �n�`������
class LandShape
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;
	using Quaternion = DirectX::SimpleMath::Quaternion;

public:
	// �G�t�F�N�g�t�@�N�g������
	static void InitializeCommon(LandShapeCommonDef def);

	// �R���X�g���N�^
	LandShape();
	// ������
	void Initialize(const std::wstring& filename_bin, const std::wstring& filename_cmo);
	// ���[���h�s��̌v�Z
	void Update();
	// �f�o�b�O�`��
	void Draw();
	// ���C�e�B���O�J�b�g
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
	// ���ʃf�[�^
	static std::unique_ptr<LandShapeCommon> s_pCommon;
	// �n�`������f�[�^�}�b�v
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> s_dataarray;

	// �\���I�u�W�F�N�g
	Obj3D m_Obj;
	// �n�`������f�[�^
	const LandShapeData* m_pData;
	// ���[���h�����f���s��
	DirectX::SimpleMath::Matrix m_WorldLocal;
};