class ShowKeybindsPopup : public Popup
{
private:
public:
    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(400, 400), ImGuiCond_Always);
        
        if (ImGui::BeginTable("Keybinds", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Key");
            ImGui::TableSetupColumn("Action");
            ImGui::TableHeadersRow();

            auto Row = [](const char* key, const char* action)
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", key);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", action);
            };

            Row("LMB", "Place");
            Row("RMB", "Remove");
            Row("LShift", "Show module settings");
            Row("Esc", "Close windows/popups");
            Row("Num1", "Topografy module");
            Row("Num2", "Pathfinding module");
            Row("Num3", "Maze generator module");
            Row("Tab", "Hide sidebar");
            Row("Space", "Start algorithm");
            Row("P", "Pause algorithm");
            Row("H", "Hide interface");
            Row("T", "Random algorithm positions");
            Row("F", "Fill grid");
            Row("C", "Clear grid");
            Row("R", "Reset algorithm/grid");
            Row("Ctrl + Wheel", "Switch algorithm");

            ImGui::EndTable();
        }
    }  

    std::string GetName() override 
    {
        return "Keybinds";
    }
};