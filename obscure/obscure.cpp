//
// Created by tres on 12/7/16.
//

#include"obscure.h"

/* Applies operations to children of the root window, individually */
void execute_operations(
    const std::vector<std::unique_ptr<rectangle_t>>& rects,
    const std::vector<std::function<void(Magick::Image&, double)>> operations,
    const std::vector<double> params, Magick::Image& lock_screen) {

  // This variable is necessary if the user passes the -m flag
  Magick::Image source("x:root");

  for (auto w = rects.begin(); w != rects.end(); w++) {

    // (*dereference the iterator)->then dereference and access the unique_ptr's obj
    int x = (*w)->x;
    int y = (*w)->y;

    size_t width = (*w)->width;
    size_t height = (*w)->height;

    bool xneg = false;
    if (x < 0) {
      xneg = true;
    }

    bool yneg = false;
    if (y < 0) {
      yneg = true;
    }

    // xneg and yneg tell Magick that negative coordinates are used: x = 1919 = -1
    //                                                               y = 1079 = -1
    Magick::Geometry g(width, height, x, y, xneg, yneg);
    Magick::Image rect(source);
    rect.crop(g);

    auto function_iter = operations.begin();
    auto param_iter = params.begin();
    for (; function_iter != operations.end(); function_iter++, param_iter++) {

      // Calls stored functions. e.g. (blur)(rect, 5)
      (*function_iter)(rect, *param_iter);
    }
    lock_screen.composite(rect, x, y, Magick::OverCompositeOp);
  }
}

/* Applies operations to the desktop as a single window */
void execute_desktop_only(
    const std::vector<std::function<void(Magick::Image&, double)>> operations,
    const std::vector<double> params, Magick::Image& lock_screen) {

  // here lock_screen is always equal to 'x:root'
  auto function_iter = operations.begin();
  auto param_iter = params.begin();
  for (; function_iter != operations.end(); function_iter++, param_iter++) {
    (*function_iter)(lock_screen, *param_iter);
  }
}

void blur(Magick::Image& rect, double radius) {
  double sigma = 5;
  rect.blur(radius, sigma);
}

void shade(Magick::Image& rect, const double shade) { rect.shade(shade, shade); }

void swirl(Magick::Image& rect, const double swirl) { rect.swirl(swirl); }

void spread(Magick::Image& rect, const size_t spread) { rect.spread(spread); }

void implode(Magick::Image& rect, const double implode) { rect.implode(implode); }

void wave(Magick::Image& rect, const double amplitude) {
  double length = 100;
  rect.backgroundColor("none");
  rect.wave(amplitude, length);
}