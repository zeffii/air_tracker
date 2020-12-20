#pragma once
#include <string>

struct RT_Point
{
    float x, y;
};

struct RT_Slider
{
    int value, index;
    bool active = false;
    int minimum = 0;
    int maximum = 255;
    float min_val, max_val;
    float real_val;
};

struct RT_Parameter
{
    int index;
    float real_val, min_val, max_val;
    std::string name;
    std::string shortname;
};

