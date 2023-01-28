#include "database.cpp"
#include "models.cpp"
#include <iostream>


#define random(A, B) (A + rand() % (B-A+1))

using namespace std;


int main() {
    Database<AppearanceProperty> db ("/Users/mihailsapovalov/Desktop/C++/ta-exam-proj/db.csv");
    db.load();

    AppearanceProperty query;
    query.gender = StringField("female", QueryMode::NOT_EQUAL);
    query.id = IntField(1, QueryMode::EQUAL);

    auto res = db.find_one(query);

    if (res == nullptr) {
        cout << "User nof found";
    } else {
        cout << *res->name.value;
    }
};
