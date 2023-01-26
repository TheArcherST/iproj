#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<string> split_csv_line(string line);

string join_csv_line(vector<string> data);


struct BaseModel {
    BaseModel();

    virtual void parse(const vector<string> data) = 0;
    virtual vector<string> dump() = 0;
};


template <class T>
class Database {
    static_assert(is_base_of<BaseModel, T>::value, "T must derive from BaseModel");

private:
    string filepath;
    vector<shared_ptr<T> > data;
    bool is_loaded;

public:
    Database(string filepath);

    int insert(shared_ptr<T> model);
    int insert(const T model);

    void load();
    void save();

    vector<shared_ptr<T> > get();
};
