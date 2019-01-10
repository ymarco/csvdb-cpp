#ifndef SCHEMA_H
#define SCHEMA_H

#include <unordered_map>
#include <vector>
#include <string>
#include "utils.h"
#include "Commands/Select/agg.h"


template<class T>
class ColAggs{
public:
    agg::Avg<T> avg;
    agg::Min<T> min;
    agg::Max<T> max;
    inline void aggregate(T val){avg.aggregate(val); min.aggregate(val); max.aggregate(val);};
};

class Column{
public:
    void set_type(char type_);
    std::string name;
    char type = 0;
    void* aggs;
    void aggregate(void* val);
    char get_type();
    ~Column();
};

class Schema{
public:
    const std::string name;
    Schema(std::string name_,
        std::vector<std::pair<std::string, char>> field_names_and_types
    );
    ~Schema();
    const ushort field_cnt;
    Column* columns = nullptr; // array allocated on heap of Column objs
    std::unordered_map<std::string, ushort> field_name_to_index;

};




#endif