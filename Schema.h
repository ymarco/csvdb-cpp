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
    void set_type(dbvar type_);
    std::string name;
    dbvar type;
    void* aggs;
    void aggregate(void* val);
    char get_type();
    ~Column();
};

class Schema{
public:
    Schema(const std::vector<std::pair<dbvar, std::string>>& field_names_and_types // array of (type, name)
    );
    ~Schema();
    const unsigned short field_cnt;
    unsigned int line_cnt;
    Column* columns = nullptr; // array allocated on heap of Column objs
    std::unordered_map<std::string, ushort> field_name_to_index;

};




#endif