class GridColorThemesPopup : public Popup
{
private:
public:
    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(300, 500));

        ImGui::SetNextItemWidth(-1);
        if(ImGui::BeginCombo("##Themes", context.grid_render.GetColorTheme().name.c_str()))
        {
            for(int i = 0; i < context.grid_render.grid_color_themes.size(); i++)
            {
                bool is_selected = false;

                if(ImGui::Selectable(context.grid_render.grid_color_themes[i].name.c_str(), is_selected))
                    context.grid_render.UsePresetTheme(i);

                if(is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

        GridColorTheme grid_current_theme = context.grid_render.GetColorTheme();
        
        ImVec4 imgui_color;
        for(auto &[name, color] : grid_current_theme.colors)
        {
            imgui_color = SFMLToImColor(color);
            ImGui::ColorButton(std::string("##" + name).c_str(), imgui_color, ImGuiColorEditFlags_NoTooltip, ImVec2(30, 30));
            ImGui::SameLine();
            ImGui::Text(std::string("\n" + name).c_str());
        }
    }

    std::string GetName() override 
    {
        return "Grid Color Themes";
    }
};