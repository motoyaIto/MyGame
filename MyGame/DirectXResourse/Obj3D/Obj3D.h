//
//3D�`��
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
	static std::unique_ptr<DirectX::CommonStates> m_states;//�ėp�`��X�e�[�g
	static std::unique_ptr<DirectX::EffectFactory> m_factory;//�G�t�F�N�g�t�@�N�g��

	static Camera* m_camera;//�J����

private:
	std::unique_ptr<DirectX::Model> m_model;//3D���f��
	DirectX::ModelMesh::Collection* m_meshes;//���b�V���f�[�^

	Vector3 m_scale;		//�傫��
	Quaternion m_rotationQ;	//��](�N�I�[�^�j�I��)
	Vector3 m_rotationO;	//��](�I�C���[�p)
	Vector3 m_translation;	//�ړ�����
	Matrix m_world;			//���[���h���W

	Obj3D* m_parent;		//�e�̍s��
	
	
	
public:
	static void InitializeStatic(static Camera* camera);

public:
	Obj3D();
	~Obj3D();

	

	void UpdateQ();//�N�H�[�^�j�I���Ōv�Z����Ƃ��̃A�b�v�f�[�g
	void UpdateO();//�I�C���[�p�Ōv�Z����Ƃ��̃A�b�v�f�[�g

	void Render();

	void LoadModel(const wchar_t* fileName);//���f���̓ǂݍ���

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