#include "Schema.h"
#include <tuple>
#include "FileWriteBuffer.h"

Column::~Column() {
	switch (type) {
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

void Column::set_type(dbvar type_) {
	type = type_;
	switch (type) {
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

void Column::aggregate(void* val) {
	switch (type) {
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

Schema::Schema(const std::vector<std::pair<dbvar, std::string>>& fields_type_and_name)
	: field_cnt(fields_type_and_name.size()) {

	columns = new Column[field_cnt];
	for (ushort i = 0; i<field_cnt; i++) {
		field_name_to_index[fields_type_and_name[i].second] = i;
		columns[i].set_type(fields_type_and_name[i].first);
	}

}

Schema::~Schema() {
	delete[] columns;
}


void Schema::create_std_index_file(const std::string& filename) const {
	FileWriteBuffer<unsigned int> writer(filename + "/,std_index");
	for (unsigned int i = 0; i<line_cnt; i++) {
		writer.write(i);
	}

}