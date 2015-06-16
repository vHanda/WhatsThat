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

#include "sendmessagejob.h"
#include "jsinterface.h"

#include <QTimer>

using namespace WhatsThat;

class SendMessageJob::Private {
public:
    QString m_message;
    JsInterface* m_jsInterface;
};

SendMessageJob::SendMessageJob(JsInterface* jsInterface, const QString& id, const QString& message, QObject* parent)
    : QObject(parent)
    , d(new Private)
{
    d->m_jsInterface = jsInterface;
    d->m_message = message;

    connect(d->m_jsInterface, &JsInterface::currentChatChanged, this, &SendMessageJob::slotCurrentChatChanged);
    QMetaObject::invokeMethod(d->m_jsInterface, "changeCurrentChat", Qt::QueuedConnection, Q_ARG(QString, id));
}

SendMessageJob::~SendMessageJob()
{
    delete d;
}

void SendMessageJob::slotCurrentChatChanged()
{
    QMetaObject::invokeMethod(d->m_jsInterface, "sendMessage", Qt::QueuedConnection, Q_ARG(QString, d->m_message));

    // FIXME: Monitor the messageList changed signal?
    QTimer::singleShot(1000, this, SLOT(slotMessageListChanged()));
}

void SendMessageJob::slotMessageListChanged()
{
    Q_EMIT done(this);
    deleteLater();
}

