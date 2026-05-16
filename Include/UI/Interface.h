class Interface
{
private:
    float menubar_height = 18;
    float sidebar_width;

    Vector2f settings_window_size;
    Vector2f info_window_size;
    Vector2f modulesbar_position;
public:
    bool hide_interface = false;
    bool popup_open = false;

    bool show_sidebar_window = true;
    bool show_settings_window = false;
    bool show_info_window = false;
    
    void SetSettingsWindow(Vector2f size)
    {
        settings_window_size = size;
    }

    void SetInfoWindow(Vector2f size)
    {
        info_window_size = size;
    }

    void SetModulesbar(Vector2f position)
    {
        modulesbar_position = position;
    }

    Vector2f GetSettingsWindowSize()
    {
        return settings_window_size;
    }

    Vector2f GetInfoWindowSize()
    {
        return info_window_size;
    }

    Vector2f GetModulesbarPosition()
    {
        return modulesbar_position;
    }

    void SetSidebarWindow(float width)
    {
        sidebar_width = width;
    }

    float GetSidebarWidth()
    {
        return sidebar_width;
    }

    float GetMenubarHeight()
    {
        return menubar_height;
    }
};