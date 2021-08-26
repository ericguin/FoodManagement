#include <iostream>
#include "database.hh"

int main(int argc, char** argv)
{
    Food::Database::FileSource dbFile{"food.json"};
    Food::Database yes{dbFile};
    
    // Food::Database::Item whee {
    //     "Grapes", "12345", "1 lb"
    // };
    // yes.UpdateItem(whee);

    {
        Food::Database::ItemRef item = yes.FindItem("Grapes");

        item.get()->Quantity = "yeet";
    }

    yes.Save(dbFile);

}