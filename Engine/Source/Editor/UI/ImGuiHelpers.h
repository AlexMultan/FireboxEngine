#pragma once

#include "Utils/Types.h"

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

    inline void TextWithBackground(const char* fmt, ...)
    {
        const ImGuiStyle& style = ImGui::GetStyle();

        char buf[512];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);

        const ImU32 bgColor = ImGui::GetColorU32(ImGuiCol_FrameBg);
        const ImU32 borderColor = ImGui::GetColorU32(ImGuiCol_Border);
        const ImU32 textColor = ImGui::GetColorU32(ImGuiCol_Text);

        ImDrawList* dl = ImGui::GetWindowDrawList();
        const ImVec2 pos = ImGui::GetCursorScreenPos();
        const ImVec2 textSize = ImGui::CalcTextSize(buf);
        const ImVec2 boxSize(textSize.x + style.FramePadding.x * 2.0f,
            textSize.y + style.FramePadding.y * 2.0f);
        const ImVec2 boxMax(pos.x + boxSize.x, pos.y + boxSize.y);

        dl->AddRectFilled(pos, boxMax, bgColor, style.FrameRounding);
        if (style.FrameBorderSize > 0.0f)
            dl->AddRect(pos, boxMax, borderColor, style.FrameRounding,
                0, style.FrameBorderSize);

        dl->AddText(ImVec2(pos.x + style.FramePadding.x,
            pos.y + style.FramePadding.y),
            textColor, buf);

        ImGui::Dummy(boxSize);
    }
}