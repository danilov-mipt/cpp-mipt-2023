#include <string>
#include <iomanip>
#include <locale>
#include <sstream>

namespace cugms
{
    struct CsvString {
        float temperature;
        int8_t relative_humidity;
        int16_t pressure;
        float wind_speed;
        int8_t wind_direction;
        uint64_t unix_time;
        std::string precipitation;
    };

    class TokenizedStringConverter {
    private:
        uint64_t ConvertStringToUnix(const std::string cugms_date_time) {
            std::tm t{};
            std::istringstream ss(cugms_date_time);
            std::cerr << cugms_date_time << "\n";

            //         Time format : 01.09.2023 10:50
            ss >> std::get_time(&t, "%d.%m.%Y %H:%M");

            if (ss.fail()) {
                throw std::runtime_error{"Failed to parse time string."};
            }   

            std::time_t unix_time_stamp = mktime(&t);
            // dirty moscow local time hack
            uint64_t moscow_time_unix = 0 + unix_time_stamp;


            std::cout.imbue(std::locale("ru_RU.utf8"));
            std::cerr << "debug: ru_RU: " << std::put_time(&t, "%c %Z") << '\n';

            return moscow_time_unix;
        }

    public:
        CsvString Convert() {
            return {};
        }
        uint64_t _ConvertStringToUnix(const std::string cugms_date_time) {
            return ConvertStringToUnix(cugms_date_time);
        }
    };
}
