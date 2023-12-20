#pragma once

#include <string>
#include <vector>
#include <memory>

#include "hdr/sqlite_modern_cpp.h"
#include "csv_structure.h"

class Database {
private:
    std::unique_ptr<sqlite::database>db_up = nullptr;
    const std::string weather_table_name = "weather";

public:
    Database(const std::string& database_name) {
        db_up = std::make_unique<sqlite::database>(database_name);
    }

    void MakeWeatherTable() {
        *(db_up) <<
            "create table if not exists weather (" 
            "_id integer primary key autoincrement not null,"
            "station_id         INTEGER NOT NULL,"
            "unix_timestamp     INTEGER NOT NULL,"
            "temperature        REAL,"
            "relative_humidity  INTEGER,"
            "pressure           INTEGER,"
            "wind_speed         REAL,"
            "wind_direction     INTEGER,"
            "precipitation      TEXT,"
            "CONSTRAINT unique_station_id_and_unix_timestamp UNIQUE (station_id, unix_timestamp)"
            ");";

        //*(db_up) << "CREATE INDEX IF NOT EXISTS station_time ON " + weather_table_name + "(station_id, unix_timestamp);";
    }

    void Query(const std::string& query){
        *(db_up) << query;
    }

    void AddRecord(CsvFields record){
        std::string insert_query = "INSERT INTO weather (station_id, unix_timestamp, temperature, relative_humidity, pressure, wind_speed, wind_direction, precipitation) VALUES (?,?,?,?,?,?,?,?);";
        *(db_up) << insert_query
                 << record.station_id
                 << record.unix_time
                 << record.temperature
                 << record.relative_humidity
                 << record.pressure
                 << record.wind_speed
                 << record.wind_direction
                 << record.precipitation;
    }

    void DeleteNULL(){
        *(db_up) << "DELETE FROM weather WHERE (temperature IS NULL) AND (relative_humidity IS NULL) AND (pressure IS NULL) AND (wind_speed IS NULL) AND (wind_direction IS NULL) AND (precipitation IS NULL);";
    }

    void CreateStationsTable(){
    /*
     *  All the fancy initial parcing is done by awk
     *  cat 2023-06-01T00:09:01+03:00.csv | awk -F";" '{ printf( "VALUES(%s, \047%s\047, \047%s\047, \047%s\047),\n", $4, $5,  $2, $3); }'
     *  Or if you unsure you can combine multiple files, so i did this
     *  cat *.csv | awk -F";" '{ printf( "VALUES(%s, \047%s\047, \047%s\047, \047%s\047),\n", $4, $5,  $2, $3); }' | sort -u
     */
    *(db_up) << "CREATE TABLE IF NOT EXISTS stations(_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, station_id INTEGER, name TEXT, latitude TEXT, longitude TEXT);";

    *(db_up) << "BEGIN TRANSACTION;";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27408, 'АМС Шаховская', '56.0355', '35.5266')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27410, 'АМС Люберцы', '55.6775', '37.9921')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27411, 'АМС Талдом', '56.7251', '37.5516')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27413, 'АМС Солнечногорск', '56.2225', '36.933')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27414, 'АМС Луговая', '56.0488', '37.486')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27416, 'АМС Строгино', '55.797555', '37.398166')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27417, 'АМК Клин', '56.35', '36.7496')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27419, 'АМК Дмитров', '56.3575', '37.5571')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27420, 'АМС Пушкино', '56.0258', '37.8518')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27424, 'АМС Сергиев Посад', '56.33416', '38.1293')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27500, 'АМС Толстопальцево', '55.5918', '37.2126')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27501, 'АМС Долгопрудный', '55.9301', '37.519444')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27502, 'АМК Волоколамск', '56.0126', '35.933')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27504, 'АМС Москва Бутово', '55.5776', '37.5541')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27509, 'АМК Можайск', '55.518', '36.0125')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27511, 'АМК Ново-Иерусалим', '55.9063', '36.825')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27515, 'АМК Немчиновка', '55.7066', '37.3718')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27518, 'АМК Подмосковная', '55.7085', '37.1818')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27523, 'АМК Павловский Посад', '55.7716', '38.6925')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27530, 'АМС Железнодорожный', '55.7576', '37.9666')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27531, 'АМС Электроугли', '55.7613', '38.2868')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27534, 'АМС Электросталь', '55.8', '38.493')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27538, 'АМК Черусти', '55.5476', '39.9976')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27601, 'АМС Красногорск', '55.8068', '37.3446')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27602, 'АМС Обнинск', '55.107', '36.6038')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27605, 'АМК Москва Балчуг', '55.7455', '37.63')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27609, 'АМС Мелихово', '55.1143', '37.6525')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27611, 'АМК Наро-Фоминск', '55.3871', '36.701')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27612, 'АМК ВДНХ', '55.831389', '37.621944')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27614, 'АМК Михайловское', '55.3668', '37.20')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27618, 'АМК Серпухов', '54.9225', '37.4655')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27619, 'АМК Тушино', '55.8783', '37.4366')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27620, 'АМС Михнево', '55.1313', '37.956')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27621, 'АМС Ленинские горки', '55.5076', '37.7755')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27622, 'АМС Зарайск', '54.7716', '38.8441')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27623, 'АМС Егорьевск', '55.3813', '39.008')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27625, 'АМК Коломна', '55.14216', '38.7325')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27627, 'АМК Кашира', '54.823', '38.1541')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27630, 'АМС Луховицы', '54.9651', '39.0233')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27634, 'АМС Воскресенск', '55.3035', '38.6575')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27666, 'АМК Кучино', '55.7575', '37.965')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27711, 'АМК СФМ Данки', '54.9025', '37.556')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(27725, 'АМС Серебряные пруды', '54.4683', '38.721')";
    *(db_up) << "INSERT INTO stations (station_id, name, latitude, longitude) VALUES(91029, 'АМС Марьина Роща', '55.7864', '37.6095')";
    *(db_up) << "COMMIT;";
    }
};
