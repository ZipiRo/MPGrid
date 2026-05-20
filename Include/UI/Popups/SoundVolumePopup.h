class SoundVolumePopup : public Popup
{
private:
    float sound_volume;
    bool no_sound = false;

public:
    void Init(ApplicationContext &context) override
    {
        sound_volume = SoundPlayer::GetMasterVolume();
        
        if(sound_volume == 0.0f)
            no_sound = true;
    }

    void Interface(ApplicationContext &context) override
    {
        ImGui::SetWindowSize(ImVec2(280, 80));

        if(ImGui::Checkbox("No Sound", &no_sound))
        {
            if(no_sound) sound_volume = 0.0f;    
            else sound_volume = 100.0f;

            SoundPlayer::SetMasterVolume(sound_volume);
        }

        if(ImGui::IsItemHovered())
            ImGui::SetTooltip("Set the volume to 0");

        if(ImGui::SliderFloat("Volume", &sound_volume, 0.0f, 100.0f))
        {
            if(sound_volume == 0.0f) no_sound = true;
            else no_sound = false;

            SoundPlayer::SetMasterVolume(sound_volume);
        }
    }

    std::string GetName() override
    {
        return "Sound Volume";
    }
};