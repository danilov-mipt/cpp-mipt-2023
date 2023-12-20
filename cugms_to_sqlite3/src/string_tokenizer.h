#pragma once

#include <string>
#include <vector>

class StringTokenizer {
public:
    using TokenContainer = std::vector<std::string>; 

private:
    TokenContainer tokens;
    std::string initial_string;
    bool tokenized = false;

public:
    StringTokenizer (const std::string& initial_string_)  {
        initial_string = initial_string_;
        tokenized = false;
    }

    const TokenContainer& GetTokens(const std::string& delimiter = ";") {
        if (!tokenized) {
            std::string::size_type start = 0;
            std::string::size_type end = initial_string.find(delimiter);
            while (end != std::string::npos) {
                tokens.push_back(initial_string.substr(start, end - start));
                start = end + delimiter.length();
                end = initial_string.find(delimiter, start);
            }
            if (start < initial_string.length()) {
                tokens.push_back(initial_string.substr(start));
            }
        }
        return tokens;
    }

};
