//
// Created by tres on 12/7/16.
//

#ifndef SHANTYLOCKER_OBSCURE_H
#define SHANTYLOCKER_OBSCURE_H

#include "xcbutil.h"

/* Applies operations to appropriate windows */
void execute_operations(
    const std::vector<std::unique_ptr<rectangle_t>>& rects,
    const std::vector<std::function<void(Magick::Image&, double)>> operations,
    const std::vector<double> params, Magick::Image& lock_screen);

void blur(Magick::Image& rect, const double radius = 5);

void shade(Magick::Image& rect, const double shade = 20);

void swirl(Magick::Image& rect, const double swirl = 720);

void spread(Magick::Image& rect, const size_t spread = 12);

void implode(Magick::Image& rect, const double implode = 20);

void wave(Magick::Image& rect, const double amplitude = 5);

#endif //SHANTYLOCKER_OBSCURE_H
