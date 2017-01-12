#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //needed for std::transform

namespace StringUtility {

    template < typename T >
    static std::string toString( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
    
    template < typename T >
    static T stringToBool ( std::string &Text )
    {
        return Text != "0";
    }
    
    template <typename T>
    static T stringToNumber ( std::string &Text )//Text not by const reference so that the function can be used with a character array as argument
    {
        std::stringstream ss(Text);
        T result;
        return ss >> result ? result : 0;
    }

    static bool startsWith(std::string baseString, std::string stringToFind) {
        
        if (baseString.compare(0, stringToFind.length(), stringToFind) == 0)
        {
            return true;
        }
        return false;
    }
    
    static bool endsWith (std::string baseString, std::string stringToFind) {
        if (baseString.length() >= stringToFind.length()) {
            return (0 == baseString.compare (baseString.length() - stringToFind.length(), stringToFind.length(), stringToFind));
        } else {
            return false;
        }
    }
    
    
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> tokens;
        while (getline(ss, item, delim)) {
            tokens.push_back(item);
        }
        return tokens;
    }
    
    static std::string toLowerCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
}
