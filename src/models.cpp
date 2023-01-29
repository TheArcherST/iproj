#include "database.h"



struct AppearanceEquipment : public BaseModel {
    StringField type;
    StringField name;
    StringField gender;
    IntField is_color_requested;
    StringField url;

    void parse(const vector<string> data, int &__pos)
    {
        BaseModel::parse(data, __pos);
        this->type = StringField(data[__pos++]);
        this->name = StringField(data[__pos++]);
        this->gender = StringField(data[__pos++]);
        this->is_color_requested = IntField(data[__pos++]);
        this->url = StringField(data[__pos++]);
    }

    bool match_query(const shared_ptr<AppearanceEquipment> query)
    {
        return (
            BaseModel::match_query(query)
            && this->type.match_query(query->type)
            && this->name.match_query(query->name)
            && this->gender.match_query(query->gender)
            && this->is_color_requested.match_query(query->is_color_requested)
            && this->url.match_query(query->url)
            );
    }

    vector<string> dump()
    {
        vector<string> result;
        result.push_back(this->id.dump());
        result.push_back(this->type.dump());
        result.push_back(this->name.dump());
        result.push_back(this->gender.dump());
        result.push_back(this->is_color_requested.dump());
        result.push_back(this->url.dump());
        return result;
    }
};


struct Color : public BaseModel {
    StringField equipment_type;
    StringField color;

    void parse(const vector<string> data, int &__pos)
    {
        BaseModel::parse(data, __pos);
        this->equipment_type = StringField(data[__pos++]);
        this->color = StringField(data[__pos++]);
    }

    bool match_query(const shared_ptr<Color> query)
    {
        return (
            BaseModel::match_query(query)
            && this->equipment_type.match_query(query->equipment_type)
            && this->color.match_query(query->color)
            );
    }

    vector<string> dump()
    {
        vector<string> result;
        result.push_back(this->id.dump());
        result.push_back(this->equipment_type.dump());
        result.push_back(this->color.dump());
        return result;
    }
};


struct ActorAppearanceProperty : public BaseModel {
    IntField apr_prop_id;
    IntField color_id;

    void parse(const vector<string> data, int &__pos)
    {
        BaseModel::parse(data, __pos);
        this->apr_prop_id = IntField(data[__pos++]);
        this->color_id = IntField(data[__pos++]);
    }

    bool match_query(const shared_ptr<ActorAppearanceProperty> query)
    {
        return (
            BaseModel::match_query(query)
            && this->apr_prop_id.match_query(query->apr_prop_id)
            && this->color_id.match_query(query->color_id)
            );
    }

    vector<string> dump()
    {
        vector<string> result;
        result.push_back(this->id.dump());
        result.push_back(this->apr_prop_id.dump());
        result.push_back(this->color_id.dump());
        return result;
    }
};
