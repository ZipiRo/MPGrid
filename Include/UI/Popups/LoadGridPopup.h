class LoadGridPopup : public Popup
{
private:
    char savefile_input[100];
    std::vector<std::string> files;

public:
    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(335, 300), ImGuiCond_Always);
        
        ImGui::Text(std::string("File Name (" + GridSaveFileExt + ')').c_str());
        ImGui::InputText("##FileName", savefile_input, 100);
        ImGui::SameLine();
        if((ImGui::Button("Load (Enter)") || ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Enter)) && 
            !std::string(savefile_input).empty())
        {
            if(!context.grid.Load(savefile_input)) return;
            context.grid_render.Build(context.grid.GetSize());
            context.grid_cursor.Init(context.grid_render.GetCellSize());
            open = false;       
        }

        ImGui::Text(std::string(GridSaveFileDir).c_str());
        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetStyle().ItemSpacing.x - ImGui::CalcTextSize("Refresh").x - 10);
        if(ImGui::Button("Refresh"))
            files = GetStrFilesFrom(GridSaveFileDir, GridSaveFileExt);

        ImGui::BeginChild("FileList", ImVec2(0, -1), true);
        for(auto &file : files)
        {
            if(ImGui::Selectable(file.c_str()))
                strcpy(savefile_input, file.c_str());

            if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
            {   
                if(!context.grid.Load(savefile_input)) return;
                context.grid_render.Build(context.grid.GetSize());
                context.grid_cursor.Init(context.grid_render.GetCellSize());
                open = false;     
            }
        }
        ImGui::EndChild();
    }

    std::string GetName() override 
    {
        return "Load Grid";
    }
};