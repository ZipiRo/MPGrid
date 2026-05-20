#include "Popups/Popup.h"

class InterfaceManager
{
private:
    Vector2f grid_offset;

    std::unique_ptr<Popup> popup;

    void Menubar(ApplicationContext &);
    void Bottombar(ApplicationContext &);
    void Modulesbar(ApplicationContext &);

    void SidebarWindowBase(std::string title, ApplicationContext &context, std::function<void(ApplicationContext &)> Interface)
    {
        Vector2u window_size = context.window.getSize();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowPos(ImVec2(window_size.x - context.interface.GetSidebarWidth(), context.interface.GetMenubarHeight()), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(context.interface.GetSidebarWidth(), window_size.y - context.interface.GetMenubarHeight() * 2), ImGuiCond_Always);

        ImGui::Begin(title.c_str(), nullptr, flags);

        Interface(context);

        ImGui::End();
    }

    void SettingsWindowBase(std::string title, ApplicationContext &context, std::function<void(ApplicationContext &)> Interface)
    {
        if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Escape))
        {
            context.interface.show_settings_window = false;
            return;
        }

        Vector2u window_size = context.window.getSize();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowSize(ImVec2(context.interface.GetSettingsWindowSize().x, context.interface.GetSettingsWindowSize().y), ImGuiCond_Always);

        ImGui::Begin(title.c_str(), &context.interface.show_settings_window, flags);

        if (ImGui::IsWindowHovered()) context.grid_cursor.enabled = false;
    
        Interface(context);

        ImGui::End();
    }

    void InfoWindowBase(std::string title, ApplicationContext &context, std::function<void(ApplicationContext &)> Interface)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowSize(ImVec2(context.interface.GetInfoWindowSize().x, context.interface.GetInfoWindowSize().y), ImGuiCond_Always);

        ImGui::Begin(title.c_str(), &context.interface.show_info_window, flags);

        if (ImGui::IsWindowHovered()) context.grid_cursor.enabled = false;

        Interface(context);

        ImGui::End();
    }

    void PopupBase(Popup &popup, ApplicationContext &context)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoCollapse;

        if (ImGui::IsKeyDown(ImGuiKey_Escape))
        {
            popup.open = false;
            return;
        }

        ImGui::SetNextWindowPos(ImVec2(context.window.getSize().x / 2, context.window.getSize().y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin(popup.GetName().c_str(), &popup.open, flags);

        popup.Interface(context);

        ImGui::End();
    }

    template <typename T>
    void OpenPopup(ApplicationContext &context)
    {
        popup = std::make_unique<T>();
        popup->Init(context);
    }

    bool ShowPopup(ApplicationContext &context)
    {
        if (!popup)
            return false;

        if (popup->open)
        {
            PopupBase(*popup, context);
            return true;
        }
        else
            popup = nullptr;

        return false;
    }

    void UpdateToolUI(ApplicationContext &context, Module &active)
    {
        if (Input::IsKeyDown(Keyboard::Key::Tab))
            context.interface.show_sidebar_window = !context.interface.show_sidebar_window;

        if (Input::IsKeyDown(Keyboard::Key::LShift))
            context.interface.show_settings_window = !context.interface.show_settings_window;

        if (Input::IsKeyDown(Keyboard::Key::I))
            context.interface.show_info_window = !context.interface.show_info_window;

        Modulesbar(context);

        if (context.interface.show_sidebar_window)
        {
            SidebarWindowBase(active.GetSidebarTitle(), context, [&](ApplicationContext &) { return active.SidebarInterface(context); });

            grid_offset.x = -context.interface.GetSidebarWidth();
        }

        if (context.interface.show_settings_window)
        {
            SettingsWindowBase(active.GetSettingsTitle(), context, [&](ApplicationContext &) { return active.SettingsInterface(context); });
            return;
        }

        if (context.interface.show_info_window)
            InfoWindowBase(active.GetInfoTitle(), context, [&](ApplicationContext &) { return active.InfoInterface(context); });
    }

public:
    void Update(ApplicationContext &context, Module &active)
    {
        context.interface.popup_open = ShowPopup(context);

        if (context.interface.popup_open)
        {
            context.grid_render.SetOffset(Vector2f(0, 0));
            return;
        }

        if (Input::IsKeyDown(Keyboard::Key::H))
            context.interface.hide_interface = !context.interface.hide_interface;

        grid_offset = Vector2f(0, 0);

        if (context.interface.hide_interface)
        {
            context.grid_render.SetOffset(Vector2f(0, 0));
            return;
        }

        Menubar(context);
        Bottombar(context);

        grid_offset.y = 0;
        context.grid_cursor.enabled = true;

        UpdateToolUI(context, active);
        context.grid_render.SetOffset(grid_offset);
    }
};

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

    if (ImGui::BeginMenu("Settings"))
    {
        if (ImGui::MenuItem("Background Color"))
            OpenPopup<SetBackgroundPopup>(context);

        if(ImGui::MenuItem("Sound Volume"))
            OpenPopup<SoundVolumePopup>(context);

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("Keybinds"))
            OpenPopup<ShowKeybindsPopup>(context);

        if(ImGui::MenuItem("Documentation"))
            StartHDocument(HDocumnets::Document.Get("Main"));

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

#include "BottombarUI.h"
#include "ModulesbarUI.h"