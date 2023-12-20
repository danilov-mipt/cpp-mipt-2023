#pragma once
#include <optional>
#include <string>

struct CsvFields {
    std::optional<int32_t>      station_id;
    std::optional<float>        temperature;
    std::optional<int32_t>      relative_humidity;
    std::optional<int32_t>      pressure;
    std::optional<float>        wind_speed;
    std::optional<int32_t>      wind_direction;
    std::optional<uint64_t>     unix_time;
    std::optional<std::string>  precipitation;
};
