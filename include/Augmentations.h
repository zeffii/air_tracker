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
    int index = 0;
    float real_val = 1.0;
    float min_val = 0.0;
    float max_val = 2.0;
    std::string name = "Long Name";
    std::string shortname = "Short Name";
};

