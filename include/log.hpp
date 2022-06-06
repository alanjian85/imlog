#ifndef LOG_HPP
#define LOG_HPP

#include <vector>

#include <imgui.h>

#include "message.hpp"

class Log {
public:
    Log() {
        m_AutoScroll = true;
        clear();
    }

    void clear() {
        m_Messages.clear();
    }

    void addLog(Message message) {
        m_Messages.push_back(std::move(message));
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
                
                for (const auto& message : m_Messages) {
                    ImGui::TextUnformatted(message.str.c_str());
                }
                
                if (m_AutoScroll) {
                    ImGui::SetScrollHereY(1.0f);
                    m_AutoScroll = false;
                }
            ImGui::PopStyleVar();
            ImGui::EndChild();
        ImGui::End();
    }
private:
    std::vector<Message> m_Messages;
    bool m_AutoScroll;
};

#endif