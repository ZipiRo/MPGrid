void InterfaceManager::Modulesbar(ApplicationContext &context)
{
    Vector2f position = context.interface.GetModulesbarPosition();
    Vector2f button_size(20.0f, 20.0f);

    const auto &modules = GetModules();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
                             ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoCollapse;

    ImGui::SetNextWindowPos(ImVec2(position.x, position.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(button_size.x + 37.5f, (button_size.y + 28.0f) * modules.size()), ImGuiCond_Always);
    ImGui::Begin("##Modulesbar", nullptr, flags);

    for (int i = 0; i < modules.size(); i++)
    {
        const ModuleEntry &module_entry = modules[i];

        ImGui::PushStyleColor(ImGuiCol_Button, (i == context.using_module) ? ImVec4(0.2f, 0.7f, 0.2f, 1.0f) : ImGui::GetStyleColorVec4(ImGuiCol_Button));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));

        if (Input::IsKeyDown(module_entry.open_key) ||
            ImGui::ImageButton(module_entry.name.c_str(), ResourceManager::Textures.Get(module_entry.texture_name), Vector2f(20, 20)))
            context.SetModule(i);

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered())
            ImGui::SetTooltip(module_entry.tooltip.c_str());

        ImGui::SameLine(-1, 11.5f);
        ImGui::Text(std::to_string(i + 1).c_str());
    }

    ImGui::End();
}