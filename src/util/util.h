#pragma once

#include <map>
#include <vector>
#include <string>

// String manipuliation
std::vector<std::string> split(const std::string &s, char delim=' ', int limit=-1);
std::vector<std::string> splitCSV(const std::string s, char delim=' ', char enclosure='"');
std::string ltrim(std::string s);
std::string rtrim(std::string s);
std::string trim(std::string s);
bool startswith(std::string str, std::string start);
bool endswith(std::string str, std::string end);

// Path manipulation
bool file_exists(std::string filename);
void file_put_contents(std::string path, std::string contents);
std::string file_get_contents(std::string path);
