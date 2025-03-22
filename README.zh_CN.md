在官方原版5.15.0基础上增加了手机扫码播放功能，同时将加速播放调到最高10倍速度(需要快捷键调节)
1.编译依赖(有可能统计的不全面，如果编译报错的话可以直接问deepseek或者gpt，都可以解决)
sudo apt build-dep deepin-movie #如果报错，可以vim /etc/apt/sources.list,将第二行注释去掉，然后sodo apt update 然后重新装
sudo apt install debhelper   cmake   pkg-config   \
                libqt5svg5-dev   qtmultimedia5-dev   qttools5-dev  \
                libqt5x11extras5-dev   libdtkcore5-bin   libdtkwidget-dev  \
                libqt5sql5-sqlite  \
                libmpv-dev   libxcb1-dev   libxcb-util0-dev  \
                libffmpegthumbnailer-dev  \
                libxcb-shape0-dev  libxcb-ewmh-dev   xcb-proto  \
                x11proto-record-dev   libxtst-dev  \
                libavcodec-dev   libavformat-dev  libavutil-dev  \
                libpulse-dev   libdvdnav-dev   libgsettings-qt-dev  \
                libmpris-qt5-dev   libdbusextended-qt5-dev   libva-dev  \
                libgstreamer-plugins-base1.0-dev   libgstreamer1.0-dev  \
			    qttools5-dev-tools  libgtest-dev googletest \
				libqrencode-dev libgmock-dev g++   qt5-default
有可能还会依赖这个:https://github.com/nikhilm/qhttpserver,我也不太确定，因为用ai改的，中间试了无数次，也装了一堆依赖，最终才成功
2. 安装构建过程
cd deepin-movie-reborn
mkdir Build
cd Build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install

3.常见报错解决
1.报错：缺翻译文件:
解决方法:去translations文件夹下，执行lrelease  deepin-movie_zh_CN.ts  -qm deepin-movie_zh_CN.qm ，然后移到对应目录下即可

2.报错：“Settings schema 'com.deepin.deepin-movie' is not installed”
解决方法：	进入src目录，然后sudo cp libdmr/com.deepin.deepin-movie.gschema.xml /usr/share/glib-2.0/schemas/
 	        然后sudo glib-compile-schemas /usr/share/glib-2.0/schemas/

下面是官方的说明
### Deepin movie

影院是深度技术开发的全功能视频播放器，支持以多种视频格式播放本地和流媒体。

### 依赖

### 编译依赖

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

## 安装 

### 构建过程

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

## 用途

Execute `deepin-movie`

## 文档

 - [Development Documentation](https://linuxdeepin.github.io/deepin-movie/)
 - [User Documentation](https://wikidev.uniontech.com/index.php?title=%E5%BD%B1%E9%99%A2) | [用户文档](https://wikidev.uniontech.com/index.php?title=%E5%BD%B1%E9%99%A2)

## 帮助

* [Official Forum](https://bbs.uniontech.com/)
 * [Developer Center](https://github.com/linuxdeepin/developer-center)
 * [Gitter](https://gitter.im/orgs/linuxdeepin/rooms)
 * [IRC Channel](https://webchat.freenode.net/?channels=deepin)
 * [Wiki](https://wikidev.uniontech.com/)

## 贡献指南

* We encourage you to report issues and contribute changes

   - [Contribution guide for developers](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers-en) (English)
   - [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers) (中文)
   - [Translate for your language on Transifex](https://www.transifex.com/linuxdeepin/deepin-movie/)

## 开源许可证

Deepin Movie 根据 [GPL-3.0-or-later]（许可证）获得许可.
