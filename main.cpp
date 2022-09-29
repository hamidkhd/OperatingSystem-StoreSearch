#include "header.hpp"

int main(int argc, char *argv[])
{
    mkdir("pipes", 0777); 

    std::ifstream file(argv[1]); 
    std::string line;

    std::vector <std::string> named_pipes;
    std::vector <int> result;

	while (std::getline(file, line))
	{
        std::vector <std::string> command_info = split(line, ' ');

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
            std::string temp = line + "#" + argv[2] + "#" + named_pipe_str;
            strcpy(buff, temp.c_str());
            write(unnamed_pipe[1], buff, BUFFER_SIZE);
        }

        else if (pid == 0)
        {
            std::string temp_unnamed_pipe = std::to_string(unnamed_pipe[0]) + " " + std::to_string(unnamed_pipe[1]);
            execl("./assets.out", "assets.cpp", temp_unnamed_pipe.c_str(), NULL);
        }
	}

    file.close();

    for (int j = 0; j < named_pipes.size(); j++)
    {
        char read_named_buff[BUFFER_SIZE];
        int fd = open(named_pipes[j].c_str(), O_RDONLY); 
        read(fd, read_named_buff, BUFFER_SIZE); 
        unlink(named_pipes[j].c_str());
        if (strcmp(read_named_buff, "reject") != 0)
            cout << read_named_buff << endl;
        else 
            cout << -1 << endl;
        close(fd);
    }   

    exit(EXIT_FAILURE);
}