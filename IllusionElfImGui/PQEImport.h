#ifndef __PQEIMPORT_H__
#define __PQEIMPORT_H__

#include"PQEModel.h"
#include<iostream>

namespace PQE
{
	class PQEImport
	{
	public:
		PQEImport(std::string path);
		PQE_MODEL *GetModel();
		~PQEImport();
	private:
		void LoadModel(std::string path);
		void LoadNode(const aiScene *scene);		//��ȡ�ڵ�
		void LoadMesh(const aiScene *scene);		//��ȡ����
		void LoadMaterial(const aiScene *scene);	//��ȡ����
		void LoadShape(std::string path, std::vector<PQE_SHAPE> &shape);							//��ȡ���ζ���
		void LoadBoneChild(const aiScene *scen);
		void LoadNodeChild(const aiScene *scen, std::vector<PQE_MATRIX> &vec, std::vector<PQE_NODE>& pqe_node, aiNode *node, PQE_NODE *pNodeParent, unsigned int &index);
		void LoadMaterialTexture(aiMaterial *material, PQE_MATERIAL *pqematerial, std::vector<PQE_TEXTURE> &texture, unsigned int materialIndex);
		void LoadMaterialTextureChild(aiMaterial *material, PQE_MATERIAL *pqematerial, aiTextureType type, std::vector<PQE_TEXTURE> &path, std::vector<unsigned int> &textureIndex, unsigned int materialIndex);
		bool checkTextureRepeat(PQE_TEXTURE &tex, std::string path);
		inline void InitFbxSdk(FbxManager *&pManager, FbxScene*&pScene);//��ʼ��fbx sdk
		void LoadFbxNode(FbxNode* pNode, std::vector<PQE_SHAPE> &shape);
		inline void LoadFbxMesh(FbxNode* pNode, std::vector<PQE_SHAPE> &shape);
		inline void LoadFbxShape(FbxMesh* pMesh, PQE_NODE *pqe_node, std::vector<PQE_SHAPE> &shape);
		inline void LoadFbxShapeVertexIndex(PQE_NODE *pqe_node, std::vector<PQE_SHAPE> &shape, std::vector<glm::vec4> &vertex);
		//----------------------------------------------------------------------------------------
		void LoadPQE(std::string path);
		void LoadPQENode();
		void LoadPQEMatrix();
		void LoadPQEMesh();
		void LoadPQEShape();
		void LoadPQEMaterial();
		void LoadPQETexture();
		//----------------------------------------------------------------------------------------
	private:
		bool mIsFbx;
		PQE_MODEL *mModel;
		std::fstream *file;
		std::string mModelPath;
	};
}


#endif // !__PQEIMPORT_H__



