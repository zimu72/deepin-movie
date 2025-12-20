#include "qrcodewidget.h"
#include <qrencode.h>
#include <QPainter>

QRCodeWidget::QRCodeWidget(const QString &url, QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle(tr("Scan QR Code"));
    setFixedSize(300, 300);
    
    QRcode *qrcode = QRcode_encodeString(url.toUtf8().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    m_qrImage = QImage(qrcode->width + 8, qrcode->width + 8, QImage::Format_ARGB32);
    m_qrImage.fill(Qt::white);
    
    unsigned char *p = qrcode->data;
    for(int y=0; y<qrcode->width; y++) {
        for(int x=0; x<qrcode->width; x++) {
            m_qrImage.setPixel(x+4, y+4, (*p & 1) ? qRgb(255, 255, 255) : qRgb(0, 0, 0));
            p++;
        }
    }
    QRcode_free(qrcode);
}

void QRCodeWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(rect(), m_qrImage.scaled(size(), Qt::KeepAspectRatio));
}
