#include "Load.h"
#include "../utils.h"

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
	Schema* schema = &g_table_name_to_schema.at(_dst);
	unsigned short field_cnt = schema->field_cnt;
	Column* columns = schema->columns;
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
		dbvar ct = columns[i].type;
		if (ct == dbv_VARCHAR)
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios_base::app);
		else
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios::binary);
	}

	unsigned int& line_cnt = schema->line_cnt;
	std::string splitted[field_cnt+1];
	while (std::getline(src_csv, line)){
		line_cnt++;
		_split(line, splitted);
		for (unsigned short i = 0; i < field_cnt; i++){
			dbvar ct = columns[i].type;
			//out_files[i] << splitted[i];
			
			switch(ct){
				case dbv_INT:{
					int value = std::stoi(splitted[i]);
					out_files[i].write(reinterpret_cast<char*>(&value), sizeof(int));
					break;
				}
				case dbv_FLOAT:{
					float value = std::stof(splitted[i]);
					out_files[i].write(reinterpret_cast<char*>(&value), sizeof(float));
					break;
				}
				default:{
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