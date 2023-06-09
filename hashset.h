#pragma once
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <QLabel>
#include <QList>

using namespace std;

class HashSet
{
public:
    HashSet();
    HashSet(QString fileName);

    void insert(const string& value);
    void erase(const string& value);
    bool contains(const string& value);
    list<string> getFlippersList();
    list<string> getWordsLessFiveList();

    bool empty();
    size_t size();
    string toString();
    class Iterator
    {
    public:
        Iterator(vector<list<string>>::iterator bucket_iterator, list<string>::iterator element_iterator,
                 vector<list<string>>::iterator bucket_end): bucket_iterator(bucket_iterator),
                 element_iterator(element_iterator), buckets_end(bucket_end) {}

        Iterator(const Iterator& other):
                bucket_iterator(other.bucket_iterator),
                element_iterator(other.element_iterator),
                buckets_end(other.buckets_end) {}

        Iterator& operator=(const Iterator& other) {
            bucket_iterator = other.bucket_iterator;
            element_iterator = other.element_iterator;
            return *this;
        }

        Iterator& operator++() {
            element_iterator++;
            if (element_iterator == bucket_iterator->end()) {
                bucket_iterator++;
                while (bucket_iterator != buckets_end && bucket_iterator->empty()) {
                    bucket_iterator++;
                }
                if (bucket_iterator != buckets_end) {
                    element_iterator = bucket_iterator->begin();
                }
                else {
                    element_iterator = typename list<string>::iterator();
                }
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) {
            return (bucket_iterator == other.bucket_iterator && element_iterator == other.element_iterator);
        }

        string operator*() {
            return *element_iterator;
        }

    private:
        vector<list<string>>::iterator bucket_iterator;
        vector<list<string>>::iterator buckets_end;
        list<string>::iterator element_iterator;
        friend class HashSet;
    };

    Iterator begin()
    {
        auto bucket = find_if_not(buckets.begin(), buckets.end(), [](const list<string>& bucket) {
            return bucket.empty();
        });
        if (bucket == buckets.end()) {
            return end();
        }
        auto element = bucket->begin();
        return Iterator(bucket, element, buckets.end());
    };

    Iterator end()
    {
        return Iterator(buckets.end(), list<string>::iterator(), buckets.end());
    };

private:
    vector<list<string>> buckets;
    size_t elements_count;

    size_t hash_function(const string& value) const;
};


