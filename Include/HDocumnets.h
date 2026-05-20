class HDocumnets
{
private:
    HDocumnets() {}

public:
    static Resource<std::string> Document;

    static bool LoadDocument(std::string name, std::string path)
    {
        if(!std::filesystem::exists(path)) return false;

        Document.Insert(name, path);

        return false;
    }
};

Resource<std::string> HDocumnets::Document;