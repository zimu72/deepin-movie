// Copyright (C) 2020 ~ 2021, Deepin Technology Co., Ltd. <support@deepin.org>
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "player_engine.h"
#include "burst_screenshots_dialog.h"
#include "dmr_settings.h"
#include "utils.h"

#include <DThemeManager>

DWIDGET_USE_NAMESPACE

namespace dmr {
/**
* @brief BurstScreenshotsDialog 构造函数
* @param strPlayItemInfo 播放项信息
*/
BurstScreenshotsDialog::BurstScreenshotsDialog(const PlayItemInfo &PlayItemInfo)
    : DAbstractDialog(nullptr)
{
    MovieInfo strMovieInfo = PlayItemInfo.mi;

    //title
    m_pTitlebar = new DTitlebar(this);
    m_pTitlebar->setFixedHeight(50);
    m_pTitlebar->layout()->setContentsMargins(0, 0, 0, 0);
    m_pTitlebar->setMenuVisible(false);
    m_pTitlebar->setIcon(QIcon::fromTheme("deepin-movie"));
    //参考设计图
    m_pTitlebar->setFixedWidth(590);
    m_pTitlebar->setTitle(strMovieInfo.title);
    m_pTitlebar->setBackgroundTransparent(true);
    //参考设计图
    setFixedSize(600, 700);
    const int nStretch = 1;
    //title bottom
    QHBoxLayout *pTitleLayout = new QHBoxLayout;
    pTitleLayout->setContentsMargins(0, 0, 0, 0);
    pTitleLayout->setSpacing(0);
    pTitleLayout->addStretch(nStretch);
    {
        QLabel *pDurationLabel = new QLabel(tr("Duration: %1").arg(strMovieInfo.durationStr()), this);
        pTitleLayout->addWidget(pDurationLabel);
        pTitleLayout->addStretch(nStretch);
    }
    {
        QLabel *pResolutionLabel = new QLabel(tr("Resolution: %1").arg(strMovieInfo.resolution), this);
        pTitleLayout->addWidget(pResolutionLabel);
        pTitleLayout->addStretch(nStretch);
    }
    {
        QLabel *pSizeLabel = new QLabel(tr("Size: %1").arg(strMovieInfo.sizeStr()), this);
        pTitleLayout->addWidget(pSizeLabel);
        pTitleLayout->addStretch(nStretch);
    }

    // main content
    QVBoxLayout *pMainContent = new QVBoxLayout;
    pMainContent->setContentsMargins(0, 10, 0, 0);

    m_pGrid = new QGridLayout();
    //参考设计图
    m_pGrid->setHorizontalSpacing(12);
    m_pGrid->setVerticalSpacing(15);
    m_pGrid->setContentsMargins(0, 0, 0, 0);
    pMainContent->addLayout(m_pGrid);
    m_pGrid->setColumnMinimumWidth(0, 160);
    m_pGrid->setColumnMinimumWidth(1, 160);
    m_pGrid->setColumnMinimumWidth(2, 160);

    QHBoxLayout *pButtonContent = new QHBoxLayout;
    pButtonContent->setContentsMargins(0, 13, 0, 0);
    pButtonContent->addStretch(1);

    m_pSaveBtn = new QPushButton(tr("Save"));
    m_pSaveBtn->setObjectName("SaveBtn");
    connect(m_pSaveBtn, &QPushButton::clicked, this, &BurstScreenshotsDialog::savePoster);
    m_pSaveBtn->setFixedSize(70, 30);
    m_pSaveBtn->setDefault(true);
    pButtonContent->addWidget(m_pSaveBtn);
    pMainContent->addLayout(pButtonContent);
    QVBoxLayout *pMainlayout = new QVBoxLayout;
    pMainlayout->setContentsMargins(10, 0, 10, 15);
    pMainlayout->setSpacing(0);
    pMainlayout->addWidget(m_pTitlebar);
    pMainlayout->addLayout(pTitleLayout);
    pMainlayout->addLayout(pMainContent);

    setLayout(pMainlayout);

#ifdef DTKWIDGET_CLASS_DSizeMode
    if (DGuiApplicationHelper::instance()->sizeMode() == DGuiApplicationHelper::CompactMode) {
        m_pTitlebar->setFixedSize(389, 33);
        setFixedSize(396, 462);
        m_pGrid->setHorizontalSpacing(8);
        m_pGrid->setVerticalSpacing(10);
        m_pSaveBtn->setFixedSize(46, 20);
        pMainlayout->setContentsMargins(7, 0, 7, 10);
    }

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::sizeModeChanged, this, [=](DGuiApplicationHelper::SizeMode sizeMode) {
        if (sizeMode == DGuiApplicationHelper::NormalMode) {
            m_pTitlebar->setFixedSize(590, 50);
            setFixedSize(600, 700);
            m_pGrid->setHorizontalSpacing(12);
            m_pGrid->setVerticalSpacing(15);
            m_pSaveBtn->setFixedSize(70, 30);
            layout()->setContentsMargins(10, 0, 10, 15);
        } else {
            m_pTitlebar->setFixedSize(389, 33);
            setFixedSize(396, 462);
            m_pGrid->setHorizontalSpacing(8);
            m_pGrid->setVerticalSpacing(10);
            m_pSaveBtn->setFixedSize(46, 20);
            layout()->setContentsMargins(7, 0, 7, 10);
        }
        this->moveToCenter();
    });
#endif
}

