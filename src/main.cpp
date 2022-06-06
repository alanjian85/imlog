#include <GLFw/glfw3.h>
#include <imgui.h>
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#include <spdlog/spdlog.h>

#include "log_sink.hpp"

const char* getClipboardText(void* userData) {
    return glfwGetClipboardString(static_cast<GLFWwindow*>(userData));
}

void setClipboardText(void* userData, const char* text) {
    glfwSetClipboardString(static_cast<GLFWwindow*>(userData), text);
}

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    glfwInit();

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ImLog", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("fonts/consola.ttf", 24.0f);
    io.Fonts->AddFontDefault();
    io.UserData = window;
    io.GetClipboardTextFn = getClipboardText;
    io.SetClipboardTextFn = setClipboardText;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();

    Log log;
    auto logSink = std::make_shared<LogSink_st>(log);
    spdlog::default_logger()->sinks().push_back(logSink);

    spdlog::info("Info");
    spdlog::warn("Warning");
    spdlog::error("Error");
    spdlog::critical("Critical");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
            //ImGui::ShowDemoWindow();
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
            log.draw("Log");
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}