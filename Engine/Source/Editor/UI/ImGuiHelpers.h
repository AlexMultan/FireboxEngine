#pragma once

#include <imgui.h>

namespace ImGui {

    inline bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    inline void TextDisabledCenteredOnLine(const char* text, float alignment = 0.5f, float textSize = 1.0f)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(text).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        ImGui::SetWindowFontScale(textSize);
        ImGui::TextDisabled(text);
        ImGui::SetWindowFontScale(1.0f);
    }
}