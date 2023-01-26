#include "database.h"


vector<string> split_csv_line(string line)
{
    vector<string> result;
    string curr;

    for (char ch : line) {
        switch (ch)
        {
        case ',':
            result.push_back(curr);
            curr.clear();
            break;
        case '\n':
            // nope
            break;
        default:
            curr += ch;
            break;
        }
    }
    result.push_back(curr);
    return result;
}


string join_csv_line(vector<string> data)
{
    string result;

    for (int i = 0; i < data.size(); i++) {
        result += data[i] + ",";
    }

    return result;
}


BaseModel::BaseModel() {}


template <class T>
Database<T>::Database(string filepath)
{
    this->filepath = filepath;
    this->is_loaded = false;
}


template <class T>
int Database<T>::insert(shared_ptr<T> model)
{
    if (model->id == nullptr) {
        model->id = (shared_ptr<int>) new int (this->data.size());
    }

    this->data.push_back(model);

    return *model->id;
}


template <class T>
int Database<T>::insert(const T model)
{
    shared_ptr<T> prepared = (shared_ptr<T>) new T (model);
    return this->insert(prepared);
}


template <class T>
void Database<T>::load()
{
    this->data.clear();

    fstream stream (this->filepath);

    if (!stream.is_open()) {
        throw runtime_error("Can't open database file");
    }

    string buffer;

    while (getline(stream, buffer)) {
        vector<string> data = split_csv_line(buffer);

        shared_ptr<T> model (new T());

        int pos = 0;
        model->parse(data, pos);

        this->data.push_back(model);
    }

    this->is_loaded = true;
}


template <class T>
void Database<T>::save()
{
    fstream stream (this->filepath);

    if (!stream.is_open()) {
        throw runtime_error("Can't open database file");
    }

    for (shared_ptr<T> current : this->data) {
        stream << join_csv_line(current->dump()) << "\n";
    }
}


template <class T>
vector<shared_ptr<T> > Database<T>::get()
{
    return this->data;
}
