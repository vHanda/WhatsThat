/*
 * Copyright (C) 2015  Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef WHATSTHAT_CHAT_H
#define WHATSTHAT_CHAT_H

#include "whatsthat_export.h"
#include <QObject>
#include <QDateTime>

namespace WhatsThat {

class SendMessageJob;

class WHATSTHAT_EXPORT Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject* parent = 0);
    ~Chat();

    SendMessageJob* sendMessage(const QString& message);

Q_SIGNALS:
    // FIXME: Create a proper Message class.
    //        A message can be a voice note / image / video / emoticon / etc
    void messageReceived(const QString& senderId, const QDateTime& dt, const QString& message);

private:
    Chat(const Chat& rhs) = delete;
    Chat& operator=(const Chat& rhs) = delete;

    class Private;
    Private* d;
};
}

#endif // WHATSTHAT_CHAT_H
