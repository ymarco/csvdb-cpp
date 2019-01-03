#ifndef DROP_H
#define DROP_H

#include <string>
#include <utility>


class Drop {
private:
	const std::string _name;
	const bool _enable_ifexists;
	void _create_json();

public:
	Drop(std::string name, bool enable_ifexists);
	void execute();
};

#endif