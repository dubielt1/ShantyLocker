//
// Created by tres on 12/3/16.
//

#ifndef SHANTYLOCKER_XCBUTIL_H
#define SHANTYLOCKER_XCBUTIL_H

/* Magick++ */
#include <ImageMagick-6/Magick++.h>

/* XCB */
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_util.h>
#include <xcb/xcb_ewmh.h>

/* STL */
#include <memory>       //std::unique_ptr
#include <vector>       //std::vector
#include <algorithm>    //std::transform (::tolower)
#include<functional>    //std::function

/* system */
#include <pwd.h>        //getpwuid
#include <unistd.h>     //getuid
#include <getopt.h>     //getopt_long


/* rectangle_t will store the coordinates and sizes of windows */
struct rectangle_t {
  int x;
  int y;
  size_t width;
  size_t height;

  rectangle_t(int x, int y, size_t w, size_t h);
  rectangle_t(const rectangle_t& r);
  rectangle_t& operator=(const rectangle_t& r);
};

bool window_is_visible(xcb_connection_t* c, const xcb_window_t& w);
bool window_is_desktop(xcb_connection_t* c, const xcb_window_t& w);

void get_visible_windows(xcb_connection_t* c, const xcb_screen_t* s,
                         std::vector<std::unique_ptr<rectangle_t>>& rects);

std::unique_ptr<rectangle_t> get_bounding_rect(xcb_connection_t* c,
                                               const xcb_window_t& w);

#endif //SHANTYLOCKER_XCBUTIL_H
