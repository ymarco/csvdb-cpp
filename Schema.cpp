#include "Schema.h"
#include <tuple>

Column::~Column(){
    switch(type){
        case dbv_INT:
            delete (ColAggs<int>*)aggs;
            break;
        case dbv_FLOAT:
            delete (ColAggs<float>*)aggs;
            break;
        case dbv_TIMESTAMP:
            delete (ColAggs<unsigned int>*)aggs;
            break;
    }

}

void Column::set_type(char type_){
    type = type_;
    switch(type){
        case dbv_INT:
            aggs = new ColAggs<int>;
            break;
        case dbv_FLOAT:
            aggs = new ColAggs<float>;
            break;
        case dbv_TIMESTAMP:
            aggs = new ColAggs<unsigned int>;
            break;
        case dbv_VARCHAR:
            throw "not implemented!";
            break;
    }
}

void Column::aggregate(void* val){
    switch(type){
        case dbv_INT:
            ((ColAggs<int>*)aggs)->aggregate((*(int*)val));
            break;
        case dbv_FLOAT:
            ((ColAggs<float>*)aggs)->aggregate((*(float*)val));
            break;
        case dbv_TIMESTAMP:
            ((ColAggs<unsigned int>*)aggs)->aggregate((*(unsigned int*)val));
            break;
    }
}

Schema::Schema(std::string name_,
    std::vector<std::pair<std::string, char>> field_names_and_types)
    :name(name_), field_cnt(field_names_and_types.size()){

    columns = new Column[field_cnt];
    for(ushort i=0; i<field_cnt; i++){
        field_name_to_index[field_names_and_types[i].first] = i;
        columns[i].set_type(field_names_and_types[i].second);
    }

}

Schema::~Schema(){
    delete[] columns;
}