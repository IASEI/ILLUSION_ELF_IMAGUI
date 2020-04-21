#ifndef __FANTASYMAGIC_H__
#define __FANTASYMAGIC_H__

#include "fantastic.h"
#include "PurpleDreamElf.h"

namespace FM
{

	class ModelInput_PDE
	{
	public:
		int ii;
		ModelInput_PDE();

		~ModelInput_PDE();

		//�������뺯��
	public:
		//����ģ����Ϣ
		bool importFile(const TCHAR *filename);

		bool importFile(const char *filename);

	private:
		//������Ϣ�ֱ�1
		void importChoose(const char *channge, PDE::model_m_pde *models, FILE *fp);

		//������Ϣ�ֱ�2
		void importChoose(const char *channge, FILE *fp);

		//�����ܵ�����
		void importModelRoot(FILE *fp);

		//���뵥��ģ����Ϣ����תվ��
		void importModel(PDE::root_m_pde *modelRoot, FILE *fp);

		//���뵥��ģ��ͷ��Ϣ
		void importModelName(PDE::model_m_pde *models, FILE *fp);

		//���뵥��ģ��ȫ����Ϣ
		void importModelInformation(PDE::model_m_pde *models, FILE *fp);

		//����ͨ��
		void importMapChannel(PDE::model_m_pde *models, FILE *fp);

		//���붥��
		void importVertex(PDE::model_m_pde *models, FILE *fp);

		//���������Ϣ
		void importMesh(PDE::model_m_pde *models, FILE *fp);

		//����ƹ�
		void importLight(PDE::model_m_pde *models, FILE *fp);

		//�����޸���
		void importModifier(PDE::model_m_pde *models, FILE *fp);

		//�������
		void importMaterial(FILE *fp);

		//�����Ӳ���
		void importMaterialChild(PDE::material_m_pde *material, FILE *fp);

		PDE::material_m_pde *getMaterial(PDE::root_m_pde modelRoots, const char *materialName);

		//PDE::material_m_pde *getModifier(PDE::model_m_pde model, const char *modelName);

		//Ϊ�������id
		void genTexxtureID();

		//Ϊ�������id��
		void genTextureIDChild(PDE::material_m_pde *material);

		//�����淨��
		void generationMeshNormal(PDE::model_m_pde *model);

		//ȫ�������淨��
		void generationAllMeshNormal();
	public:

		//����ʹ��Freeimage������bit��������
		void setGenCoordFreeimageOrBit(bool is);

	public:
		PDE::model_m_pde *updateJojintMatrix(PDE::model_m_pde *model);

		void updateVertex(PDE::model_m_pde *model);

		//�ӹ��������������ƾ���
		void updateBoneToPostMatrix(PDE::model_m_pde *model, bool isState);

		void updateBoneState(PDE::model_m_pde *model, glm::mat4x4 Rot);

		void initBoneMatrix();
	public:
		void drawUseShader(PDE::model_m_pde *model, Shader *shader);

		void drawAnimation(glm::mat4x4 mat, PDE::model_m_pde *model);

		/** ��ʼ���������� */
		bool IsExtensionSupported(char* szTargetExtension);
		
		bool initMultiTexture();

		void updateModelToWord(PDE::model_m_pde *model);

		void updateModelToModel(PDE::model_m_pde *model);

		//void updateModelToModel(PDE::model_m_pde *model,glm::mat4x4 mat);

		void updateModelNewJointMatrix(PDE::model_m_pde *model, bool isUpateShowMatrix);

		void updateModelJointMatrix(PDE::model_m_pde *model, glm::mat4x4 Rot);

		void initModelJointMatrix(PDE::model_m_pde *model);

		void initModelJointMatrixUntilTran(PDE::model_m_pde *model);

		void updateBoneId();

		void genVaoVboEbo(PDE::model_m_pde *model);

	

		PDE::root_m_pde *getModelRoot();

		bool BOOLS;
	private:
		FILE *fp;

		bool textureOrNormalEBO;//true ʹ��������������Ϊ��Ҫ������falseʹ�÷�������Ϊ��Ҫ����
		bool isGenCoordFreeImageOrBit;//true ʹ��Freiamge ��false ʹ��Bit��������

		char buffer[255];
		char change[255];
		PDE::root_m_pde modelRoot;
		float j;


	};

}
#endif