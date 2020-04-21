#ifndef __PQEMODEL_H__
#define __PQEMODEL_H__

#include "PQE\PurpleDreamElf.h"
#include "fbxsdk.h"
#include<algorithm>
#include<functional>

namespace PQE
{

	class PQE_MODEL;
	class PQE_NODE;
	class PQE_MESH;
	class PQE_MATERIAL;
	class PQE_TEXTURE;
	class PQE_MATRIX;
	class PQE_SHAPE;
	class AABB;

	class PQEExport;
	class PQEImport;


	enum PQE_MODEL_TYPE
	{
		PQE_MODEL_FBX,
		PQE_MODEL_ASE,
		PQE_MODEL_OTHER
	};
	
	enum PQE_FRAME_TYPE
	{
		PQE_FRAME_ORDINARY,
		PQE_FRAME_SHADOW,
		PQE_FRAME_MSAA,
	};

	class PQE_MODEL
	{
	public:
		PQE_MODEL();
		void SetMatrix(PQE_MATRIX *matrix, glm::mat4 *mat);
		void SetMatrix(PQE_NODE *node, glm::mat4 *mat);
		void SetMatrix(std::string name, glm::mat4 *mat);
		void GenSpesicalID();
		void GenTextureID();
		void ComputeBoneMatrix(PQE_NODE *node, glm::mat4 parent, glm::mat4 *data);
		PQE_NODE *FindNode(std::string name);
		PQE_MATRIX *FindMatrix(std::string name);
		PQE_MODEL *operator=(PQEImport& mImport);
		~PQE_MODEL();
	public:
		unsigned int        		nodeNum;		//�ڵ�����
		unsigned int				meshNum;		//��������
		unsigned int				shapeNum;		//��������
		unsigned int        		matrixNum;		//��������
		unsigned int				textureNum;		//��������
		unsigned int				materialNum;	//��������
		std::vector<PQE_NODE>		mNode;			//���
		std::vector<PQE_MESH>		mMesh;			//����
		std::vector<PQE_SHAPE>		mShape;			//���ζ���
		std::vector<PQE_MATRIX>		mMatrix;		//����
		std::vector<PQE_TEXTURE>	mTexture;		//����
		std::vector<PQE_MATERIAL>	mMaterial;		//����
	};

	class PQE_NODE
	{
	public:
		enum PQE_NODE_TYPE
		{
			PQE_NODE_BONE,
			PQE_NODE_MESH,
			PQE_NODE_MESH_SHAPE,
			PQE_NODE_MESH_ROOT
		};
	public:
		PQE_NODE();
		~PQE_NODE();

	public:
		PQE_NODE_TYPE				mType;			//�ڵ�����
		char						mName[255];		//�ڵ�����
		long 						mSelfId;
		long						mParentId;
		unsigned int				childNum;		//�ӽڵ�����
		unsigned int				meshNum;		//��������
		unsigned int				shapeNum;		//����������
		unsigned int				vertexNum;		//��������
		unsigned int       			 mMatrixIndex;	//��������
		unsigned int				shapeVertexNum;	//���������ж���
		unsigned int				spesicalId[5];
		std::vector<long>			mChildId;
		std::vector<unsigned int>	mMeshIndex;		//����
		std::vector<unsigned int>	mShapeIndex;	//������
		std::vector<glm::int4>		mBoneIndex;		//��������
		std::vector<glm::vec4>		mBoneWeight;	//Ȩ��
		std::vector<glm::vec4>		mPosition;		//����
		std::vector<glm::vec3>		mNormal;		//����
		std::vector<glm::vec2>		mCoord;			//��������
		AABB						*aabb;			//��Χ��
	};

	class PQE_MATRIX
	{
	public:
		PQE_MATRIX();
		~PQE_MATRIX();

	public:
		glm::mat4			mSelf;			//�ڵ��ʼ����
		glm::mat4			mFinsh;			//�ڵ���Ծ���
		glm::mat4			mOffset;		//�ڵ�ƫ�ƾ���
	};

	class PQE_MESH
	{
	public:
		enum PQE_MESH_TYPE
		{
			PQE_MESH_ORDINARY,
			PQE_MESH_SHAPE,
			PQE_MESH_SHAPE_INDEX
		};
	public:
		PQE_MESH();
		~PQE_MESH();

	public:
		PQE_MESH_TYPE		mType;			//��������
		char				mName[255];		//����
		unsigned int		vertexNum;		//��������
		unsigned int		faceNum;		//������
		unsigned int		boneNum;		//��������
		unsigned int		mMaterilIndex;	//��������
		unsigned int        mShapeWeight;	//�α�Ȩ��
		unsigned int		vao;
		unsigned int		ebo;
		std::vector<unsigned int>		mFace;			//��
		AABB				*aabb;			//aabb��Χ��
	};

	class PQE_SHAPE
	{
	public:
		PQE_SHAPE();
		~PQE_SHAPE();
	public:
		char					mName[255];		//����
		float					weight;			//Ȩ��
		unsigned int			vertexNum;		//��������
		std::vector<glm::vec4>	mPosition;		//����������
	};

	class PQE_MATERIAL
	{
	public:
		PQE_MATERIAL();
		~PQE_MATERIAL();

	public:
		unsigned int				materialNum;	//��������
		unsigned int				textureNum;		//��������
		std::vector<unsigned int>	mTextureIndex;	//��������
	};
	
	class PQE_TEXTURE
	{
	public:
		enum PQE_TEXTURE_TYPE
		{

		};
	public:
		PQE_TEXTURE();
		PQE_TEXTURE(PQE_TEXTURE_TYPE type, std::string path);
		~PQE_TEXTURE();

	public:
		unsigned int		mId;			//����id
		PQE_TEXTURE_TYPE	mType;			//��������
		char				mPath[255];		//����·��
	};

	

}


#endif