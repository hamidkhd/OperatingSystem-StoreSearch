#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <vector>
#include <array>
#include <bits/stdc++.h> 

using namespace std;

#define BUFFER_SIZE 1024

std::vector <std::string> find_directory_contents(char *path);
std::vector <std::string> split(std::string input, char value);
vector <string> read_csv_file(char *path);
int find_result(std::vector <std::string> items, std::string command);
std::string str_convert(std::string input, char value);
int find_max(std::vector <int> input);
int find_min(std::vector <int> input);
bool check_first_date(std::vector <std::string> date, std::vector <std::string> command_first_date);
bool check_last_date(std::vector <std::string> date, std::vector <std::string> command_last_date);

#endif