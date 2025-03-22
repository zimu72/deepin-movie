在deepin官方播放器dlan投屏基础上增加了手机扫码播放的功能(点击投屏按钮会同时搜索dlan设备并弹出二维码)，并且将加速播放倍数调到10倍(需要用ctrl+右方向箭头调节)，所有代码都是通过ai改的
使用说明
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
