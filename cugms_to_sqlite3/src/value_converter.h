#pragma once
#include <optional>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>

namespace Convert {
    std::optional<uint64_t> ToTime(const std::string& cugms_date_time) noexcept {
        // this code subtracts current timezone and adds a Moscow one (UTC+03:00).
        // inspired by https://stackoverflow.com/questions/56884307/read-time-from-string-as-gmt-in-c

        std::tm cugms_tm{};
        std::istringstream ss(cugms_date_time);
        
        //                Time format : 01.09.2023 10:50
        ss >> std::get_time(&cugms_tm, "%d.%m.%Y %H:%M");
        // if fail to parse
        if (ss.fail()) {
            return {};
        }
        
        std::time_t cugms_seconds_with_timezone = std::mktime(&cugms_tm);

        std::tm* gm_tm = std::gmtime(&cugms_seconds_with_timezone);
        gm_tm->tm_isdst = false; // works only without daylight savings
    
        std::time_t gm_seconds = std::mktime(gm_tm);
        std::time_t gm_offset = (cugms_seconds_with_timezone - gm_seconds);
        std::time_t cugms_seconds_without_timezone = cugms_seconds_with_timezone + gm_offset; // got rid of random timezone 

        // adding a Moscow timezone difference by hand 
        std::time_t cugms_seconds_with_moscow_timezone = (-3 * 3600) + cugms_seconds_without_timezone;

        return cugms_seconds_with_moscow_timezone;
    }

    std::optional<float> ToFloat(const std::string& input) noexcept {
        float result = 0.0;
        try {
            result = std::stof(input);
        }
        catch (const std::exception& e) {
            return {};
        }
        return result;
    }
    
    template <class Int>
    std::optional<Int> ToInt(const std::string& input) noexcept {
        Int result = 0;
        try {
            result = std::stoi(input);
        }
        catch (const std::exception& e) {
            return {};
        }
        return result;
    }
    
    std::optional<int32_t> ToWindDirection(std::string direction) noexcept {
        static const std::map<const std::string, int32_t> wind_directions = {{"С", 0}, {"СЗ", 1}, {"З", 2}, {"ЮЗ", 3}, {"Ю", 4}, {"ЮВ", 5}, {"В", 6}, {"СВ", 7}};

        auto search = wind_directions.find(direction); 
        if (search != wind_directions.end()) {
            return search->second;
        }
        else {
            return {};
        }
    }

    std::optional<std::string> ToString(const std::string& input) noexcept {
        if (input != "н/д") {
            return input;
        }
        return {};
    }
};
