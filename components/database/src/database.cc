#include "database.hh"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace Food
{
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

    Database::Database(Source& Source)
    {
        std::string s = Source.Read();
        db = nlohmann::json::parse(s);
        initDb();
    }
    
    bool Database::initDb()
    {
        if (!db.contains("largest_id"))
        {
            db["largest_id"] = 1;
            db["items"] = nlohmann::json::array();
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
        assignId(item);

        addOrUpdateItem(item);

        return true;
    }
    
    unsigned long long Database::assignId(Database::Item& item)
    {
        if (item.Id == 0)
        {
            item.Id = db["largest_id"].get<unsigned long long>();
            db["largest_id"] = db["largest_id"].get<unsigned long long>() + 1;
        }

        return db["largest_id"].get<unsigned long long>();
    }
    
    bool Database::addOrUpdateItem(Database::Item& item)
    {
        for (auto& val : db["items"].items())
        {
            if (val.value()["Id"] == item.Id)
            {
                val.value() = item;
                return true;
            }
        }
        
        db["items"].push_back(item);
        
        return false;
    }
    
    bool Database::Save(Database::Source& Source)
    {
        std::string json = db.dump();
        return Source.Write(json);
    }
    
    Database::ItemRef Database::FindItem(std::string name)
    {
        ItemRef ret;
        
        ret.onExpire = [this](Database::Item& i) { this->addOrUpdateItem(i); };

        for (auto& val : db["items"].items())
        {
            if (val.value()["Name"] == name)
            {
                ret = val.value().get<Database::Item>();
                break;
            }
        }
        
        return ret;
    }
    
    Database::~Database()
    {
    }
}