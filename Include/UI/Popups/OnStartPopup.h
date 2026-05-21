class OnStartPopup : public Popup
{
private:

public:
    void Init(ApplicationContext &context) override
    {}

    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(330, 257));

        ImGui::TextWrapped("Welcome to MPGrid! \n\n"
        "MPGrid is an interactive algorithm visualizer where you can explore pathfinding, maze generation, and grid-based simulations in real time.\n\n"
        "Use the grid to place walls, generate mazes, and watch algorithms solve problems step-by-step\n\n"
        "Open the documentation to learn the controls and interface, or close this window and start experimenting directly.");

        ImGui::NewLine();

        if(ImGui::Button("Close"))
            open = false;
        
        ImGui::SameLine();

        if(ImGui::Button("Documentation"))
        {
            StartHDocument(HDocumnets::Document.Get("Main"));
            open = false;
        }
    }

    std::string GetName() override
    {
        return "Welcome";
    }
};