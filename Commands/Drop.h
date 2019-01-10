#ifndef DROP_H
#define DROP_H

#include <string>
#include <utility>
#include "Command.h"
#include "../filesys.h"

class Drop: public Command {
private:
	const std::string _name;
	const bool _enable_ifexists;

public:
	Drop(std::string name, bool enable_ifexists);
	void execute();
};

#endif