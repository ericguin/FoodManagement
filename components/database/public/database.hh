#pragma once
#include "nlohmann/json.hpp"
#include <cstring>
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

        class Batch
        {
        public:
            Batch() {}
            Batch(std::string quantity, std::string purchaseDate)
                : Quantity(quantity), PurchaseDate(purchaseDate) {}

            std::string Quantity;
            std::string PurchaseDate;

        };

        friend void to_json(nlohmann::json& j, const Batch& b)
        {
            j = nlohmann::json{
                {"Quantity", b.Quantity},
                {"PurchaseDate", b.PurchaseDate}
            };
        }

        friend void from_json(const nlohmann::json& j, Batch& b)
        {
            j.at("Quantity").get_to(b.Quantity);
            j.at("PurchaseDate").get_to(b.PurchaseDate);
        }
        
        class Item
        {
        public:
            Item() {}
            Item(std::string n)
                : Name(n) {}
            
            Item& operator=(const Item& rhs)
            {
                Name = rhs.Name;
                Batches = rhs.Batches;
                return *this;
            }

            std::string Name{};
            std::vector<Batch> Batches{};
        protected:
            friend class Database;
            std::string upperName() { return StringToUppercase(Name); }
        };

        friend void to_json(nlohmann::json& j, const Item& i)
        {
            j = nlohmann::json{
                {"Name", i.Name},
                {"Batches", i.Batches}
            };
        }
        
        friend void from_json(const nlohmann::json& j, Item& i)
        {
            j.at("Name").get_to(i.Name);
            j.at("Batches").get_to(i.Batches);
        }

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
        bool addOrUpdateItem(Item& item);

        nlohmann::json db;
    };
}
