#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>


/// [section1]
/// key1 value1
/// key2 value2
/// [section1]

class IniFile {
    std::map<std::string, std::map<std::string, std::string>> _data;
    std::vector<std::string> _boolValues = { "true", "on", "yes", "y", "1" }; // for realisation function read for bool

    bool isSection(const std::string& target) {
        /*std::cout << "target is " << target << std::endl;*/
        return (target[0] == '[');
    }

    std::pair<std::string, std::string> getKeyValue(const std::string& text) {
        std::pair<std::string, std::string> pair;
        size_t eq_index = 0;
        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == '=') {
                eq_index = i;
                break;
            }
        }
        for (size_t i = 0; i < text.size(); ++i) {
            if (i < eq_index) {
                pair.first += text[i];
            }
            else if (i > eq_index) {
                pair.second += text[i];
            }
        }

        return pair;
    }

    bool isPair(const std::string& text) {
        for (auto symbol : text) {
            if (symbol == '=') {
                return true;
            }
        }
        return false;
    }

public:
    explicit IniFile(std::string path) {
        std::ifstream fin(path);
        std::string str;
        std::string tmpSection;
        while (getline(fin, str)) {
            if (isSection(str) || isPair(str)) {
                if (isSection(str)) {
                    tmpSection = str;
                    _data.insert({ tmpSection, std::map<std::string, std::string>() });
                }
                else {
                    _data[tmpSection].emplace(getKeyValue(str));
                }
            }
            else {
                continue;
            }
        }
    }

    void save(std::string path) const {
        std::ofstream fout(path);
        for (const auto& section : sections()) {
            fout << section << '\n';
            for (const auto& [key, value] : _data.at(section)) {
                fout << key << '=' << value << '\n';
            }
        }
    }

    /**
     * Считывает из секции section
     * значение ключа key
     * Если не удалось считать - возвращает default value
     *
     * Определить для std::string, int, float, bool
     */


    template<typename T>
    T read(std::string section, std::string key, T defaultValue = T()) const {
        try {
            return static_cast<T>(_data.at(section).at(key));
        }
        catch (std::exception&) {
            return defaultValue;
        }
    }

    bool read(std::string section, std::string key) const {
        for (const auto& val : _boolValues) {
            if (_data.at(section).at(key) == val) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    std::string read(std::string section, std::string key, std::string defaultValue) {
        return _data[section][key];
    }

    template<typename T>
    int read(std::string section, std::string key, int defaultValue)
    {
        try {
            return std::stoi(_data[section][key]);
        }
        catch (std::exception&) {
            return defaultValue;
        }
    }

    /**
     * В ключ key из секции section
     * записывает значение value
     *
     * Определить для std::string, int, float, bool
     */

    template<typename T>
    void write(std::string section, std::string key, T value) {
        _data[section][key] = value;
    }

    /**
     * Проверяет, существует ли секция targetSection
     */
    bool sectionExists(std::string targetSection) const {
        for (const auto& section : sections()) {
            if (targetSection == section) {
                return true;
            }
        }
        return false;
    }

    /**
     * Проверяет, существует ли ключ key в секции section
     */

    bool keyExists(std::string section, std::string key) const {
        for (const auto& pair : _data.at(section)) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    /**
     * Возвращает существующие секции
     */
    std::vector<std::string> sections() const {
        std::vector<std::string> result;
        result.reserve(_data.size());
        for (const auto& [section, sectionMap] : _data) {
            result.emplace_back(section);
        }
        return result;
    }

    /**
     * Возвращает существующие ключи в секции section
     */

    std::vector<std::string> keys(const std::string& section) const {
        std::vector<std::string> result;
        result.reserve(_data.at(section).size());
        for (const auto& pair : _data.at(section)) {
            result.emplace_back(pair.first);
            /*std::cout << pair.first << std::endl;*/
        }
        return result;
    }
};


int main() {
    std::ofstream fout("C:\\Users\\PC\\CLionProjects\\untitled\\output.txt");
    IniFile inFile("C:\\Users\\PC\\CLionProjects\\untitled\\input.txt");
    inFile.save("C:\\Users\\PC\\CLionProjects\\untitled\\output.txt");

    /// sections()
    for (const auto& section : inFile.sections()) {
        std::cout << section << std::endl;
    }

    /// keys()
    for (const auto& section : inFile.sections()) {
        for (const auto& key : inFile.keys(section)) {
            std::cout << key << std::endl;
        }
    }

    /// write()
    inFile.write("[section1]", "key4", "value4");
    inFile.save("C:\\Users\\PC\\CLionProjects\\untitled\\output.txt");

    /// read<std::string>()
    std::cout << inFile.read<std::string>("[section2]", "key3") << std::endl;

    /// keyExist()
    std::cout << inFile.keyExists("[section1]", "key5") << std::endl;

    /// sectionExist()
    std::cout << inFile.sectionExists("[section2]") << std::endl;
    std::cout << inFile.sectionExists("[section3]") << std::endl;


    return 0;
}
