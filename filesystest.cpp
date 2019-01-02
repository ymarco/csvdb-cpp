#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
 
int main()
{
    fs::create_directories("this_dir_was_created_by_filesystest/1/2/a");
    std::cout << "finished\n";
}
