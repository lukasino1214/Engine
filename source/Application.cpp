
#include "Application.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // positions            // normals             // texture coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f,  0.0f,
    
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f,  0.0f,
    
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
    
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
    
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f,  1.0f,
    
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f,  1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
        
    Shader cube_s("resources/shader/light_direction.shader");
    Shader light_s("resources/shader/light.shader");

    VertexArray cube;
    VertexArray light;
    VertexBuffer vb(vertices, 8 * 36 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    cube.AddBuffer(vb, layout);
    light.AddBuffer(vb, layout);
    cube.Unbind();
    light.Unbind();

    Texture container_texture("resources/texture/container2.png");
    Texture container_texture_specular("resources/texture/container2_specular.png");

    cube_s.Bind();
    container_texture.Bind(0);
    cube_s.SetUniform1i("material.diffuse", 0);
    container_texture.Unbind();
    container_texture_specular.Bind(1);
    cube_s.SetUniform1i("material.specular", 1);
    container_texture_specular.Unbind();

    glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        CameraInfo Info;
        Info = Camera(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        cube_s.Bind();
        //cube_s.SetUniform3f("light.direction", -0.2f, -1.0f, -0.3f);
        cube_s.SetUniform3f("light.direction", 0.0f, -5.0f, 0.0f);
        cube_s.SetUniform3fv("viewPos", Info.position);

        cube_s.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
        cube_s.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f); // darkened
        cube_s.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);


        // material properties
        /*cube_s.SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
        cube_s.SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
        cube_s.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);*/
        cube_s.SetUniform1f("material.shininess", 256.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f);
        glm::mat4 view = Info.view;
        cube_s.SetUniformMat4f("projection", projection);
        cube_s.SetUniformMat4f("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        cube_s.SetUniformMat4f("model", model);

        // render the cube
        container_texture.Bind(0);
        container_texture_specular.Bind(1);
        cube.Bind();
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cube_s.SetUniformMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        cube.Unbind();
        cube_s.Unbind();
        container_texture.Unbind();
        container_texture_specular.Unbind();


        // // also draw the lamp object
        // light_s.Bind();
        // light_s.SetUniformMat4f("projection", projection);
        // light_s.SetUniformMat4f("view", view);
        // model = glm::mat4(1.0f);
        // model = glm::translate(model, lightPos);
        // model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        // light_s.SetUniformMat4f("model", model);

        // light.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // light.Unbind();
        // light_s.Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube.Unbind();
    vb.Bind();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
}