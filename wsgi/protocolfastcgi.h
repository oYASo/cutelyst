/*
 * Copyright (C) 2017 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef PROTOCOLFASTCGI_H
#define PROTOCOLFASTCGI_H

#include <QObject>

#include "protocol.h"

namespace CWSGI {

class WSGI;
class ProtocolFastCGI : public Protocol
{
    Q_OBJECT
public:
    explicit ProtocolFastCGI(TcpSocket *sock, WSGI *wsgi, QObject *parent = nullptr);
    virtual ~ProtocolFastCGI();

    virtual void readyRead() override;
    virtual bool sendHeaders(TcpSocket *sock, quint16 status, const QByteArray &dateHeader, const Headers &headers) override;
    qint64 sendBody(TcpSocket *sock, const char *data, qint64 len) override;

private:
    inline quint16 addHeader(Socket *wsgi_req, char *key, quint16 keylen, char *val, quint16 vallen);
    inline int parseHeaders(Socket *wsgi_req, char *buf, size_t len);
    inline int processPacket(TcpSocket *sock);
    inline int writeBody(Socket *sock, char *buf, size_t len);
    // write a STDOUT packet
    int wsgi_proto_fastcgi_write(TcpSocket *wsgi_req, const char *buf, int len);

    QByteArray m_headerBuffer;
    qint64 m_postBufferSize;
    qint64 m_bufferSize;
    qint64 m_postBuffering;
    char *m_postBuffer;
};

}

#endif // PROTOCOLFASTCGI_H
