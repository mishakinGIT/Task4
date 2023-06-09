#include "hashSet.h"
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

HashSet::HashSet()
{
    elements_count = 0;
    buckets.resize(100);
}

HashSet::HashSet(QString fileName)
{
    elements_count = 0;
    buckets.resize(100);
    string nextLine;
    ifstream myFile(fileName.toStdString());

    while (getline (myFile, nextLine)) {
        this->insert(nextLine);
    }
    myFile.close();
}

void HashSet::insert(const string& value)
{
    size_t bucket_index = hash_function(value);
    auto bucket = this->buckets[bucket_index];
    auto it = find(bucket.begin(), bucket.end(), value);
    if (it != bucket.end()) {
        return;
    }
    bucket.push_back(value);
    this->buckets[bucket_index] = bucket;
    elements_count++;
}

void HashSet::erase(const string& value)
{
    size_t bucket_index = hash_function(value);
    auto bucket = this->buckets[bucket_index];
    auto it = find(bucket.begin(), bucket.end(), value);
    if (it == bucket.end()) {
        return;
    }

    bucket.erase(it);
    this->buckets[bucket_index] = bucket;
    elements_count--;
}

bool HashSet::contains(const string& value)
{
    size_t bucket_index = hash_function(value);
    auto bucket = buckets[bucket_index];

    auto it = find(bucket.begin(), bucket.end(), value);
    return (it != bucket.end());
}

list<string> HashSet::getFlippersList()
{
    list<string> flippersList;
    auto it = this->begin();
    while (!(it == this->end()))
    {
        string word = *it;
        bool isFlipper = true;
        for(int i = 0; i < word.size() / 2; i++)
        {
            if (word[i] != word[word.size() - i - 1])
            {
               isFlipper = false;
               break;
            }
        }
        if (isFlipper)
        {
            flippersList.push_back(word);
        }
        it++;
    }
    return flippersList;
}

list<string> HashSet::getWordsLessFiveList()
{
    list<string> wordsLessFiveList;
    auto it = this->begin();
    while (!(it == this->end()))
    {
        if ((*it).size() < 5)
        {
            wordsLessFiveList.push_back(*it);
        }
        it++;
    }
    return wordsLessFiveList;
}

bool HashSet::empty()
{
    return (size() == 0);
}

size_t HashSet::size()
{
    return elements_count;
}


size_t HashSet::hash_function(const string& value) const
{
    hash<string> hash_func;
    size_t hash = hash_func(value);
    return hash % buckets.size();
}

string HashSet::toString() {
    stringstream ss;
    auto it = this->begin();
    bool first = true;
    while (!(it == this->end()))
    {
        if (!first)
        {
            ss << endl;
        }
        ss << *it;
        it++;
        first = false;
    }
    return ss.str();
}

