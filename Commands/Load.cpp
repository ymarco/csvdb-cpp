#include "Load.h"
#include "../utils.h"
#include <iostream>

Load::Load(std::string src, std::string dst, unsigned int ignore_lines = 0)
    : _src(src), _dst(dst), _ignore_lines(ignore_lines){}


void Load::_split(const std::string& txt_line, std::string* splitted){
	std::string field_buffer = "";
	unsigned short curr_field_num = 0;
	for (unsigned short i = 0; i < txt_line.length(); i++){
		if (txt_line.at(i) == ','){
			splitted[curr_field_num] = field_buffer;
			field_buffer = "";
			curr_field_num++;
		}else
			field_buffer += txt_line.at(i);
	}
	splitted[curr_field_num] = field_buffer;
}

void Load::execute(){
	Schema* schema = g_schema_name_to_ptr.at(_dst);
	const unsigned short field_cnt = schema->field_cnt;
	Column* const columns = schema->columns;
	std::ifstream src_csv(_src);

	std::string line;
	// skipping the lines that are spposed to be ignored
	for (size_t i = 0; i < _ignore_lines; i++)
		std::getline(src_csv, line);

	std::vector<std::ofstream> out_files;
	out_files.resize(field_cnt);
	//out_files.shrink_to_fit();
	// creating and opening all the files
	for (size_t i = 0; i < field_cnt; i++){
		std::cout << "opening file for column #" << i << "\n";
		if (columns[i].type == dbv_VARCHAR)
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios_base::app);
		else
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios::binary);
	}

	unsigned int& line_cnt = schema->line_cnt;
	std::string splitted[field_cnt];
	dbv curr_val;
	while (std::getline(src_csv, line)){
		line_cnt++;
		_split(line, splitted);
		std::cout << "Reading record #" << line_cnt << std::endl;
		for (unsigned short i = 0; i < field_cnt; i++){
			dbvar ct = columns[i].type;
			std::cout << "processing: \"" << splitted[i] <<"\"\n";
			
			switch(ct){
				case dbv_INT:{
					std::string& sval = splitted[i];
					if(sval.empty()) curr_val.i = null_int;
					else curr_val.i = std::stoll(sval);
					columns[i].aggregate(curr_val);
					out_files[i].write(reinterpret_cast<char*>(&curr_val), sizeof(int64_t));
					break;
				}
				case dbv_FLOAT:{
					std::string& sval = splitted[i];
					if(sval.empty()) curr_val.f = null_float;
					else curr_val.f = std::stod(sval);
					out_files[i].write(reinterpret_cast<char*>(&curr_val), sizeof(float));
					break;
				}
				case dbv_TIMESTAMP:{
					std::string& sval = splitted[i];
					if(sval.empty()) curr_val.t = null_timestamp;
					else curr_val.t = std::stoull(sval);
					columns[i].aggregate(curr_val);
					out_files[i].write(reinterpret_cast<char*>(&curr_val), sizeof(unsigned int));
				}
				default:/* varchar */{
					out_files[i] << splitted[i] << "\n";
					break;
				}
			}
		}
	}

	src_csv.close();
	for (size_t i = 0; i < out_files.size(); i++)
		out_files[i].close();
}
