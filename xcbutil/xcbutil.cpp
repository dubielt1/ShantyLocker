//
// Created by tres on 12/3/16.
//

#include <xcb/xcb_ewmh.h>
#include "xcbutil.h"

rectangle_t::rectangle_t(int x, int y, size_t w, size_t h)
    : x(x), y(y), width(w), height(h) {}
rectangle_t::rectangle_t(const rectangle_t& r) {
  x = r.x;
  y = r.y;
  width = r.width;
  height = r.height;
}
rectangle_t& rectangle_t::operator=(const rectangle_t& r) {
  x = r.x;
  y = r.y;
  width = r.width;
  height = r.height;

  return *this;
}

bool window_is_visible(xcb_connection_t* c, const xcb_window_t& w) {
  xcb_get_window_attributes_cookie_t cookie = xcb_get_window_attributes(c, w);

  xcb_get_window_attributes_reply_t* reply;

  // Check if reply was successful
  if ((reply = xcb_get_window_attributes_reply(c, cookie, NULL))) {
    return XCB_MAP_STATE_VIEWABLE == (*reply).map_state;
  }
  return false;
}

/* Returns true if there is a desktop window (e.g. xfdesktop) */
bool window_is_desktop(xcb_connection_t* c, const xcb_window_t& w) {
  xcb_ewmh_connection_t ewmh;
  xcb_ewmh_init_atoms_replies(&ewmh, xcb_ewmh_init_atoms(c, &ewmh), NULL);

  // Get window name
  xcb_get_property_cookie_t name_cookie = xcb_ewmh_get_wm_name(&ewmh, w);
  char* cwindow_name = (char*)xcb_get_property_value(
      xcb_get_property_reply(c, name_cookie, NULL));

  std::string window_name(cwindow_name);
  std::transform(window_name.begin(), window_name.end(), window_name.begin(),
                 ::tolower);

  // Get _NET_WM_WINDOW_TYPE
  xcb_get_property_cookie_t type_cookie = xcb_ewmh_get_wm_window_type(&ewmh, w);
  xcb_atom_t* window_type = (xcb_atom_t*)xcb_get_property_value(
      xcb_get_property_reply(c, type_cookie, NULL));

  // Check if replies were successful
  if (window_type && !window_name.empty()) {
      return *window_type == ewmh._NET_WM_WINDOW_TYPE_DESKTOP ||
             window_name.find("desktop") != std::string::npos;
  }

  return false;
}

/* Stores every visible child of root window in rects */
void get_visible_windows(xcb_connection_t* c, const xcb_screen_t* s,
                         std::vector<std::unique_ptr<rectangle_t>>& rects) {
  xcb_query_tree_cookie_t cookie = xcb_query_tree(c, s->root);
  xcb_query_tree_reply_t* reply;

  // Get the children of the root window, and how many there are
  if ((reply = xcb_query_tree_reply(c, cookie, NULL))) {
    xcb_window_t* children = xcb_query_tree_children(reply);
    int num_children = xcb_query_tree_children_length(reply);

    // If a window is visible, store its bounding_rect for obscuring
    for (int i = 0; i < num_children; i++) {
      if (window_is_visible(c, children[i]) &&
          !window_is_desktop(c, children[i])) {
        rects.push_back(get_bounding_rect(c, children[i]));
      }
    }
  }
}

std::unique_ptr<rectangle_t> get_bounding_rect(xcb_connection_t* c,
                                               const xcb_window_t& w) {
  xcb_get_geometry_cookie_t cookie;
  xcb_get_geometry_reply_t* reply;
  cookie = xcb_get_geometry(c, w);

  if ((reply = xcb_get_geometry_reply(c, cookie, NULL))) {
    std::unique_ptr<rectangle_t> rectangle = std::make_unique<rectangle_t>(
        reply->x, reply->y, reply->width, reply->height);

    return rectangle;
  }
  return nullptr;
}
