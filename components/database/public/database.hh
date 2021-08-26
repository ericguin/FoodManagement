#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace Food
{
    std::string StringToUppercase(std::string& in);

    class Database
    {
    public:
        class Source
        {
        public:
            virtual std::string Read() = 0;
            virtual bool Write(std::string& contents) = 0;
        protected:
            virtual ~Source() = default;
        };
        
        class FileSource : public Source
        {
        public:
            FileSource(std::string FileName);
            ~FileSource() = default;
            std::string Read();
            bool Write(std::string& contents);
        private:
            std::string fileName;
        };

        Database(Source& Source);
        ~Database();
        
        class Item
        {
        public:
            Item() {};
            Item(std::string n, std::string b, std::string q)
                : Name(n), Barcode(b), Quantity(q) {}
            
            Item& operator=(const Item& rhs)
            {
                Name = rhs.Name;
                Barcode = rhs.Barcode;
                Quantity = rhs.Quantity;
                Id = rhs.Id;
                return *this;
            }

            std::string Name{};
            std::string Barcode{};
            std::string Quantity{};
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Item, Id, Name, Barcode, Quantity);
        protected:
            friend class Database;
            unsigned long long Id{0};
            std::string upperName() { return StringToUppercase(Name); }
        };
        
        class ItemRef : public std::shared_ptr<Item>
        {
        public:
            ItemRef() : std::shared_ptr<Item>(nullptr) {}
            
            ItemRef& operator=(const Item& rhs)
            {
                reset(new Item());
                *get() = rhs;
                return *this;
            }
            
            ~ItemRef()
            {
                if (use_count() == 1)
                {
                    onExpire(*get());
                }
            }

        protected:
            friend class Database;
            std::function<void(Item&)> onExpire;
        };

        std::vector<ItemRef> GetAllItems();
        ItemRef FindItem(std::string name);

        bool UpdateItem(Item& item);
        bool Save(Source& Source);

    private:
        bool initDb();
        unsigned long long assignId(Item& item);
        bool addOrUpdateItem(Item& item);

        nlohmann::json db;
    };
}