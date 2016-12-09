#include <iostream>
#include "obscure.h"


using namespace std;
using namespace Magick;

static const struct option opts[] = {{"help", no_argument, 0, 'h'},
                                     {"alt-image", required_argument, 0, 'm'},
                                     {"output", required_argument, 0, 'o'},
                                     {"root", no_argument, 0, 'd'},
                                     {"blur", optional_argument, 0, 'b'},
                                     {"shade", optional_argument, 0, 'S'},
                                     {"swirl", optional_argument, 0, 's'},
                                     {"spread", optional_argument, 0, 'p'},
                                     {"implode", optional_argument, 0, 'i'},
                                     {"wave", optional_argument, 0, 'w'},
                                     {0, 0, 0, 0}};

static void help() {
  cout << "ShantyLocker [OPTIONS...]         " << endl;
  cout << "    -h --help                        "
       << "Show help" << endl;
  cout << "    -m --alt-image [path]            "
       << "Use image at [path] as background to transpose obfuscated windows "
          "onto. Can't be used with --root"
       << endl;
  cout << "    -o --output [path]               "
       << "Save resulting lock screen image to path" << endl;
  cout << "    -d --root                        "
       << "Obfuscate the desktop as one window, instead of each visible window "
          "individually"
       << endl;
  cout << "  Obfuscation methodologies:         (built-in functions provided "
          "by ImageMagick)"
       << endl;
  cout << "    -b --blur [radius]               Blurs image. [radius] "
          "specifies the radius of the Gaussian"
       << endl;
  cout << "    -S --shade [value]               " << endl;
  cout << "    -s --swirl [degrees]             Swirl the image from the "
          "center by [degrees]"
       << endl;
  cout << "    -p --spread [amount]             Spread pixels randomly within "
          "image by [amount]"
       << endl;
  cout << "    -i --implode [factor]            Implode image by [factor]"
       << endl;
  cout << "    -w --wave [amplitude]            Must use with --alt-image for best effect"
       << endl;
}

int main(int argc, char** argv) {
  vector<function<void(Image&, double)>> operations;
  vector<double> params;

  // Default values for operations
  double rad = 5;
  double shade_factor = 20;
  double swirl_factor = 720;
  size_t spread_factor = 12;
  double implode_factor = 50;
  double amp = 5;
  bool desktop = false;

  Image base("x:root");

  string alt_image;

  // Get user's home directory, returns /home/user
  string path(getpwuid(getuid())->pw_dir);
  path += "/.config/shantylocker.png";

  int optidx;
  int c;

  while ((c = getopt_long(argc, argv, "hm:o:db::S::s::p::i::w::", opts,
                          &optidx)) != -1) {
    switch (c) {
      case 'h':
        help();
        return 0;

      case 'm':
        alt_image = string(optarg);
        base = Image(alt_image);
        break;

      case 'o':
        path = string(optarg);

      case 'd':
        desktop = true;
        break;

      case 'b':
        rad = optarg ? stod(string(optarg)) : rad;
        operations.push_back(blur);
        params.push_back(rad);
        break;

      case 'S':
        shade_factor = optarg ? stod(string(optarg)) : shade_factor;
        operations.push_back(shade);
        params.push_back(shade_factor);
        break;

      case 's':
        swirl_factor = optarg ? stod(string(optarg)) : swirl_factor;
        operations.push_back(swirl);
        params.push_back(swirl_factor);
        break;
      case 'p':
        spread_factor = optarg ? (size_t)stoi(string(optarg)) : spread_factor;
        operations.push_back(spread);
        params.push_back(spread_factor);
        break;
      case 'i':
        implode_factor = optarg ? stod(string(optarg)) : implode_factor;
        operations.push_back(implode);
        params.push_back(implode_factor);
        break;

      case 'w':
        amp = optarg ? stod(string(optarg)) : amp;
        operations.push_back(wave);
        params.push_back(amp);
        break;

      case '?':
        help();
        return 1;
      default:
        if (optopt == 'c')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option -%c.\n", optopt);
        else
          fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
        return 1;
    }
  }

  InitializeMagick(*argv);

  int screens;

  // 1st parameter takes display name. If NULL, uses DISPLAY env
  xcb_connection_t* connection = xcb_connect(NULL, &screens);

  /* Get the first screen */

  const xcb_setup_t* setup = xcb_get_setup(connection);
  xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

  xcb_screen_t* screen = iter.data;

  if (desktop) {
    execute_desktop_only(operations, params, base);
    TerminateMagick();
    xcb_disconnect(connection);
    return 0;
  }

  vector<unique_ptr<rectangle_t>> visible_windows;
  get_visible_windows(connection, screen, visible_windows);
  execute_operations(visible_windows, operations, params, base);

  // Add a display flag?
   base.display();
  //base.write(path);
  TerminateMagick();
  xcb_disconnect(connection);
  return 0;
}