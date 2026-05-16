struct Module
{
    virtual void Init(ApplicationContext&) {}
    virtual void Update(ApplicationContext&) = 0;
    virtual void Draw(ApplicationContext&) {}

    virtual void SidebarInterface(ApplicationContext&) {}
    virtual void SettingsInterface(ApplicationContext&) {}
    virtual void InfoInterface(ApplicationContext&) {}

    virtual std::string GetSidebarTitle() { return "Sidebar"; };
    virtual std::string GetSettingsTitle() { return "Settings"; };
    virtual std::string GetInfoTitle() { return "Info"; };
};

struct ModuleEntry
{
    std::string name;
    std::string tooltip;
    std::string texture_name;
    Keyboard::Key open_key;
    std::function<std::unique_ptr<Module>()> Get; 
};

#include "Topo.h"
#include "Pathfinder.h"
#include "Mazer.h"

std::vector<ModuleEntry> GetModules()
{
    std::vector<ModuleEntry> modules;
    ModuleEntry module_entry;

    module_entry.name = "Topo";
    module_entry.tooltip = "A kind of paint but you draw and remove walls";
    module_entry.open_key = Keyboard::Key::Num1;
    module_entry.texture_name = "Map";
    module_entry.Get = []() { return std::make_unique<Topo>(); };
    modules.push_back(module_entry);
    
    module_entry.name = "Pathfinder";
    module_entry.tooltip = "Module that helps you to find paths from two points";
    module_entry.open_key = Keyboard::Key::Num2;
    module_entry.texture_name = "Path";
    module_entry.Get = []() { return std::make_unique<Pathfinder>(); };
    modules.push_back(module_entry);

    module_entry.name = "Mazer";
    module_entry.tooltip = "Module that helps you to creat mazes";
    module_entry.open_key = Keyboard::Key::Num3;
    module_entry.texture_name = "Maze";
    module_entry.Get = []() { return std::make_unique<Mazer>(); };
    modules.push_back(module_entry);

    return modules;
}