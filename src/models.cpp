#include "database.h"
 


template <class T>
T choice(vector<T> vec) {
    return vec[random(0, vec.length())];
};


struct AppearanceProperty : public BaseModel {
    StringField name;
    StringField gender;
    StringField type;

    void parse(const vector<string> data, int &__pos)
    {
        BaseModel::parse(data, __pos);
        this->name = StringField(data[__pos++]);
        this->gender = StringField(data[__pos++]);
        this->type = StringField(data[__pos++]);
    }

    bool match_query(const shared_ptr<AppearanceProperty> query)
    {
        return (
            BaseModel::match_query(query)
            && this->name.match_query(query->name)
            && this->gender.match_query(query->gender)
            && this->type.match_query(query->type)
            );
    }

        vector<string> dump()
        {
            vector<string> result;
            result.push_back(this->id.dump());
            result.push_back(this->name.dump());
            result.push_back(this->gender.dump());
            result.push_back(this->type.dump());
            return result;
        }
};
