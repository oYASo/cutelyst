#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QHostAddress>
#include <Cutelyst/Headers>

class QIODevice;

namespace CWSGI {

class CWsgiEngine;
class Socket
{
public:
    Socket();
    virtual ~Socket();

    inline void resetSocket() {
        buffer = QByteArray();

        buf_size = 0;
        connState = 0;
        beginLine = 0;
        last = 0;
        headerClose = 0;
        processing = false;
    }

    Cutelyst::Headers headers;
    QString serverAddress;
    QString method;
    QString path;
    QByteArray query;
    QString protocol;
    QByteArray buffer;
    quint64 start;
    CWsgiEngine *engine;
    char *buf;
    int buf_size = 0;
    int connState = 0;
    int beginLine = 0;
    int last = 0;
    int headerClose = 0;
    bool processing = false;
};

class TcpSocket : public QTcpSocket, public Socket
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);

    void socketDisconnected();

Q_SIGNALS:
    void finished();
};

}

#endif // SOCKET_H
