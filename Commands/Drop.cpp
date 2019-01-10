#include "Drop.h"

Drop::Drop(std::string name, bool enable_ifexists) :
	_name(name), _enable_ifexists(enable_ifexists) {};

void Drop::execute(){
	std::error_code err_code;
	filesys::remove_all(_name, err_code);
	if(!err_code && !_enable_ifexists){
		std::string temp("you tried to drop a non-existing table without the 'if exists' flag. exiting.");
		throw "hey!\n"/* CmdError(temp) */;
	}
}