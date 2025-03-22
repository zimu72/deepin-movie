**1. Build Dependencies** (The list might be incomplete. If compilation fails, consult DeepSeek or GPT for solutions)

```
sudo apt build-dep deepin-movie  
# If this fails:  
# 1. Edit /etc/apt/sources.list and uncomment line 2  
# 2. Run `sudo apt update` and retry installation  

sudo apt install debhelper cmake pkg-config \  
                libqt5svg5-dev qtmultimedia5-dev qttools5-dev \  
                libqt5x11extras5-dev libdtkcore5-bin libdtkwidget-dev \  
                libqt5sql5-sqlite \  
                libmpv-dev libxcb1-dev libxcb-util0-dev \  
                libffmpegthumbnailer-dev \  
                libxcb-shape0-dev libxcb-ewmh-dev xcb-proto \  
                x11proto-record-dev libxtst-dev \  
                libavcodec-dev libavformat-dev libavutil-dev \  
                libpulse-dev libdvdnav-dev libgsettings-qt-dev \  
                libmpris-qt5-dev libdbusextended-qt5-dev libva-dev \  
                libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev \  
                qttools5-dev-tools libgtest-dev googletest \  
                libqrencode-dev libgmock-dev g++ qt5-default  
```

*Might also require this dependency: https://github.com/nikhilm/qhttpserver (uncertain, as AI-modified code required numerous trials and installed multiple dependencies to finally succeed).*

------

**2. Build Instructions**

```
cd deepin-movie-reborn  
mkdir Build  
cd Build  
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..  
make  
sudo make install  
```

------

**3. Common Errors & Solutions**

**Error 1**: Missing translation files
**Solution**:

```
cd translations  
lrelease deepin-movie_zh_CN.ts -qm deepin-movie_zh_CN.qm  
# Move the generated .qm file to the appropriate directory  
```

**Error 2**: `"Settings schema 'com.deepin.deepin-movie' is not installed"`
**Solution**:

```
cd src  
sudo cp libdmr/com.deepin.deepin-movie.gschema.xml /usr/share/glib-2.0/schemas/  
sudo glib-compile-schemas /usr/share/glib-2.0/schemas/  
```

### Deepin movie

Deepin Movie is a full-featured video player developed by Deepin Technology, supporting playing local and streaming media in multiple video formats.

### Dependencies

### Build dependencies

_The **master** branch is current development branch, build dependencies may changes without update README.md, refer to `./debian/control` for a working build depends list_

- debhelper

* cmake
* pkg-config
* libdtkcore5-bin
* libdtkwidget-dev
* libmpv-dev
* libxcb1-dev
* libxcb-util0-dev
* libxcb-shape0-dev
* libxcb-ewmh-dev
* xcb-proto
* x11proto-record-dev
* libxtst-dev
* libavcodec-dev
* libavformat-dev
* libavutil-dev
* libpulse-dev
* libssl-dev
* libdvdnav-dev
* libgsettings-qt-dev
* ffmpeg module(s):
  - libffmpegthumbnailer-dev
* Qt5(>= 5.6) with modules:
  - qtbase5-dev
  - qtbase5-private-dev
  - libqt5x11extras5-dev
  - qt5-qmake
  - libqt5svg5-dev
  - qttools5-dev
  - qttools5-dev-tools
  - libqt5sql5-sqlite
  - qtmultimedia5-dev

## Installation 

### Build from source code

1. Make sure you have installed all dependencies.

_Package name may be different between distros, if deepin-movie is available from your distro, check the packaging script delivered from your distro is a better idea._

Assume you are using [Deepin](https://distrowatch.com/table.php?distribution=deepin) or other debian-based distro which got deepin-movie delivered:

``` 
$ apt build-dep deepin-movie
```

2. Build:

```
$ cd deepin-movie-reborn
$ mkdir Build
$ cd Build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
$ make
```

3. Install:
```
$ sudo make install
```

When install complete, the executable binary file is placed into `/usr/bin/deepin-movie`.

## Usage

Execute `deepin-movie`

## Documentations

 - [Development Documentation](https://linuxdeepin.github.io/deepin-movie/)
 - [User Documentation](https://wikidev.uniontech.com/index.php?title=%E5%BD%B1%E9%99%A2) | [用户文档](https://wikidev.uniontech.com/index.php?title=%E5%BD%B1%E9%99%A2)

## Getting help

* [Official Forum](https://bbs.uniontech.com/)
 * [Developer Center](https://github.com/linuxdeepin/developer-center)
 * [Gitter](https://gitter.im/orgs/linuxdeepin/rooms)
 * [IRC Channel](https://webchat.freenode.net/?channels=deepin)
 * [Wiki](https://wikidev.uniontech.com/)

## Getting involved

* We encourage you to report issues and contribute changes

   - [Contribution guide for developers](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers-en) (English)
   - [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers) (中文)
   - [Translate for your language on Transifex](https://www.transifex.com/linuxdeepin/deepin-movie/)

## License

Deepin Movie is licensed under [GPL-3.0-or-later](LICENSE)
