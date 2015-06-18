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
#include <QUrl>

namespace WhatsThat {

class Message;
class ChatListJob;
class SendMessageJob;
class JsInterface;

class WHATSTHAT_EXPORT Chat : public QObject
{
    Q_OBJECT
public:
    ~Chat();

    QString title() const;
    QUrl avatar() const;

    SendMessageJob* sendMessage(const Message& message);

Q_SIGNALS:
    void messageReceived(Chat* chat, const Message& message);

private Q_SLOTS:
    void slotRefreshMessages();

private:
    Chat(JsInterface* jsInterface, const QString& title, const QString& id, const QUrl& avatarUrl, QObject* parent = 0);
    Chat(const Chat& rhs) = delete;
    Chat& operator=(const Chat& rhs) = delete;

    class Private;
    Private* d;

    friend class ChatListJob;
};
}

#endif // WHATSTHAT_CHAT_H