/**
 * @brief updateWithFrames 更新截图图像
 * @param frames 截图图像
 */
void BurstScreenshotsDialog::updateWithFrames(const QList<QPair<QImage, qint64>> &frames)
{
    qreal devicePixelRatio = qApp->devicePixelRatio();
    //参考设计图
    QSize size(static_cast<int>(178 * devicePixelRatio), static_cast<int>(100 * devicePixelRatio));

    int nCount = 0;
    QImage scaled;
    for (auto frame : frames) {
        QImage image = frame.first;
        ThumbnailFrame *pThumbnailFrame = new ThumbnailFrame(this);

        int nRowCount = nCount / 3;
        int nColumn = nCount % 3;

        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap = pixmap.scaled(size.width() - 2, size.height() - 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
#ifdef DTKWIDGET_CLASS_DSizeMode
    if (DGuiApplicationHelper::instance()->sizeMode() == DGuiApplicationHelper::CompactMode) {
        pThumbnailFrame->setFixedSize(118, 67);
        pixmap = pixmap.scaled(pixmap.width() * 0.66, pixmap.height() * 0.66, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmap = utils::MakeRoundedPixmap(size*0.66, pixmap, 2, 2, frame.second);
    } else {
        pixmap = utils::MakeRoundedPixmap(size, pixmap, 2, 2, frame.second);
    }

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::sizeModeChanged, pThumbnailFrame, [=](DGuiApplicationHelper::SizeMode sizeMode) {
        if (sizeMode == DGuiApplicationHelper::NormalMode) {
            pThumbnailFrame->setFixedSize(178, 100);
            auto pixmap = pThumbnailFrame->pixmap();
            auto new_pix = pixmap->scaled(178, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//            new_pix = utils::MakeRoundedPixmap(QSize(180, 102), new_pix, 2, 2, frame.second);
            pThumbnailFrame->setPixmap(new_pix);
        } else {
            pThumbnailFrame->setFixedSize(118, 67);
            auto pixmap = pThumbnailFrame->pixmap();
            auto new_pix = pixmap->scaled(118, 67, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//            new_pix = utils::MakeRoundedPixmap(QSize(120, 69), new_pix, 2, 2, frame.second);
            pThumbnailFrame->setPixmap(new_pix);
        }
    });
#else
        pixmap = utils::MakeRoundedPixmap(size, pixmap, 2, 2, frame.second);
#endif
    pixmap.setDevicePixelRatio(devicePixelRatio);
    pThumbnailFrame->setAlignment(Qt::AlignCenter);
    pThumbnailFrame->setPixmap(pixmap);
    m_pGrid->addWidget(pThumbnailFrame, nRowCount, nColumn);
    nCount++;
    }
}

/**
 * @brief exec 返回执行函数的标识符
 * @return 执行函数的标识符
 */
int BurstScreenshotsDialog::exec()
{
    return DAbstractDialog::exec();
}

/**
 * @brief savePoster 保存截图
 */
void BurstScreenshotsDialog::savePoster()
{
    //参考设计图
    m_pTitlebar->setFixedWidth(610);
    QPixmap img = this->grab(rect().marginsRemoved(QMargins(10, 0, 10, 45)));
    m_sPosterPath = Settings::get().screenshotNameTemplate();
    img.save(m_sPosterPath);
    DAbstractDialog::accept();
}

/**
 * @brief savedPosterPath 保存截图路径
 * @return 返回设置的截图保存路径
 */
QString BurstScreenshotsDialog::savedPosterPath()
{
    return m_sPosterPath;
}

}

