void InterfaceManager::Menubar(ApplicationContext &context)
{
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Grid"))
    {
        if (ImGui::MenuItem("Themes"))
            OpenPopup<GridColorThemesPopup>(context);

        if (ImGui::MenuItem("Resize"))
            OpenPopup<ResizeGridPopup>(context);

        if (ImGui::MenuItem("Save"))
            OpenPopup<SaveGridPopup>(context);

        if (ImGui::MenuItem("Load"))
            OpenPopup<LoadGridPopup>(context);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("SetBackgroundColor"))
            OpenPopup<SetBackgroundPopup>(context);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("Keybinds"))
            OpenPopup<ShowKeybindsPopup>(context);

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}