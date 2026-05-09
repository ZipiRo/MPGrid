class ResizeGridPopup : public Popup
{
private:
    int size_input[2] = {};
    bool lock_size_input = true;

public:
    void Init(ApplicationContext &context) override
    {
        size_input[0] = context.grid.GetSize().x;
        size_input[1] = context.grid.GetSize().y;
    }

    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(360, 80), ImGuiCond_Always);
        ImGui::Text("Cols");
        ImGui::SameLine(145.0f);

        ImGui::Text("Rows");

        ImGui::SetNextItemWidth(100.0f);
        ImGui::InputInt("##Colls", &size_input[0]);

        ImGui::SameLine();
        if (ImGui::Checkbox("##LockSize", &lock_size_input))
        {
            if (lock_size_input)
                size_input[1] = size_input[0];
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Make the rows and cols equal");

        ImGui::SameLine();
        ImGui::SetNextItemWidth(100.0f);
        ImGui::InputInt("##Rows", &size_input[1]);

        ImGui::SameLine();
        bool changes = false;
        if (size_input[0] != context.grid.GetSize().x || size_input[1] != context.grid.GetSize().y)
        {
            changes = true;

            if (lock_size_input)
                size_input[1] = size_input[0];
        }

        if ((ImGui::Button("Apply (Enter)") || ImGui::IsKeyDown(ImGuiKey_Enter)) && changes)
        {
            context.grid.Create(size_input[0], size_input[1]);
            context.grid_render.Build(context.grid.GetSize());
            context.grid_cursor.Init(context.grid_render.GetCellSize());
            open = false;
        }
    }

    std::string GetName() override
    {
        return "Resize Grid";
    }
};