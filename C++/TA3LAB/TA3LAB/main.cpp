#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "BTREE.h"
#include "autoFill.h"

using namespace std;

vector<string> *FILES = new vector<string>;

string hashKey(string str)
{
    for (int i=0; i <str.size(); i++) str[i] = str[i]+3;
    return str;
}

bool remove_line(string filename, size_t index)
{
    std::vector<std::string> vec;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string str;
        while (std::getline(file, str))
            vec.push_back(str);
        file.close();
        if (vec.size() < index)
            return false;
        vec.erase(vec.begin() + index);
        std::ofstream outfile(filename);
        if (outfile.is_open())
        {
            std::copy(vec.begin(), vec.end(),
                      std::ostream_iterator<std::string>(outfile, "\n"));
            outfile.close();
            return true;
        }
        return false;
    }
    return false;
}

void addDB(Tree *BTREE, string data)
{
    if(BTREE->search(hashKey(data))) cout << "DataBase already has this el." << endl;
    else
    {
        BTREE->insert(hashKey(data));
        BNode *node = BTREE->getBNode(hashKey(data));
        if (node->nameOfFile == "")
        {
            node->nameOfFile = "/Applications/data/TA3LAB/TA3LAB/DB/" + hashKey(data) + ".txt";
            FILES->push_back("/Applications/data/TA3LAB/TA3LAB/DB/" + hashKey(data) + ".txt");
        }
        ofstream outFile;
        outFile.open(node->nameOfFile, ios_base::app);
        outFile << hashKey(data) << " " << data << "\n";
        outFile.close();
    }
}

vector<vector<string> > getStrings(string FileName)
{
    vector<vector<string> > Numbers;
    ifstream infile(FileName.c_str());
    string String;
    string a;
    while (getline(infile, String)) {
        vector<string> Line;
        stringstream Stream(String);
        while (Stream >> a) Line.push_back(a);
        Numbers.push_back(Line);
    }
    return Numbers;
}

void getDb(Tree *BTREE, string data)
{
    if(!BTREE->search(hashKey(data))) cout << "DataBase does not have this el." << endl;
    else
    {
        BNode *node = BTREE->getBNode(hashKey(data));
        int index = 0;
        for (int i = 0; i < sizeof(node->keys)/sizeof(string); i++)
        {
            if (node->keys[i] == hashKey(data))
            {
                index = i;
                break;
            }
        }
        vector<vector<string>> file = getStrings(node->nameOfFile);
        cout << file[index][1] << endl;
    }
}

void delDB(Tree *BTREE, string data)
{
    if(!BTREE->search(hashKey(data))) cout << "DataBase does not have this el." << endl;
    else
    {
        BNode *node = BTREE->getBNode(hashKey(data));
        int index = 0;
        for (int i = 0; i < sizeof(node->keys)/sizeof(string); i++)
        {
            if (node->keys[i] == hashKey(data))
            {
                index = i;
                cout << "found!" << endl;
                break;
            }
        }
        remove_line(node->nameOfFile, index);
    }
}

void fromDiskToRam(Tree * BTREE)
{
    for (auto i = FILES->begin(); i != FILES->end(); i++)
    {
        vector<vector<string>> infile = getStrings(*i);
        for (auto j = infile.begin(); j != infile.end(); j++) addDB(BTREE, (*j)[1]);
    }
}


void AutoFill(Tree *BTREE, int amount) { for (int i = 0; i < amount; i++) addDB(BTREE, random_string(10)); }

int main()
{
    Tree BTREE = Tree();
    if (FILES->size() != 0) fromDiskToRam(&BTREE);
//    AutoFill(&BTREE, 20);
    delDB(&BTREE, "Q9wQj99nsQ");
    cout << FILES->size() << endl;
    return 0;
}
