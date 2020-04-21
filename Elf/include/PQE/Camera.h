#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera()
	{
		position = glm::vec3(0.0, 0.0, 10.0);
		view = glm::vec3(0.0, 0.0, 0.0);
		up = glm::vec3(0.0, 1.0, 0.0);
		speed = 0.1f;
	}

	~Camera();

	void init(glm::vec3 mposition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 meye = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 mup = glm::vec3(0.0f, 1.0f, 0.0f))
	{
		position = mposition;
		view = meye;
		up = mup;
		speed = 5.0f;
	}

	glm::mat4 getViewMat()
	{
		return glm::lookAt(position, view,up);
	}

	void rotateView(float angle, float x, float y, float z)
	{
		glm::vec3 newView;
		glm::vec3 mview = view - position;

		float cosTheta = (float)cos(angle);
		float sinTheta = (float)sin(angle);

		/** ������ת������xֵ */
		newView.x = (cosTheta + (1 - cosTheta) * x * x)		* mview.x;
		newView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* mview.y;
		newView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* mview.z;

		/** ������ת������yֵ */
		newView.y = ((1 - cosTheta) * x * y + z * sinTheta)	* mview.x;
		newView.y += (cosTheta + (1 - cosTheta) * y * y)		* mview.y;
		newView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* mview.z;

		/** ������ת������zֵ */
		newView.z = ((1 - cosTheta) * x * z - y * sinTheta)	* mview.x;
		newView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* mview.y;
		newView.z += (cosTheta + (1 - cosTheta) * z * z)		* mview.z;

		view = position + newView;
	}

	void useMouse()
	{
		POINT mousePos;									  /**< ���浱ǰ���λ�� */
		int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< �õ���Ļ��ȵ�һ�� */
		int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< �õ���Ļ�߶ȵ�һ�� */
		float angleY = 0.0f;							  /**< �����������ת�Ƕ� */
		float angleZ = 0.0f;		                      /**< �����������ת�Ƕ� */
		static float currentRotX = 0.0f;

		/** �õ���ǰ���λ�� */
		GetCursorPos(&mousePos);
		ShowCursor(TRUE);

		/** ������û���ƶ�,���ø��� */
		if ((mousePos.x == middleX) && (mousePos.y == middleY))
			return;

		/** �������λ������Ļ���� */
		SetCursorPos(middleX, middleY);

		/**< �õ�����ƶ����� */
		angleY = (float)((middleX - mousePos.x)) / 1000.0f;
		angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

		static float lastRotX = 0.0f;      /**< ���ڱ�����ת�Ƕ� */
		lastRotX = currentRotX;

		/** ���������������ת�Ƕ� */
		currentRotX += angleZ;

		/** ���������ת���ȴ���1.0,���ǽ�ȡ��1.0����ת */
		if (currentRotX > 1.0f)
		{
			currentRotX = 1.0f;

			/** ���ݱ���ĽǶ���ת���� */
			if (lastRotX != 1.0f)
			{
				/** ͨ������ҵ�����ת����ֱ������ */
				glm::vec3 vAxis = view - position;
				vAxis=glm::cross(vAxis,up);
				vAxis=glm::normalize(vAxis);
				///��ת
				rotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		/** �����ת����С��-1.0,��Ҳ��ȡ��-1.0����ת */
		else if (currentRotX < -1.0f)
		{
			currentRotX = -1.0f;

			if (lastRotX != -1.0f)
			{

				/** ͨ������ҵ�����ת����ֱ������ */
				glm::vec3 vAxis = view - position;
				vAxis = glm::cross(vAxis, up);
				vAxis = glm::normalize(vAxis);

				///��ת
				rotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		/** �������תangleZ�� */
		else
		{
			/** �ҵ�����ת����ֱ���� */
			glm::vec3 vAxis = view - position;
			vAxis = glm::cross(vAxis, up);
			vAxis = glm::normalize(vAxis);

			///��ת
			rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
		}

		/** ����������ת����� */
		rotateView(angleY, 0, 1, 0);
	}

	void leftMove(bool right)
	{
		float mSpeed = speed;
		if (!right)
		{
			mSpeed *= -1;
		}
		glm::vec3 left = glm::normalize(glm::cross(view - position,up));

		position.x += left.x*mSpeed;
		position.z += left.z*mSpeed;

		view.x += left.x*mSpeed;
		view.z += left.z*mSpeed;
	}

	void fontMove(bool back)
	{
		float mSpeed = speed;
		if (back)
		{
			mSpeed *= -1;
		}
		glm::vec3 fong = glm::normalize(view - position);
		position.x += fong.x*mSpeed;
		position.y += fong.y*mSpeed;
		position.z += fong.z*mSpeed;

		view.x += fong.x*mSpeed;
		view.y += fong.y*mSpeed;
		view.z += fong.z*mSpeed;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	void channgeSpeed()
	{
		if (speed == 1.0f)
		{
			speed = 0.1f;
		}
		else
		{
			speed = 1.0f;
		}
	}

	glm::vec3 &getView()
	{
		return view;
	}
private:
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 up;
	float speed;
};

#endif

