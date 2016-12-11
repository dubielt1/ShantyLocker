# shanty lock

A 'spirtual' extension of ![xwobf](https://github.com/glindste/xwobf), this program can either:
take a screenshot of your desktop and obscure only all visible windows, or obscure the desktop as a whole.
Many image obscuring options have been added.

Must be used in conjunction with a screen locking program

### Wave and Blur using --alt-image
![wave and blur](http://i666.photobucket.com/albums/vv27/tres_dubiel1/w_b_zpskampi1c2.png)

### Swirl --root
![blur and swirl desktop](http://i666.photobucket.com/albums/vv27/tres_dubiel1/i3sd_zpsvzf1vd4r.png)

### xwobf
![xwobf](http://i666.photobucket.com/albums/vv27/tres_dubiel1/x_zpsi35wupar.png)

### Spread and Shade --alt-image
![spread, shade and alt-image](http://i666.photobucket.com/albums/vv27/tres_dubiel1/jetlocker_zpslfsp37cw.png)

### Usage

All options have default values

```
[OPTIONS...]
    -h --help                        Show help
    -m --alt-image [path]            Use image at [path] as background to transpose obfuscated windows onto. Can't be used with --root
    -o --output [path]               Save resulting lock screen image to path
    -d --root                        Obfuscate the desktop as one window, instead of each visible window individually
    -D --display                     Display the generated image for fast option tweaking
  Obscuring methodologies:           (built-in functions provided by ImageMagick)
    -b --blur [radius]               Blurs image. [radius] specifies the radius of the Gaussian
    -S --shade [value]
    -s --swirl [degrees]             Swirl the image from the center by [degrees]
    -p --spread [amount]             Spread pixels randomly within image by [amount]
    -i --implode [factor]            Implode image by [factor]
    -w --wave [amplitude]            Must use with --alt-image for best effect
    -x --xwobf [size]                Same effect as xwobf
```

### Example using i3lock

```
#!/bin/bash
shantylock  -S -p -o/tmp/lock.png
i3lock -i/tmp/lock.png
```

### Install

```
git clone https://github.com/dubielt1/ShantyLocker
cd ShantyLocker
cmake -DCMAKE_BUILD_TYPE=Release .
make -j4
sudo make install
```

or

```
git clone https://github.com/dubielt1/ShantyLocker
cd ShantyLocker
mkdir build && cd $_
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install
```

### Uninstall

```
cd ShantyLocker
sudo make uninstall
```

or

```
cd ShantyLocker/build
sudo make uninstall
```

### Credit

![xwobf](https://github.com/glindste/xwobf)

### License

Unlicense