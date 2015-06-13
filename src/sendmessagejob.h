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

#ifndef WHATSTHAT_SENDMESSAGEJOB_H
#define WHATSTHAT_SENDMESSAGEJOB_H

#include "whatsthat_export.h"
#include <QObject>

namespace WhatsThat {

class JsInterface;
class Chat;

class WHATSTHAT_EXPORT SendMessageJob : public QObject
{
    Q_OBJECT
public:
    ~SendMessageJob();

Q_SIGNALS:
    // deletes itself after done
    void done();

private Q_SLOTS:
    void slotMessageListChanged();

private:
    SendMessageJob(JsInterface* jsInterface, const QString& id, const QString& message, QObject* parent = 0);
    SendMessageJob(const SendMessageJob& rhs) = delete;
    SendMessageJob& operator=(const SendMessageJob& rhs) = delete;

    class Private;
    Private* d;

    friend class Chat;
};

}

#endif // WHATSTHAT_SENDMESSAGEJOB_H
