class Interface
{
private:
    float menubar_height = 18;
    float sidebar_window_width;
    
    Vector2f settings_window_size;
    Vector2f settings_window_position;
    
    Vector2f modules_bar_position;

public:
    bool hide_interface = false;
    bool popup_open = false;

    bool show_sidebar_window = true;
    bool show_settings_window = false;

    void SetSettingsWindow(Vector2f position, Vector2f size)
    {
        settings_window_position = position;
        settings_window_size = size;
    }

    void SetModulesbar(Vector2f position)
    {
        modules_bar_position = position;
    }

    Vector2f GetSettingsWindowPosition()
    {
        return settings_window_position;
    }
    
    Vector2f GetSettingsWindowSize()
    {
        return settings_window_size;
    }

    Vector2f GetModulesbarPosition()
    {
        return modules_bar_position;
    }

    void SetSidebarWindow(float width)
    {
        sidebar_window_width = width;
    }

    float GetSidebarWidth()
    {
        return sidebar_window_width;
    }

    float GetMenubarHeight()
    {
        return menubar_height;
    }
};