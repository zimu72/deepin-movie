// Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <DApplication>
#include "mainwindow.h"
#include "url_dialog.h"
#include "presenter.h"
#include "movieapp.h"
#include "window.h"

using namespace dmr;

class Application;

#if defined(dApp)
#undef dApp
#endif
#define dApp (static_cast<Application *>(QCoreApplication::instance()))

DWIDGET_USE_NAMESPACE


class Application : public DApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application();

    void setMainWindow(Window *window);
    Window * getMainWindow();

private:
    Window *m_mainwindow {nullptr};
};

#endif  // APPLICATION_H_
