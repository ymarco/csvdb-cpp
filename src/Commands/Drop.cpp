#include "Drop.h"

Drop::Drop(const std::string& name, bool enable_ifexists) :
	_name(name), _enable_ifexists(enable_ifexists) {};

void Drop::execute(){
	if(g_schema_name_to_ptr.find(_name) != g_schema_name_to_ptr.end()){
		filesys::remove_all(_name);
		auto s = g_schema_name_to_ptr.at(_name);
		delete s;
		g_schema_name_to_ptr.erase(_name);
	}else{
		throw CmdError("you tried to drop a non-existing table without the ifexists flag.");
	}

}