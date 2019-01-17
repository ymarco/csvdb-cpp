#ifndef FILEWRITEBUFFER_H
#define FILEWRITEBUFFER_H

#include <string>
#include <fstream>
#include <cstring>

template<class T, unsigned short BUFFER_SIZE = 8192/sizeof(T)>
class FileWriteBuffer{
private:
    unsigned short _i = 0;
    T _buffer[BUFFER_SIZE];
    std::ofstream out_file;
public:
    inline FileWriteBuffer(const std::string& filename){
        out_file.open(filename); /* no err detection */
    };
    inline write(const T& value){
        _buffer[_i] = value;
        _i++;
        if(i >= BUFFER_SIZE){
            out_file.write(reinterpret_cast<const char*>(_buffer), BUFFER_SIZE);
            _i=0;
        }
    };
    inline ~FileWriteBuffer(){
        out_file.write(_buffer, _i+1); //write whats left in the buffer
        out_file.close();
    };
};


#endif