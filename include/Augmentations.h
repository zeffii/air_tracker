#pragma once

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
};