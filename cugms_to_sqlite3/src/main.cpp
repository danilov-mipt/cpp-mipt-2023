#include <iostream>
#include <fstream>
#include <string>
#include "database_wrapper.h"
#include "line_converter.h"

void PrintCsv(CsvFields f){
    std::cout << f.station_id.value_or(0) << "|"
              << f.temperature.value_or(0) << "|"
              << f.relative_humidity.value_or(0) << "|"
              << f.pressure.value_or(0) << "|"
              << f.wind_speed.value_or(0) << "|"
              << f.wind_direction.value_or(0) << "|"
              << f.unix_time.value_or(0) << "|"
              << f.precipitation.value_or("NULL") << "\n";
}


int main(){
    std::unique_ptr<Database> db;

    try {
        db = std::make_unique<Database>("weather.db");
    }
    catch (const std::exception& e) {
        std::cout << "Database initialisation failed. ";
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        db->MakeWeatherTable();
    }
    catch (const std::exception& e) {
        std::cout << "Making weather table failed. ";
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        db->CreateStationsTable();
    }
    catch (const std::exception& e) {
        std::cout << "Failed to Create Stations Table" << '\n';
        std::cout << " Caught exception: " << e.what() << "\n";
    }
    

    std::ifstream istrm("weather.csv", std::ios::binary);
    if (!istrm.is_open()) {
        std::cout << "failed to open csv" << '\n';
    }
    else {
        std::string line = "";
        try {
            db->Query("BEGIN TRANSACTION;");
            while (std::getline(istrm, line) ) {
                LineConverter converter{line};
                auto record = converter.GetConverted();
                db->AddRecord(record);
            }
            db->Query("COMMIT;");
        }
        catch (const std::exception& e) {
            std::cout << " Caught exception: " << e.what() << "\n";
            std::cout << line << "\n";
            std::cout << "-------------------------------------\n";
        }
    }

    try {
        db->DeleteNULL();
    }
    catch (const std::exception& e) {
        std::cout << "Failed to delete NULLs" << '\n';
    }
}
