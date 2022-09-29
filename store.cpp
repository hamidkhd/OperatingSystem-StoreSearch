#include "header.hpp"

int main(int argc, char *argv[])
{    
    char unnamed_buff[BUFFER_SIZE];
    std::vector <std::string> parent_unnamed_pipe = split(argv[1], ' ');
    read(stoi(parent_unnamed_pipe[0]), unnamed_buff, 1024);    
    std::string str(unnamed_buff);
    close(stoi(parent_unnamed_pipe[0]));

    std::vector <std::string> out_unnamed_pipe = split(str, '#');
    std::vector <std::string> items = read_csv_file(&out_unnamed_pipe[1][0]);

    int result = find_result(items, out_unnamed_pipe[0]);

    char write_named_buff[BUFFER_SIZE];    
    strcpy(write_named_buff, to_string(result).c_str()); 
    int fd = open(out_unnamed_pipe[2].c_str(), O_WRONLY);     
    write(fd, write_named_buff, BUFFER_SIZE); 
    close(fd);

    exit(EXIT_FAILURE);
}