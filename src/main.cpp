#include "database.cpp"
#include "models.cpp"
#include <iostream>
#include <set>

#define random(A, B) (A + rand() % (B-A+1))

using namespace std;


template <class T>
T choice(vector<T> &vec) {
    if (!vec.size()) throw runtime_error("Vector is empty");
    return vec[random(0, vec.size()-1)];
};


template <class T>
void vec_union(vector<T> &v1, vector<T> &v2) {
    v1.reserve(v1.size() + distance(v2.begin(),v2.end()));
    v1.insert(v1.end(),v2.begin(),v2.end());
};


class Actor {
    vector<shared_ptr<ActorAppearanceProperty> > appearance;

public:

    void gen_random_appearance(Database<AppearanceEquipment> &eq_db,
                               Database<Color> &color_db) {

        string gender = random(0, 1) ? "male" : "female";

        AppearanceEquipment q;
        q.gender = StringField(gender, QueryMode::EQUAL);
        auto all_equipment = eq_db.find(q);
        q.gender = StringField("universal", QueryMode::EQUAL);
        auto universal_equipment = eq_db.find(q);
        vec_union(all_equipment, universal_equipment);
        Database<AppearanceEquipment> all_possible_equipment ("");
        all_possible_equipment.set(all_equipment);

        set<string> eq_types;
        vector<shared_ptr<ActorAppearanceProperty> > result;
        AppearanceEquipment q2;

        for (auto eq : all_possible_equipment.get()) {
            eq_types.insert(*(eq->type.value));
        }
        for (string eq_type : eq_types) {
            q2.type = StringField(eq_type);
            auto sel = all_possible_equipment.find(q2);
            auto eq_elem = choice(sel);
            Color color_q;
            color_q.equipment_type = StringField(*(eq_elem->type.value));
            auto sel2 = all_possible_equipment.find(q2);
            auto color_elem = choice(sel2);

            shared_ptr<ActorAppearanceProperty> elem = (shared_ptr<ActorAppearanceProperty>) new ActorAppearanceProperty();
            elem->apr_prop_id = eq_elem->id;

            if (eq_elem->is_color_requested.value) {
                elem->color_id = color_elem->id;
            }

            result.push_back(elem);
        }

        this->appearance = result;
    }

    vector<shared_ptr<ActorAppearanceProperty> > getApr() {
        return this->appearance;
    }
};


int main() {
    srand(time(NULL));

    Database<AppearanceEquipment> eqipment_db ("/Users/mihailsapovalov/Desktop/C++/ta-exam-proj/db.csv");
    eqipment_db.load();

    Database<Color> colors_db ("/Users/mihailsapovalov/Desktop/C++/ta-exam-proj/colors.csv");
    colors_db.load();

    Actor a;
    a.gen_random_appearance(eqipment_db, colors_db);

    auto  apr = a.getApr();
    for (auto i : apr) {
        AppearanceEquipment eq_q;
        eq_q.id = i->apr_prop_id;
        Color color_q;
        color_q.id = IntField(*(i->color_id.value), QueryMode::EQUAL);
        auto eqipment = eqipment_db.find_one(eq_q);
        cout << *(eqipment->name.value) << endl;
        if (i->color_id.value != nullptr) {
            auto color = colors_db.find_one(color_q);
            cout << *(color->color.value) << endl;
        }
        cout << endl;
     }
};
