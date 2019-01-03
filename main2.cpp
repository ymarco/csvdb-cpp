#include "Commands/Create.h"
#include <vector>
#include <utility>


int main(){
    std::vector<std::pair<char, std::string>> args;
    args.push_back({1,"year"});
    Create c("movies", true, args, 1);
}