#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QDialog>

class QRCodeWidget : public QDialog {
    Q_OBJECT
public:
    explicit QRCodeWidget(const QString &url, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:
    QImage m_qrImage;
};

#endif // QRCODEWIDGET_H