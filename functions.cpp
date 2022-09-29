#include "header.hpp"

std::vector <std::string> find_directory_contents(char *path)
{    
    std::vector <std::string> folders;
    DIR *dir = opendir(path);
    struct dirent *ent;

    if (dir != NULL) 
    {
        while ((ent = readdir(dir)) != NULL) 
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
                folders.push_back(ent->d_name);
        }
        closedir(dir);    
    } 
    else 
    {    
        write(1, "Erorr in opening the directory! \n", 34);
        exit(EXIT_FAILURE);
    }

    return folders;
}

std::vector <std::string> split(std::string input, char value)
{
    std::vector <std::string> result;
    std::string word;
  
    for (auto x : input) 
    {
        if (x == value)
        {
            result.push_back(word);
            word = "";
        }
        else 
            word += x;
    }
    result.push_back(word);

    return result;
}

vector <string> read_csv_file(char *path) 
{
	int i = 0;
	ifstream infile(path);
	std::string line, word;
	std::vector <std::string> lines;

	while (getline(infile, line))
	{
        if (i != 0)
		    lines.push_back(line);
		i++;
	}

	return lines;
}

int find_result(std::vector <std::string> items, std::string command)
{
    std::vector <std::string> command_info = split(command, ' ');
    int command_id = stoi(command_info[1]);    

    std::vector <std::string> command_first_date = split(str_convert(command_info[2], '/'), ' ');
    std::vector <std::string> command_last_date = split(str_convert(command_info[3], '/'), ' ');

    std::vector <int> result;

    for (int i = 0; i < items.size(); i++)
    {    
        bool id_status = false;
        bool first_date_status = false;
        bool last_date_status = false;

        std::vector <std::string> info = split(str_convert(items[i], ','), ' ');
        std::vector <std::string> date = split(str_convert(info[0], '/'), ' ');
        int id = stoi(info[1]);
        int price = stoi(info[2]);

        if (id == command_id)
            id_status = true;

        first_date_status = check_first_date(date, command_first_date);
        last_date_status = check_last_date(date, command_last_date);

        if (id_status == true && first_date_status == true && last_date_status == true)
            result.push_back(price);
    }

    if (result.size() == 0)
        return -1;

    if (strcmp(command_info[0].c_str(), "MAX") == 0)
        return find_max(result);
    else 
        return find_min(result); 
}

bool check_first_date(std::vector <std::string> date, std::vector <std::string> command_first_date)
{
    if (stoi(date[0]) > stoi(command_first_date[0]) || (stoi(date[0]) == stoi(command_first_date[0]) && stoi(date[1]) > stoi(command_first_date[1])) 
        || (stoi(date[0]) == stoi(command_first_date[0]) && stoi(date[1]) == stoi(command_first_date[1]) && stoi(date[2]) >= stoi(command_first_date[2])))
        return true;
    else
        return false;
}

bool check_last_date(std::vector <std::string> date, std::vector <std::string> command_last_date)
{
    if (stoi(date[0]) < stoi(command_last_date[0]) || (stoi(date[0]) == stoi(command_last_date[0]) && stoi(date[1]) < stoi(command_last_date[1])) 
            || (stoi(date[0]) == stoi(command_last_date[0]) && stoi(date[1]) == stoi(command_last_date[1]) && stoi(date[2]) <= stoi(command_last_date[2])))
        return true;
    else
        return false;
}

int find_max(std::vector <int> input)
{
    std::vector <int> temp;
    for (int i = 0; i < input.size(); i++)
        if (input[i] != -1)
            temp.push_back(input[i]);

    if (temp.size() != 0)
        return *max_element(temp.begin(), temp.end());

    return *max_element(input.begin(), input.end());
}

int find_min(std::vector <int> input)
{
    std::vector <int> temp;
    for (int i = 0; i < input.size(); i++)
        if (input[i] != -1)
            temp.push_back(input[i]);

    if (temp.size() != 0)
        return *min_element(temp.begin(), temp.end());

    return *min_element(input.begin(), input.end());
}

std::string str_convert(std::string input, char value)
{
    for (int i = 0; i < input.length(); i++)
        if (input[i] == value)
            input[i] = ' ';

    return input;
}