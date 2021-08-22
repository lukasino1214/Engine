
#include "Application.hpp"

//#include <glad/glad.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{
    glfwInit();

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

    const char* glsl_version = "#version 450";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float r = 0.0f;
    float increment =  0.05f;
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    bool enable = true;


    Scene scene;
    Entity entity, entity2, entity3;
    //Entity entity2;
    //CameraInfo camera;
    std::vector<Entity> entities;
    
    entity.setName("backpack 1");
    entity.setModel("resources/model/backpack/backpack.obj");
    entity.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    entity.setRotation(glm::vec3(0.0f));
    entity.setScale(glm::vec3(1.0f));

    entity2.setName("backpack 2");
    entity2.setModel("resources/model/backpack/backpack.obj");
    entity2.setPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    entity2.setRotation(glm::vec3(0.0f));
    entity2.setScale(glm::vec3(1.0f));

    entity3.setName("statue 1");
    entity3.setModel("resources/model/liberty/LibertStatue.obj");
    entity3.setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    entity3.setRotation(glm::vec3(0.0f));
    entity3.setScale(glm::vec3(1.0f));

    entities.push_back(entity);
    entities.push_back(entity2);
    entities.push_back(entity3);

    scene.setEntities(entities);

    bool Camera_Move = false;
    bool first = true;
    int selected_Entity = {};

    FramebufferSpecification fbSpec;
    fbSpec.Height = SCR_HEIGHT;
    fbSpec.Width = SCR_WIDTH;
    fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth};
    Framebuffer m_Framebuffer(fbSpec);
    
    Camera camera(window, fbSpec);
    glm::vec2 m_ViewportBounds[2];

    std::cout << glad_glGetString(GL_VERSION) << std::endl;

    glm::vec2 m_ViewportSize = {};

    int m_GizmoType;

    int mouseX, mouseY;

    int pixelData;

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        m_Framebuffer.Bind();
        pixelData = m_Framebuffer.ReadPixel(1, mouseX, mouseY);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_Framebuffer.ClearAttachment(1, -1);

        auto[mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
	    mouseX = (int)mx;
		mouseY = (int)my;

        if(mouseX >= 0 && mouseY >=0 && mouseX < (int)viewportSize.x && mouseY << (int)viewportSize.y) {
            //int pixelData = m_Framebuffer.ReadPixel(1, mouseX, mouseY);
            /*std::cout << "###########################################################################################################################" << std::endl;
            std::cout << "- pixelData " << pixelData << std::endl;
            std::cout << "---------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "- mousePos " << mouseX << " " << mouseY << std::endl;*/
            //std::cout << m_Framebuffer.TestPixel() << std::endl;
            //m_Framebuffer.TestPixel();

            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                if(pixelData <= scene.getMaxID() && 0 <= pixelData) {
                    selected_Entity = pixelData;
                    //std::cout << "yes" << std::endl;
                    //std::cout << pixelData << std::endl; 
                }
            }
        }

        //selected_Entity = pixelData;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        
        bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        // Docking
        {
            if (opt_fullscreen)
            {
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            else
            {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
            // and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            if (!opt_padding)
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &p_open, window_flags);
            if (!opt_padding)
                ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }
            else
            {

            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Options"))
                {
                    // Disabling fullscreen would allow the window to be moved to the front of other windows,
                    // which we can't undo at the moment without finer window depth/z control.
                    ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                    ImGui::MenuItem("Padding", NULL, &opt_padding);
                    ImGui::Separator();

                    if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                    if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                    if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                    if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                    if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                    ImGui::Separator();

                    if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                        p_open = false;
                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }
        }


        //Entity list
        {
            ImGui::Begin("Entity list");
            for(int i = 0; i < entities.size(); i++) {
                //ImGui::Text("%s", entities[i].getName());
                if(ImGui::Button(entities[i].getName().c_str(), ImVec2(80, 25))) {
                    selected_Entity = i;
                }
            }
            ImGui::End();

            /*if(pixelData != -1 && pixelData != 708049008) {
                selected_Entity = pixelData;
            }*/


            glm::vec3 position = entities[selected_Entity].getPosition();
            glm::vec3 rotation = entities[selected_Entity].getRotation();
            glm::vec3 scale = entities[selected_Entity].getScale();

            ImGui::Begin("Entity info");

            ImGui::Text("Name: %s", entities[selected_Entity].getName().c_str());
            ImGui::SliderFloat3("Position: ", &position.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("Rotation: ", &rotation.x, -180.0f, 180.0f);
            ImGui::SliderFloat3("Scale: ", &scale.x, 0.0f, 2.0f);

            entities[selected_Entity].setPosition(position);
            entities[selected_Entity].setRotation(rotation);
            entities[selected_Entity].setScale(scale);

            ImGui::End();

        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 1.0f));
        ImGui::Begin("Viewport");
        //auto viewportOffset = ImGui::GetCursorPos();
        //glm::vec2 m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {
            m_Framebuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
            camera.SetProjection(viewportPanelSize.x, viewportPanelSize.y);
            m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        }
        //camera.Move(window);
        //ImGui::Image((void*)textureColorbuffer, ImVec2{ 400.0f, 300.0f }, ImVec2(0, 1), ImVec2(1, 0));
        //ImGui::GetContentRegionAvail();
        ImGui::Image((void*)m_Framebuffer.GetColorAttachmentRendererID(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

        /*auto windowSize = ImGui::GetWindowSize();
        ImVec2 minBound = ImGui::GetWindowPos();
        minBound.x += viewportOffset.x;
        minBound.y += viewportOffset.y;

        ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
        m_ViewportBounds[0] = { minBound.x, minBound.y };
        m_ViewportBounds[1] = { maxBound.x, maxBound.y };*/

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            if (!ImGuizmo::IsUsing())
                m_GizmoType = -1;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::ROTATE;
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::SCALE;
		}

        // Gizmos
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        float windowWidth = (float)ImGui::GetWindowWidth();
        float winodwHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, winodwHeight);
        glm::mat4 transform = entities[selected_Entity].getTransform();
        ImGuizmo::Manipulate(glm::value_ptr(camera.GetView()), glm::value_ptr(camera.GetProjection()), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));
        if (ImGuizmo::IsUsing()) {
				glm::vec3 translation, rotation, scale;
				//Math::DecomposeTransform(transform, translation, rotation, scale);

				entities[selected_Entity].setPosition(translation);
				entities[selected_Entity].setRotation(rotation);
				entities[selected_Entity].setScale(scale);

                scene.setEntities(entities);
			}
        ImGui::End();

        scene.setEntities(entities);

        /*ImGui::Begin("Color Attachment");
        ImGui::Image((void*)m_Framebuffer.GetColorAttachmentRendererID(1), ImVec2{ ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y }, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();*/
        ImGui::PopStyleVar();

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            Camera_Move = true;
        }

        if(Camera_Move) {
            camera.Move(window);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        
        if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
            Camera_Move = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        ImGui::Render();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

        processInput(window);

        shader.Bind();
        shader.SetUniformMat4f("projection", camera.GetProjection());
        shader.SetUniformMat4f("view", camera.GetView());

        scene.Render(shader);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_Framebuffer.Unbind();



        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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