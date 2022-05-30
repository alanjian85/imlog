#ifndef LOG_HPP
#define LOG_HPP

#include <imgui.h>

class Log {
public:
    Log() {
        m_AutoScroll = true;
    }

    void draw(const char* title, bool* open = nullptr) {
        if (!ImGui::Begin(title, open)) {
            ImGui::End();
            return;
        }
            if (ImGui::BeginPopup("Options")) {
                ImGui::Checkbox("Auto-scroll", &m_AutoScroll);
                ImGui::EndPopup();
            }
        
            if (ImGui::Button("Options"))
                ImGui::OpenPopup("Options");
            ImGui::SameLine();
            bool clear = ImGui::Button("Clear");
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");
            ImGui::SameLine();
            m_Filter.Draw("Filter", -50.0f);

        ImGui::End();
    }
private:
    ImGuiTextFilter m_Filter;
    bool m_AutoScroll;
};

#endif