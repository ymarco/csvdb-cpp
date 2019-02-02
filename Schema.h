#ifndef SCHEMA_H
#define SCHEMA_H

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
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
    dbvar type;
    union{
        ColAggs<int64_t> i;
        ColAggs<double> f;
        ColAggs<uint64_t> t;
    } aggs = {ColAggs<int64_t>()};
    std::function<void(dbv)> aggregate = [](dbv){std::cerr << "ERROR: column aggregate function not initialized\n";};
    inline ~Column(){std::cout << "deleting column with type"<<utils::dbvcode2name(type) << std::endl;}
    //void aggregate(void* val);
};

class Schema{
private:
    friend void load_to_file(std::istream& file, const Schema& schema);
    void create_std_index_file(const std::string& filename) const;
public:
    Schema(const std::vector<std::pair<dbvar, std::string>>& field_names_and_types /* array of (type, name) */);
    Schema(const unsigned short field_cnt_, unsigned int line_cnt_, Column* columns_);
    ~Schema();
    const unsigned short field_cnt;
    unsigned int line_cnt;
    Column* columns = nullptr; // array allocated on heap of Column objs
    std::unordered_map<std::string, unsigned short> field_name_to_index;
};

Schema* load_from_file(std::istream& file);
void load_to_file(std::ostream& file, const Schema& schema);



#endif