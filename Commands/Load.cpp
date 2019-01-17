#include "Load.h"

Load::Load(std::string src, std::string dst, unsigned int ignore_lines = 0)
    : _src(src), _dst(dst), _ignore_lines(ignore_lines){}

std::vector<std::string> Load::split(std::string txt)
{
	std::vector<std::string> splited;
	std::string correct_place = "";

	for (int i = 0; i < (int)txt.length(); i++)
	{
		if (txt.at(i) == ',')
		{
			splited.push_back(correct_place);
			correct_place = "";
		}
		else
			correct_place += txt.at(i);
	}
	splited.push_back(correct_place);

	return splited;
}

void Load::execute()
{
	Schema schema = g_table_name_to_schema[_dst];
	std::ifstream file(_src);

	std::string line;

	for (size_t i = 0; i < _ignore_lines; i++)
		std::getline(file, line);

	//std::getline(file, line);

	//std::vector<std::string> places = split(line);

	std::vector<std::ofstream> out_files;

	//out_files.resize(places.size());
	out_files.resize(schema.field_cnt);

	

	for (size_t i = 0; i < out_files.size(); i++)
	{
		int ct = schema.columns[i].get_type();
		if (ct == 2)
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios_base::app);
		else
			out_files[i].open(_dst + "/" + std::to_string(i), std::ios::binary);
	}

	unsigned int line_cnt = 0;
	while (std::getline(file, line))
	{
		std::vector<std::string> vector_line = split(line);
		for (int i = 0; i < (int)(vector_line.size()); i++)
		{
			int ct = schema.columns[i].get_type();

			out_files[i] << vector_line[i];
			if (ct == 1)
			{
				int value = std::stoi(vector_line[i]);
				out_files[i].write((char*)(&value), sizeof(int));
			}
			else if (ct == 2)
			{
				float value = std::stof(vector_line[i]);
				out_files[i].write((char*)(&value), sizeof(float));
			}
			else
				out_files[i] << vector_line[i] << "\n";
		}
		line_cnt++;
	}

	schema.line_cnt = line_cnt;

	file.close();
	for (size_t i = 0; i < out_files.size(); i++)
		out_files[i].close();
}