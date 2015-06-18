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

#include "chatlistjob.h"
#include "chat.h"

#include "jsinterface.h"

#include <QMetaObject>
#include <QUrl>

using namespace WhatsThat;

class ChatListJob::Private {
public:
    JsInterface* m_jsInterface;
    QList<Chat*> m_chatList;
};

ChatListJob::ChatListJob(JsInterface* jsInterface, QObject* parent)
    : QObject(parent)
    , d(new Private)
{
    d->m_jsInterface = jsInterface;
    connect(d->m_jsInterface, &JsInterface::chatListChanged, this, &ChatListJob::slotChatListChanged);

    QMetaObject::invokeMethod(d->m_jsInterface, "populateChatList", Qt::QueuedConnection);
}

ChatListJob::~ChatListJob()
{
    delete d;
}

QList<Chat*> ChatListJob::chatList() const
{
    return d->m_chatList;
}

void ChatListJob::slotChatListChanged()
{
    Q_ASSERT(d->m_chatList.isEmpty());

    QVariantList list = d->m_jsInterface->chatList().toList();
    for (int i = 0; i < list.size(); i++) {
        QVariantMap map = list[i].toMap();

        QString title = map.value("title").toString();
        QUrl avatar = map.value("avatar").toUrl();
        QString id = map.value("id").toString();
        int unread = map.value("unread").toInt();

        Chat* chat = new Chat(d->m_jsInterface, title, id, avatar, unread, parent());
        d->m_chatList << chat;
    }

    Q_EMIT done(this);
    deleteLater();
}
