#include <iostream>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <algorithm>
#include <unistd.h>
#include "util.h"

std::vector<std::string> split(const std::string &s, char delim, int limit) {
    if (limit > 0) limit--;
    std::vector<std::string> parts;

    std::stringstream ss(s);
    std::string item;
    while (limit!=0 && getline(ss, item, delim)) {
        parts.push_back(item);
        limit--;
    }
    unsigned int c;
    std::string end = "";
    while ((c = ss.get()) <= 256) {
        end += (char)c;
    }
    if (end != "") {
        parts.push_back(end);
    }
    return parts;
}

std::vector<std::string> splitCSV(const std::string s, char delim, char enclosure)
{
    std::vector<std::string> parts;
    std::string buffer = "";
    bool in_enclosure = false;

    for (unsigned int i=0; i<s.size(); i++) {
        char c = s[i];

        // XXX: This implementation is little bit naive
        if (c == enclosure) {
            buffer += c;
            in_enclosure = !in_enclosure;
        } else {
            if (in_enclosure) {
                buffer += c;
            } else {
                if (c == delim) {
                    if (buffer != "") {
                        parts.push_back(buffer);
                        buffer = "";
                    }
                } else {
                    buffer += c;
                }
            }
        }
    }
    if (buffer != "") {
        parts.push_back(buffer);
    }

    return parts;
}

std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

bool startswith(std::string str, std::string start)
{
    return str.substr(0, start.length())==start;
}

bool endswith(std::string str, std::string end)
{
    return str.substr(str.length()-end.length(), end.length())==end;
}

bool file_exists(std::string filename)
{
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd > 0) {
        close(fd);
        return true;
    } else {
        return false;
    }
}

void file_put_contents(std::string path, std::string contents)
{
    std::ofstream ofile(path.c_str(), std::ofstream::binary|std::ofstream::trunc);

    if (ofile) {
        ofile << contents;
        ofile.close();
    }
}

std::string file_get_contents(std::string path)
{
    std::ifstream ifs(path.c_str(), std::ifstream::binary);
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
    return content;
}
