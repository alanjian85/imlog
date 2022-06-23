#ifndef LOG_HPP
#define LOG_HPP

#include <vector>

#include <imgui.h>

#include "message.hpp"

class Log {
public:
    void clear() {
        messages.clear();
    }
    
    void addMessage(Message msg) {
        messages.push_back(std::move(msg));
        scroll = true;
    }

    void draw(const char* title, bool* open = nullptr) {
        ImGui::Begin(title, open);
            if (ImGui::Button("Clear")) clear();
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");

            ImGui::Separator();
            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
                if (copy) ImGui::LogToClipboard();

                for (const auto& msg : messages) {
                    ImGui::TextUnformatted(msg.head.c_str()); ImGui::SameLine();
                    ImGui::TextColored(getLevelColor(msg.level), msg.body.c_str()); ImGui::SameLine();
                    ImGui::TextUnformatted(msg.foot.c_str());
                }

                if (scroll) {
                    ImGui::SetScrollHereY(1.0f);
                    scroll = false;
                }
            ImGui::PopStyleVar();
            ImGui::EndChild();
        ImGui::End();
    }
protected:
    static ImVec4 getLevelColor(spdlog::level::level_enum level) {
        switch (level) {
            case spdlog::level::info:     return ImVec4(0, 255, 0, 255);
            case spdlog::level::warn:     return ImVec4(255, 255, 0, 255);
            case spdlog::level::err:      return ImVec4(255, 0, 0, 255);
            case spdlog::level::critical: return ImVec4(255, 0, 255, 255);
            default:                      return ImVec4(0, 0, 0, 255);
        }
    }
private:
    bool scroll = false;
    std::vector<Message> messages;
};

#endif