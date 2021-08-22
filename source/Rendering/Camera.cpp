#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <imgui.h>
#include <iostream>

float mouseSpeed = 0.005f;
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float speed = 0.005f;
//glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::mat4 View = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//glm::mat4 View = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

bool Camera_Move = false;
bool first = true;

/*glm::mat4 Camera::movement(GLFWwindow* window) {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, 1024 / 2, 576 / 2);

    horizontalAngle -= mouseSpeed * float(1024 / 2 - xpos);
    verticalAngle += mouseSpeed * float(576 / 2 - ypos);

    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    View = glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

	return View;
}*/

/*CameraInfo Camera::Camera(GLFWwindow* window) {
    CameraInfo Info;

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, 800 / 2, 600 / 2);

    horizontalAngle += mouseSpeed * float(800 / 2 - xpos);
    verticalAngle += mouseSpeed * float(600 / 2 - ypos);

    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    View = glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    Info.view = View;
    Info.position = position;
    Info.direction = direction;

    return Info;
}

CameraInfo Camera::Mode(GLFWwindow* window, CameraInfo camera) {
    if(first) {
            first = false;
            camera = Camera(window);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            Camera_Move = true;
        }
        
        if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
            Camera_Move = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if(Camera_Move) {
            camera = Camera(window);
        }

        return camera;
}*/

Camera::Camera(GLFWwindow* window, const FramebufferSpecification& spec) : m_Specification(spec) {
    m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::mat4 m_View = glm::lookAt(m_Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    Move(window);
    SetFOV(45.0f);
    SetProjection(spec.Width, spec.Height);
    
}

void Camera::Move(GLFWwindow* window) {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, m_Specification.Width / 2, m_Specification.Height / 2);

    horizontalAngle += mouseSpeed * float(m_Specification.Width / 2 - xpos);
    verticalAngle += mouseSpeed * float(m_Specification.Height / 2 - ypos);


    glm::vec3 m_Direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

    // Up vector
    glm::vec3 up = glm::cross(right, m_Direction);


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_Position += m_Direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_Position -= m_Direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_Position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_Position -= right * deltaTime * speed;
    }

    m_View = glm::lookAt(
        m_Position,           // Camera is here
        m_Position + m_Direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    ); 
}