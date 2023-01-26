#include "database.h"
 


template <class T>
T choice(vector<T> vec) {
    return vec[random(0, vec.length())];
};


struct AppearanceAttr {
    string name;
    string color;

    vector<string> dump() {
        vector<string> result;
        result.push_back(this->name);
        result.push_back(this->color);
        return result;
    }
};


struct Appearance : public BaseModel {
    shared_ptr<string> gender;
    shared_ptr<AppearanceAttr> hair;
    shared_ptr<AppearanceAttr> lips;
    shared_ptr<AppearanceAttr> eyelashes;
    shared_ptr<AppearanceAttr> torso;
    shared_ptr<AppearanceAttr> clothes_1;
    shared_ptr<AppearanceAttr> clothes_2;
    shared_ptr<AppearanceAttr> clothes_3;
    shared_ptr<AppearanceAttr> shoes;

    Appearance(string gender) {
        this->gender = make_shared<string>(gender);
    }

    void parse(vector<string> data) {
        int pos = 0;

        this->gender = make_shared<string>(data[pos++]);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->hair = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->lips = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->eyelashes = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->torso = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->clothes_1 = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->clothes_2 = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->clothes_3 = make_shared<AppearanceAttr> (buf);

        AppearanceAttr buf{data[pos++], data[pos++]};
        this->shoes = make_shared<AppearanceAttr> (buf);
    };

    vector<string> dump() {
        vector<string> result;
        vector<string> buf;
        #define flush() result.insert(result.end(), buf.begin(), buf.end())
        result.push_back(*this->gender);

        buf = this->hair->dump();
        flush();
        buf = this->lips->dump();
        flush();
        buf = this->eyelashes->dump();
        flush();
        buf = this->torso->dump();
        flush();
        buf = this->clothes_1->dump();
        flush();
        buf = this->clothes_2->dump();
        flush();
        buf = this->clothes_3 ->dump();
        flush();
        buf = this->shoes->dump();
        flush();
    }
};


struct AppearanceProp : public BaseModel {
    shared_ptr<string> name;
    shared_ptr<string> url;
    shared_ptr<string> gener;

    AppearanceProp() : name(nullptr), url(nullptr), gener(nullptr) {};

    void parse(vector<string> data) {
        this->name = make_shared<string>(data[0]);
        this->url = make_shared<string>(data[1]);
        this->gener = make_shared<string>(data[2]);
    };

    vector<string> dump() {
        vector<string> result;
        result.push_back(*this->name);
        result.push_back(*this->url);
        result.push_back(*this->gener);
    }
};


struct AppearancePropColor : public BaseModel {
    shared_ptr<string> prop_name;
    shared_ptr<string> value;

    AppearancePropColor() : prop_name(nullptr), value(nullptr) {};

    void parse(vector<string> data) {
        this->prop_name = make_shared<string>(data[0]);
        this->value = make_shared<string>(data[1]);
    }

    vector<string> dump() {
        vector<string> result;
        result.push_back(*this->prop_name);
        result.push_back(*this->value);
    }
};
