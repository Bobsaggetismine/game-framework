#include "utils.hpp"

void call_after(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            func();
    }).detach();
}

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::string format_decimal(float value)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    std::string s = stream.str();
    return s;
}