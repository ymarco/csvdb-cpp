#include "Drop.h"

Drop::Drop(const std::string& name, bool enable_ifexists) :
	_name(name), _enable_ifexists(enable_ifexists) {};

void Drop::execute(){
	if(g_table_name_to_schema.find(_name) != g_table_name_to_schema.end()){
		filesys::remove_all(_name);
		g_table_name_to_schema.erase(_name);
	}else{
		throw /* CmdError(...) */ "you tried to drop a non-existing table without the ifexists flag.";
	}

}