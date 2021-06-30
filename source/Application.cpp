
#include "Application.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);

    Shader shader("resources/shader/model.shader");
    //Model ourModel(FileSystem::getPath("resources/objects/backpack/backpack.obj"));

    //Model ourModel("resources/model/backpack/backpack.obj");

    //Model ourModel("resources/model/gun/Handgun_obj.obj");

    //Model ourModel("resources/model/cottage/cottage_obj.obj");

    //Model ourModel("resources/model/liberty/LibertStatue.obj");
    
    //Model ourModel("resources/model/cube.obj");
    //entity.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    Scene scene;
    Entity entity;
    
    entity.setModel("resources/model/backpack/backpack.obj");
    scene.addEntity(entity);


    /*Model ourModel;
    ourModel.Load("resources/model/cube.obj");*/

    //Model ourModel("resources/model/car/car.obj");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        CameraInfo camera;
        camera = Camera(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shader.Bind();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.SetUniformMat4f("projection", projection);
        shader.SetUniformMat4f("view", camera.view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader.SetUniformMat4f("model", model);
        //ourModel.Draw(shader);
        scene.Render(shader);
        shader.Unbind();



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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