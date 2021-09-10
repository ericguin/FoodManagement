#include <iostream>
#include "database.hh"
#include "units.hh"

int main(int argc, char** argv)
{
    Food::Database::FileSource dbFile{"food.json"};
    Food::Database yes{dbFile};
    
    Food::Database::Item whee {
        "Grapes"
    };

    whee.Batches.push_back({
        "yeah", "yesterday"
    });

    yes.UpdateItem(whee);

    {
        Food::Database::ItemRef item = yes.FindItem("Grapes");

        item->Batches[0].Quantity = "less than it was before";
    }

    yes.Save(dbFile);
}
