class SetBackgroundPopup : public Popup
{
private:
public:
    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(400, 60), ImGuiCond_Always);
            
        ImVec4 imgui_color = SFMLToImColor(Application::background);
        if(ImGui::ColorEdit4("Background Color", (float*)&imgui_color))
            Application::background = ImColorToSFML(imgui_color);
    }

    std::string GetName() override 
    {
        return "Set Background";
    }
};