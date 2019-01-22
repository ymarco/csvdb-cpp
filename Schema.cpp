#include "Schema.h"
#include "FileWriteBuffer.h"
#include <iostream>


void Column::set_type(dbvar type_){
    type = type_;
    switch(type){
        case dbv_INT:
            new(&aggs.i) ColAggs<int32_t>;
            aggregate = [this](void* val){ this->aggs.i.aggregate(*((int32_t*)val)); };
            break;
        case dbv_FLOAT:
            new(&aggs.f) ColAggs<float>;
            aggregate = [this](void* val){ this->aggs.f.aggregate(*((float*)val)); };
            break;
        case dbv_TIMESTAMP:
            new(&aggs.ts) ColAggs<uint32_t>;
            aggregate = [this](void* val){ this->aggs.ts.aggregate(*((uint32_t*)val)); };
            break;
        case dbv_VARCHAR:
            aggregate = [](void* val){};
            break;
    }
}

/* void Column::aggregate(void* val){
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
*/
Schema::Schema(const std::vector<std::pair<dbvar, std::string>>& fields_type_and_name)
    : field_cnt(fields_type_and_name.size()){

    std::cout << "CONSTRUCTING SCHEMA\n";
    columns = new Column[field_cnt];
    for(unsigned short i=0; i<field_cnt; i++){
        field_name_to_index[fields_type_and_name[i].second] = i;
        columns[i].set_type(fields_type_and_name[i].first);
    }
    TEST(auto x = columns[0].type;);
}

Schema::Schema(const unsigned short field_cnt_, unsigned int line_cnt_, Column* columns_)
    :field_cnt(field_cnt_), line_cnt(line_cnt_), columns(columns_){};

Schema::~Schema(){
    TEST(delete[] columns;)
}


void Schema::create_std_index_file(const std::string& filename) const{
    FileWriteBuffer<unsigned int> writer(filename + "/,std_index");
    for(unsigned int i=0; i<line_cnt; i++){
        writer.write(i);
    }
}


Schema* load_from_file(std::istream& file){
    struct {
        const unsigned short field_cnt;
        const unsigned int line_cnt;
    } info({0,0});
    file.read(reinterpret_cast<char*>(&info), sizeof(info));
    Column* columns = new Column[info.field_cnt];
    file.read(reinterpret_cast<char*>(columns), sizeof(Column) * info.field_cnt);
    Schema* s = new Schema(info.field_cnt, info.line_cnt, columns);
    return s;
}

void load_to_file(std::ostream& file, const Schema& schema){
    struct {
        const unsigned short field_cnt;
        const unsigned int line_cnt;
    } info({schema.field_cnt, schema.line_cnt}); // needed because rein_cast cant take constants
    file.write(reinterpret_cast<char*>(&info), sizeof(info));
    file.write(reinterpret_cast<char*>(schema.columns), sizeof(Column) * schema.field_cnt); 
}