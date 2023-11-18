# Описание проекта
Следующее описание содержит (или будет содержать) описание основных классов и их реализаций. Этот рабочий документ создан для удобства синтеза множества идей из Всемирной сети в готовый продукт, потому что C++ увесистый и загруженный язык, без записи сойтись на одном варианте реализации не получится.

# lazy_reader.hpp Заголовочный Файл
## class LazyReader
Умеет лениво читать файл по строкам и возвращать строки как `std::string`.

# csv_utilities.hpp Заголовочный Файл
TODO: конкретизировать валидатор, преобразователь.

## class StringTokenizer
Токенизирует csv-строку по заданному разделителю.

# cugms_utilities.hpp Заголовочный Файл
По-хорошему, классы отсюда лучше засунуть в собственный неймспейс, типа `cugms`.

## class CsvStringValidator
Содержит два приватных метода `bool CheckLength()` и `CheckRegex()`.

`CheckLength()` проверяет количество токенов в строке.

`CheckRegex()` проверяет токены на соответствие регулярным выражениям.
`CheckRegex()` создаёт вектор из bool, который потом проверяется в `CheckString` на достаточность по маске, чтобы пройти проверку на валидность.

Они вызываются в публичном `bool CheckString(const std::string)`.

## struct CsvString
Содержит поля с преобразованными к правильному формату погодными данными из csv-строки.
Содержит поля:
```cpp
float temperature;
int_8t relative_humidity;
int_16t pressure;
float wind_speed;
int_8t wind_direction;
uint_64t unix_time;
std::string precipitation;
```

## class CsvString TokenizedStringConverter()
Преобразует вектор со строковыми токенами в CsvString структуру.

### Комментарии по преобразованию:
#### id
TODO

#### relative_humidity
TODO

#### pressure
TODO

#### wind_speed
TODO

#### wind_direction
TODO

#### unix_time
Использовать идею из https://stackoverflow.com/questions/17681439/convert-string-time-to-unix-timestamp для перевода нашего формата времени в unix-секунды.
```cpp
string s{"2019-08-22T10:55:23.000Z"};
std::tm t{};
std::istringstream ss(s);

ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");
if (ss.fail()) {
    throw std::runtime_error{"failed to parse time string"};
}   
std::time_t time_stamp = mktime(&t);
```
#### precipitation
TODO


# sqlite3_utilities.hpp Заголовочный файл
TODO
