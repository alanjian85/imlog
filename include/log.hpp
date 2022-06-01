#ifndef LOG_HPP
#define LOG_HPP

#include <vector>

#include <imgui.h>

class Log {
public:
    Log() {
        m_AutoScroll = true;
        clear();
    }

    void clear() {
        m_Buffer.clear();
    }

    void addLog(const char* str) {
        m_Buffer.append(str);
        m_AutoScroll = true;
    }

    void draw(const char* title, bool* open = nullptr) {
        ImGui::Begin(title, open);
            if (ImGui::Button("Clear")) clear();
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");

            ImGui::Separator();
            ImGui::BeginChild("scrolling");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
                if (copy) ImGui::LogToClipboard();
                ImGui::TextUnformatted(m_Buffer.begin());
                if (m_AutoScroll) {
                    ImGui::SetScrollHereY(1.0f);
                    m_AutoScroll = false;
                }
            ImGui::PopStyleVar();
            ImGui::EndChild();
        ImGui::End();
    }
private:
    ImGuiTextBuffer m_Buffer;
    bool m_AutoScroll;
};

#endif