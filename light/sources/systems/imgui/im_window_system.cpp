//
// Created by k on 11/10/19.
//

#include <flecs.h>
#include <imgui.h>

#include <systems/imgui/im_window_system.h>
#include <core/app.h>
#include <core/components.h>

const char* light::ImWindowSystem::Init(const char* name) {
    App::Instance()->Register("ComImWindow", sizeof(ComImWindow));
    return "ComImWindow";
}

void light::ImWindowSystem::Update(ecs_rows_t *rows) {
    ComImWindow *windows = ecs_column(rows, ComImWindow, 1);
    for(u_int32_t i = 0; i < rows->count; i++) {
        auto data = windows[i];
        if (data.size.x > 0 && data.size.y > 0) {
            ImGui::SetNextWindowContentSize(sf::Vector2f(data.size.x, data.size.y));
        }

        ImGui::Begin(data.name, &data.show);
        for (auto child : data.child) {
            if (child->type == 1) {
                ImGui::Text("%s", child->text);
            } else if (child->type == 2) {
                ImGui::LabelText(child->text, "");
            }
        }
        ImGui::End();
    }
}