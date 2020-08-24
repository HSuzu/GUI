// gcc -o teste -O3 -DNDEBUG teste.c -lglfw3 -lpthread -lm -lGL -lX11 -lXext -lXfixes -ldl

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Window.h"
#include "Renderer.h"
#include "materials/UniformVertexColor.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void) {
    Window window(640, 480, "Hello World");

    Renderer renderer;

    {
         float positions[] = {
             -50.0f,  50.0f, 0.0f, 0.0f,
              50.0f,  50.0f, 1.0f, 0.0f,
              50.0f, -50.0f, 1.0f, 1.0f,
             -50.0f, -50.0f,  0.0f, 1.0f,

         };

         unsigned int indices[] = {
             0, 1, 2,
             2, 3, 0
         };


         /* Vertex Array creation */
         VertexArray va;
         VertexBuffer vb(positions, sizeof(positions));

         /* Set structure of our only attribute (positions x,y) */
         VertexBufferLayout layout;
         layout.push<float>(2);
         layout.push<float>(2);
         va.addBuffer(vb, layout);

         IndexBuffer ib(indices, 6);

         glm::mat4 proj = glm::ortho(0.0f, 640.0f, 00.0f, 480.0f, -1.0f, 1.0f);
         glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));


         UniformVertexColor material;
         material.color(0.8f, 0.3f, 0.8f, 1.0f);
        /* Set Shader Uniform */
        va.unbind();
        vb.unbind();
        ib.unbind();


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window.glWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        ImGui::StyleColorsDark();

         float r = 0.0f;
         float increment = 0.05f;

         glm::vec3 translation(200,200,0);

        /* Loop until the user closes the window */
        while (window)
        {
            /* Render here */
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


             glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
             glm::mat4 mvp = proj*view*model;

            material.color(r, 0.3f, 0.8f, 1.0f);
            material.mvp(mvp);

            renderer.draw(va, ib, material);

            material.mvp(proj);
            renderer.draw(va, ib, material);

            if(r >= 1.0f)
                 increment = -0.05f;
             else if(r <= 0.0f)
                 increment = 0.05f;

             r += increment;


             ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 640.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            window.updateBuffers();
            window.pollEvents();
        }

    } // ensures the deletion of index ans vertex buffers before the termination of gl context

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
