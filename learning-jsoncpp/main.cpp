#include <cstring>
#include <iostream>

#include "..\VyperDisplayManager\json.h"
#include "..\VyperDisplayManager\JsonObject.h"
#include "addressbook.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " COMMAND FILENAME" << endl
            << "COMMAND: 'load' or 'save'" << endl
            << "Load will load the JSON file, FILENAME, and print out its contents." << endl
            << "Save will save a sample address book to FILENAME in JSON format." << endl;
        return 1;
    }
    AddressBook address_book;
    if (strcmp(argv[1], "load") == 0) {
        address_book.JsonLoad(argv[2]);
        for (vector<Contact>::const_iterator it = address_book.contacts().begin(); it != address_book.contacts().end(); ++it) {
            cout << (*it).name() << "," << (*it).phone_number() << endl;
        }
    }
    else if (strcmp(argv[1], "save") == 0) {
        address_book.AddPerson("Alice", "111-222-3333");
        address_book.AddPerson("Bob", "555-444-3333");
        address_book.JsonSave(argv[2]);
    }
    return 0;
}