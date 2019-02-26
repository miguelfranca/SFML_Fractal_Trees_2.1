#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#define PI 3.14159265358979f
#define delay 30.f


const unsigned screenWidth = sf::VideoMode::getDesktopMode().width;
const unsigned screenHeight = sf::VideoMode::getDesktopMode().height * 10 / 11.f;

const int minLength = 12;

const float min_contraction = 0.5f;
const float max_contraction = 0.5f;//0.7f

const float border = 0.f;

const float dist_factor = 1.f / (1.f - max_contraction) - 1.f;

const float DEFAULT_SIZE = 600 * sf::VideoMode::getDesktopMode().height / 2160;

static float minLength_G = 30.f;

const float DEFAULT_ZOOM = 0.97f;

const float DEFAULT_ANGLE = 30.f;//30.f

const int MAX_BRANCHES = 3;//4
const int MIN_BRANCHES = 3;//1

