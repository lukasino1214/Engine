#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Framebuffer.hpp"

/*class Camera {
public:
	//Controls(GLFWwindow* window);
	glm::mat4 movement(GLFWwindow* window);
};*/

/*struct CameraInfo {
	glm::vec3 position;
	glm::mat4 view;
	glm::vec3 direction;
};

/*namespace Camera {
	CameraInfo Camera(GLFWwindow* window);
	CameraInfo Mode(GLFWwindow* window, CameraInfo camera);
}*/

class Camera {
	private:
		glm::vec3 m_Position;
		glm::mat4 m_View;
		glm::vec3 m_Direction;
		glm::mat4 m_Projection;
		FramebufferSpecification m_Specification;
		float m_FOV = 90.0f;
		//bool m_Mode;
	public:
		Camera(GLFWwindow* window, const FramebufferSpecification& spec);

		void Move(GLFWwindow* window);

		void SetPosition(glm::vec3 position) { position = m_Position; }
		glm::mat4 GetProjection() { return m_Projection; }
		glm::mat4 GetView() { return m_View; }
		void SetFOV(float FOV) { FOV = m_FOV; }
		float GetFOV() { return m_FOV; }
		void SetProjection(int width, int height) { m_Projection = glm::perspective(glm::radians(GetFOV()), (float)width / (float)height, 0.1f, 1000.0f); }

		/*void SetTestProjection() {
			m_Projection = glm::perspective(glm::radians(GetFOV()), (float) 800 /(float) 600, 0.1f, 1000.0f);
			//Please work!!! 
		}*/
		/*void SetMode(bool mode) { mode = m_Mode; }
		bool GetMode() { return m_Mode; }*/

};