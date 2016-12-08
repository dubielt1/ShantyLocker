# shanty lock

A 'spirtual' extension of ![xwobf](https://github.com/glindste/xwobf), this program can either:
take a screenshot of your desktop and obscure only all visible windows, or obscure the entire desktop as a whole.
Many image obscuring options have been added.

### Blur and Swirl
![blur and swirl](http://i666.photobucket.com/albums/vv27/tres_dubiel1/b6s720_zpstpsc53wn.png)

### Swirl --root
![blur and swirl desktop](http://i666.photobucket.com/albums/vv27/tres_dubiel1/i3sd_zpsvzf1vd4r.png)

### Blur
![blur](http://i666.photobucket.com/albums/vv27/tres_dubiel1/b7_zpshnrbzwad.png)

### Spread and Shade --alt-image
![spread, shade and alt-image](http://i666.photobucket.com/albums/vv27/tres_dubiel1/jetlocker_zpslfsp37cw.png)

### Usage

All options have default values

```
[OPTIONS...]
    -h --help                        Show help
    -m --alt-image [path]            Use image at [path] as background to transpose obfuscated windows onto. Can be used with --root
    -o --output [path]               Save resulting lock screen image to path
    -d --root                        Obfuscate the desktop as one window, instead of each visible window individually
  Obfuscation methodologies:         (built-in functions provided by ImageMagick)
    -b --blur [radius]               Blurs image. [radius] specifies the radius of the Gaussian
    -S --shade [value]
    -s --swirl [degrees]             Swirl the image from the center by [degrees]
    -p --spread [amount]             Spread pixels randomly within image by [amount]
    -i --implode [factor]            Implode image by [factor] 
    -w --wave [amplitude]            Must use with --alt-image for best effect
```

### Example using i3lock

```
#!/bin/bash
shantylock  -S -p -o/tmp/lock.png
i3lock -i /tmp/lock.png
```

### Credit

![xwobf](https://github.com/glindste/xwobf)

### License

Unlicense