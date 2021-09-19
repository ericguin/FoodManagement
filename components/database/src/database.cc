#include "database.hh"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

namespace Food
{
    std::string StringToUppercase(std::string& in)
    {
        std::string upper = in;
        std::transform(in.begin(), in.end(), upper.begin(), ::toupper);
        return upper;
    }
    
    Database::FileSource::FileSource(std::string FileName)
        : fileName(FileName) { }

    std::string Database::FileSource::Read()
    {
        std::stringstream ss;
        std::ifstream file(fileName);
        
        if (file.is_open())
        {
            ss << file.rdbuf();
        }
        else
        {
            ss << "{}";
        }

        return ss.str();
    }
    
    bool Database::FileSource::Write(std::string& contents)
    {
        std::ofstream file(fileName);
        
        if (file.is_open())
        {
            file << contents;
            return true;
        }

        return false;
    }

    Database::Database()
    {
    }
    
    bool Database::initDb()
    {
        if (!db.contains("items"))
        {
            db["items"] = nlohmann::json::object();
        }

        return true;
    }
    
    std::vector<Database::ItemRef> Database::GetAllItems()
    {
        std::vector<Database::ItemRef> ret;

        for (auto& val : db["items"].items())
        {
            ItemRef it;
            it = val.value().get<Database::Item>();
            ret.push_back(it);
        }
        
        return ret;
    }
    
    bool Database::UpdateItem(Database::Item& item)
    {
        addOrUpdateItem(item);

        return true;
    }
    
    bool Database::addOrUpdateItem(Database::Item& item)
    {
        std::string upper_name = item.upperName();
        db["items"][upper_name] = item;

        return false;
    }
    
    bool Database::Save(Database::Source& Source)
    {
        std::string json = db.dump();
        return Source.Write(json);
    }
    
    bool Database::Load(Database::Source& Source)
    {
        std::string s = Source.Read();
        
        if (s != "")
        {
            db = nlohmann::json::parse(s);
            initDb();
            return true;
        }

        return false;
    }
    
    Database::ItemRef Database::FindItem(std::string name)
    {
        ItemRef ret;
        std::string upper = StringToUppercase(name);
        
        ret.onExpire = [this](Database::Item& i) { this->addOrUpdateItem(i); };
        
        if (db["items"].contains(upper))
        {
            ret = db["items"][upper].get<Database::Item>();
        }

        return ret;
    }
    
    Database::~Database()
    {
    }
}
