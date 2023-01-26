#include "database.h"
#include "models.cpp"

#define random(A, B) (A + rand() % (B-A+1))


Database<AppearanceProp> load_props(string fp) {
    Database<AppearanceProp> result (fp);
    result.load();
    return result;
}


template <class T>
T choice(vector<T> vec) {
    return vec[random(0, vec.length())];
};


class PersonAppearance {
    
};


int main() {
    auto clothes = load_props("clothes.csv").get();
    auto shoes = load_props("shoes.csv").get();
    auto hairstyle = load_props("hairstyle.csv").get();

    
};
