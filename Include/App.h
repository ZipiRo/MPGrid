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

#include <imgui.h>
#include <imgui-SFML.h>

using namespace sf;

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
        if(index < 0 || index >= GetModules().size())    
            return;

        change_module = true;
        using_module = index;
    }

    void CheckModuleChange()
    {
        if(!change_module) return;

        module = GetModules()[using_module].Get();
        module->Init(context);
        
        context.using_module = using_module;
        change_module = false;
    }

public:
    App() : Application(sf::Vector2u(1600, 900), "MPGrid") 
    {
        window.setFramerateLimit(999999);
    }

    Grid grid;
    GridRenderer grid_render;
    GridCursor grid_cursor;
    Interface interface;

    std::unique_ptr<Module> module;
    bool change_module = false;
    int using_module = 0;


    ApplicationContext context { 
        .window = window, 
        .grid = grid, 
        .grid_render = grid_render, 
        .grid_cursor = grid_cursor, 
        .interface = interface,
        .SetModule = [this](int index) { ChangeModule(index); }
    };

    InterfaceManager ui_manager;

    void Start() override;
    void End() override;
    void Events(const Event &event) override;
    void Update(float delta_time) override;
    void DrawCanvas() override;
};

bool LoadResources()
{
    if(!ResourceManager::LoadSound("Place", "Resources/Audio/place.wav")) return false;
    if(!ResourceManager::LoadSound("Pop", "Resources/Audio/pop.wav")) return false;
    if(!ResourceManager::LoadSound("Find", "Resources/Audio/find.wav")) return false;
    if(!ResourceManager::LoadSound("Remove", "Resources/Audio/remove.wav")) return false;

    if(!ResourceManager::LoadTexture("Map", "Resources/Textures/map.png")) return false;
    if(!ResourceManager::LoadTexture("Path", "Resources/Textures/path.png")) return false;
    if(!ResourceManager::LoadTexture("Maze", "Resources/Textures/maze.png")) return false;

    return true;
}

void App::Start()
{
    if(!ImGui::SFML::Init(window)) 
    {
        window.close();
        return;
    }

    if(!LoadResources())
    {
        window.close();
        return;
    } 
    
    srand(time(0));
    background = Color::Black;

    grid.Create(20, 20);
    grid_render.SetMaxLength(Vector2f(window.getSize().y - 70, window.getSize().y - 70));
    grid_render.Build(grid.GetSize()); 
    grid_render.SetPosition(Vector2f(window.getSize().x / 2 - grid_render.GetLength().x / 2, window.getSize().y / 2 - grid_render.GetLength().y / 2));
    grid_cursor.Init(grid_render.GetCellSize());

    interface.SetSettingsWindow(Vector2f(100, 100), Vector2f(window.getSize().x * 0.4f, window.getSize().y * 0.5f));
    interface.SetModulesbar(Vector2f(10, 30));
    interface.SetSidebarWindow(window.getSize().x * 0.2f);

    ChangeModule(using_module);
}

void App::Events(const sf::Event &event)
{
    ImGui::SFML::ProcessEvent(window, event);
}

void App::Update(float delta_time)
{
    ImGui::SFML::Update(window, seconds(delta_time));
    context.delta_time = delta_time;

    CheckModuleChange();

    ui_manager.Update(context, *module);

    module->Update(context);

    grid_render.Update(grid);
}

void App::DrawCanvas()
{
    grid_render.Draw(window);
    grid_cursor.Draw(window, grid_render);
    module->Draw(context);

    ImGui::SFML::Render(window);
}
void App::End()
{
    ImGui::SFML::Shutdown();
} 