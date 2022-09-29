#include "header.hpp"

int main(int argc, char *argv[])
{
    char buff[BUFFER_SIZE];
    std::vector <std::string> parent_unnamed_pipe = split(argv[1], ' ');
    read(stoi(parent_unnamed_pipe[0]), buff, BUFFER_SIZE);    
    std::string str(buff);
    close(stoi(parent_unnamed_pipe[0]));

    std::vector <std::string> out_unnamed_pipe = split(str, '#');
    std::vector <std::string> command_info = split(out_unnamed_pipe[0], ' ');
    std::vector <std::string> stores = find_directory_contents(&out_unnamed_pipe[1][0]);

    std::vector <std::string> named_pipes;
    std::vector <int> result;

    for (int i = 0; i < stores.size(); i++)
	{
        int unnamed_pipe[2];

        if (pipe(unnamed_pipe) == -1)
            exit(EXIT_FAILURE);
   
        int pid = fork();

        const char *named_pipe = ("pipes/" + to_string(pid)).c_str(); 
        std::string named_pipe_str(named_pipe);
        named_pipes.push_back(named_pipe_str);
        mkfifo(named_pipe, 0666); 

        if (pid == -1)
        {
            write(1, "Erorr in create new process! \n", 31);
            exit(EXIT_FAILURE);
        }
         
        else if (pid > 0)
        {   
            char buff[BUFFER_SIZE];
            std::string prev_address(out_unnamed_pipe[1]);
            string address = prev_address + "/" + stores[i];
            std::string temp = out_unnamed_pipe[0] + "#" + address + "#" + named_pipe_str;
            strcpy(buff, temp.c_str());
            write(unnamed_pipe[1], buff, BUFFER_SIZE);
        }

        else if (pid == 0)
        {
            std::string temp_unnamed_pipe = std::to_string(unnamed_pipe[0]) + " " + std::to_string(unnamed_pipe[1]);
            execl("./store.out", "store.cpp", temp_unnamed_pipe.c_str(), NULL);
        }
	}

    for (int j = 0; j < named_pipes.size(); j++)
    {
        char read_named_buff[BUFFER_SIZE];
        int fd = open(named_pipes[j].c_str(), O_RDONLY); 
        read(fd, read_named_buff, BUFFER_SIZE); 
        unlink(named_pipes[j].c_str());
        if (strcmp(read_named_buff, "reject") != 0)
            result.push_back(stoi(read_named_buff));
        close(fd);
    }

    int out;
    if (result.size() != 0)
        if (strcmp(command_info[0].c_str(), "MAX") == 0)
            out = find_max(result);
        else
            out = find_min(result);

    char write_named_buff[BUFFER_SIZE];    
    if (result.size() != 0)
        strcpy(write_named_buff, to_string(out).c_str()); 
    else
        strcpy(write_named_buff, "reject"); 
    int fd = open(out_unnamed_pipe[2].c_str(), O_WRONLY);     
    write(fd, write_named_buff, BUFFER_SIZE); 
    close(fd);

    exit(EXIT_FAILURE);
}