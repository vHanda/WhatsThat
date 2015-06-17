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

#include "chat.h"
#include "jsinterface.h"
#include "sendmessagejob.h"
#include "message.h"

using namespace WhatsThat;

class Chat::Private {
public:
    JsInterface* m_jsInterface;
    QString m_title;
    QString m_id;
    QUrl m_avatar;
};

Chat::Chat(JsInterface* jsInterface, const QString& title, const QString& id,
           const QUrl& avatarUrl, QObject* parent)
    : QObject(parent)
    , d(new Private)
{
    d->m_jsInterface = jsInterface;
    d->m_title = title;
    d->m_id = id;
    d->m_avatar = avatarUrl;
}

Chat::~Chat()
{
    delete d;
}

QString Chat::title() const
{
    return d->m_title;
}

QUrl Chat::avatar() const
{
    return d->m_avatar;
}

SendMessageJob* Chat::sendMessage(const Message& message)
{
    return new SendMessageJob(d->m_jsInterface, d->m_id, message, this);
}

