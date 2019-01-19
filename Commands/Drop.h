#ifndef DROP_H
#define DROP_H

#include <string>
#include <utility>
#include <unordered_map>
#include "Command.h"
#include "../Schema.h"
#include "../filesys.h"

extern std::unordered_map<std::string, Schema*> g_schema_name_to_ptr;

class Drop: public Command {
private:
	const std::string _name;
	const bool _enable_ifexists;

public:
	Drop(const std::string& name, bool enable_ifexists);
	void execute();
};

#endif