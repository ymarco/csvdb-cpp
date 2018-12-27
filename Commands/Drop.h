#ifndef DROP_H
#define DROP_H

#include <string>
#include <utility>


class Drop {
private:
	const std::string _name;
	const bool _enable_ifnexists;
	void _create_json();

public:
	Drop(std::string name, bool enable_ifnexists);
	void execute();
};

#endif