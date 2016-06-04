#ifndef QCAN_CLIENT_HPP_
#define QCAN_CLIENT_HPP_

#include <QObject>
#include <QUdpSocket>

#include "qcan_defs.hpp"
#include "qcan_frame.hpp"


class QCanClient : public QObject
{
    Q_OBJECT

public:
    QCanClient(QObject *parent = 0);
    ~QCanClient();

public:

private:

   QUdpSocket *   pclRcvSocketP;
   QUdpSocket *   pclTrmSocketP;


   int32_t  sendDatagram(QCanFrame & clCanFrameR);
   int32_t  receiveDatagram(const QCanFrame & clCanFrameR);
   
};

#endif // QCAN_CLIENT_HPP_
