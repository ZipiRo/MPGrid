#define AUDIO

#include <Application.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <functional>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include <filesystem>
#include <array>
#include <string>

#include <imgui.h>
#include <imgui-SFML.h>

using namespace sf;

#include <HDocumnets.h>

#include <Usings.h>
#include <Grid/Grid.h>
#include <Grid/GridTheme.h>
#include <Grid/GridRenderer.h>
#include <Grid/GridCursor.h>

#include <UI/Interface.h>

struct ApplicationContext
{
    RenderWindow &window;
    Grid &grid;
    GridRenderer &grid_render;
    GridCursor &grid_cursor;
    Interface &interface;
    float delta_time;
    int using_module;
    std::function<void(int)> SetModule;
};

#include <Algorithms/PathAlgorithms/PathAlgorithm.h>
#include <Algorithms/MazeAlgorithms/MazeAlgorithm.h>
#include <Modules/Module.h>

#include <UI/InterfaceManager.h>

class App : public Application
{
private:
    void ChangeModule(int index)
    {
        if (index < 0 || index >= GetModules().size())
            return;

        change_module = true;
        using_module = index;
    }

    void CheckModuleChange()
    {
        if (!change_module)
            return;

        module = GetModules()[using_module].Get();
        module->Init(context);

        context.using_module = using_module;
        change_module = false;
    }

public:
    App() : Application(sf::Vector2u(1920, 1080), "MPGrid", sf::Style::None, sf::State::Windowed)
    {
        GetWindow().setFramerateLimit(999999);
    }

    Grid grid;
    GridRenderer grid_render;
    GridCursor grid_cursor;
    Interface interface;

    std::unique_ptr<Module> module;
    bool change_module = false;
    int using_module = 0;

    ApplicationContext context{
        .window = GetWindow(),
        .grid = grid,
        .grid_render = grid_render,
        .grid_cursor = grid_cursor,
        .interface = interface,
        .SetModule = [this](int index)
        { ChangeModule(index); }};

    InterfaceManager ui_manager;

    void Start() override;
    void End() override;
    void Events(const Event &event) override;
    void Update(float delta_time) override;
    void DrawCanvas() override;
};

bool LoadResources()
{
    if (!ResourceManager::LoadSound("Place", "Resources/Audio/place.wav")) return false;
    if (!ResourceManager::LoadSound("Pop", "Resources/Audio/pop.wav")) return false;
    if (!ResourceManager::LoadSound("Find", "Resources/Audio/find.wav")) return false;
    if (!ResourceManager::LoadSound("Remove", "Resources/Audio/remove.wav")) return false;

    if (!ResourceManager::LoadTexture("Map", "Resources/Textures/map.png")) return false;
    if (!ResourceManager::LoadTexture("Path", "Resources/Textures/path.png")) return false;
    if (!ResourceManager::LoadTexture("Maze", "Resources/Textures/maze.png")) return false;

    if(HDocumnets::LoadDocument("Main", "Resources/Docs/index.html")) return false;
    if(HDocumnets::LoadDocument("BFS_Algo", "Resources/Docs/bfs_algo.html")) return false;
    if(HDocumnets::LoadDocument("DFS_Algo", "Resources/Docs/dfs_algo.html")) return false;
    if(HDocumnets::LoadDocument("RDFS_Algo", "Resources/Docs/random_dfs_algo.html")) return false;
    if(HDocumnets::LoadDocument("PRIM_Algo", "Resources/Docs/prim_algo.html")) return false;
    if(HDocumnets::LoadDocument("RB_Algo", "Resources/Docs/recursive_bactracking_algo.html")) return false;
    if(HDocumnets::LoadDocument("RD_Algo", "Resources/Docs/recursive_division_algo.html")) return false;

    return true;
}

void App::Start()
{
    if (!LoadResources())
    {
        Close();
        return;
    }

    if (!ImGui::SFML::Init(GetWindow()))
    {
        Close();
        return;
    }

    srand(time(0));
    background = Color::Black;

    grid.Create(20, 20);
    grid_render.SetMaxLength(Vector2f(GetWindowSize().y - 70, GetWindowSize().y - 70));
    grid_render.Build(grid.GetSize());
    grid_render.SetPosition(Vector2f(GetWindowSize().x / 2 - grid_render.GetLength().x / 2, GetWindowSize().y / 2 - grid_render.GetLength().y / 2));
    grid_cursor.Init(grid_render.GetCellSize());

    interface.SetSettingsWindow(Vector2f(GetWindowSize().x * 0.4f, GetWindowSize().y * 0.5f));
    interface.SetModulesbar(Vector2f(10, 30));
    interface.SetInfoWindow(Vector2f(GetWindowSize().x * 0.2f, GetWindowSize().y * 0.4f)); 
    interface.SetSidebarWindow(GetWindowSize().x * 0.2f);

    ChangeModule(using_module);

    ui_manager.OpenPopup<OnStartPopup>(context);
}

void App::Events(const sf::Event &event)
{
    ImGui::SFML::ProcessEvent(GetWindow(), event);
}

void App::Update(float delta_time)
{
    ImGui::SFML::Update(GetWindow(), seconds(delta_time));
    context.delta_time = delta_time;

    CheckModuleChange();

    ui_manager.Update(context, *module);

    if(!(interface.popup_open || interface.show_settings_window))
        module->Update(context);

    grid_render.Update(grid);
}

void App::DrawCanvas()
{
    grid_render.Draw(GetWindow());
    grid_cursor.Draw(GetWindow(), grid_render);
    module->Draw(context);

    ImGui::SFML::Render(GetWindow());
}
void App::End()
{
    ImGui::SFML::Shutdown();
}