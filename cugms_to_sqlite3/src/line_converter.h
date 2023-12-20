#pragma once
#include <string>
#include "value_converter.h"
#include "string_tokenizer.h"

#include "csv_structure.h"

class LineConverter{
private:
    enum indeces: size_t {
        station_id        =   3  ,
        temperature       =   5  ,
        relative_humidity =   6  ,
        pressure          =   7  ,
        wind_speed        =   8  ,
        wind_direction    =   9  ,
        unix_time         =  10  ,
        precipitation     =  11  , 
    };
    
public:
    LineConverter(const std::string& line_){
        first_run = true;
        line = line_;
    }

    CsvFields GetConverted(){
        StringTokenizer tokenizer{line};
        auto tokens = tokenizer.GetTokens(";");

        // if number of cells doesnt match specified 12
        // (or 13 in versions since Nov 2023),
        // return blank optional structure
        if ((tokens.size() != 12) && (tokens.size() != 13)) {
            std::cerr << "LineConverter: Wrong number of fields!\n";
            return CsvFields{};
        }

        if (first_run) {
            first_run = false;
            converted.station_id        = Convert::ToInt<int32_t>(tokens[indeces::station_id]); 
            converted.temperature       = Convert::ToFloat(tokens[indeces::temperature]);
            converted.relative_humidity = Convert::ToInt<int32_t>(tokens[indeces::relative_humidity]);
            converted.pressure          = Convert::ToInt<int32_t>(tokens[indeces::pressure]);
            converted.wind_speed        = Convert::ToFloat(tokens[indeces::wind_speed]);
            converted.wind_direction    = Convert::ToWindDirection(tokens[indeces::wind_direction]);
            converted.unix_time         = Convert::ToTime(tokens[indeces::unix_time]);
            converted.precipitation     = Convert::ToString(tokens[indeces::precipitation]);
        }
        return converted;
    }
private:
    CsvFields converted;
    bool first_run;
    std::string line;
};
