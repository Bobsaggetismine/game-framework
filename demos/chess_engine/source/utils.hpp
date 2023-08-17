#pragma once
#include <bq.h>

std::string format_decimal(float value);

std::vector<std::string> split(std::string s, std::string delimiter);

void call_after(std::function<void(void)> func, unsigned int interval);