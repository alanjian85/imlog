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
        m_LineOffsets.clear();
        m_LineOffsets.push_back(0);
    }

    void addLog(const char* str) {
        int oldSize = m_Buffer.size();
        m_Buffer.append(str);
        int newSize = m_Buffer.size();
        for (; oldSize < newSize; ++oldSize) {
            if (m_Buffer[oldSize] == '\n') {
                m_LineOffsets.push_back(oldSize + 1);
            }
        }
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

            ImGui::Separator();
            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
                
            ImGui::EndChild();
        ImGui::End();
    }
private:
    ImGuiTextBuffer m_Buffer;
    ImGuiTextFilter m_Filter;
    std::vector<int> m_LineOffsets;
    bool m_AutoScroll;
};

#endif