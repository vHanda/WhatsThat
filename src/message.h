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

#ifndef WHATSTHAT_MESSAGE_H
#define WHATSTHAT_MESSAGE_H

#include "whatsthat_export.h"
#include <QString>
#include <QDateTime>

namespace WhatsThat {

class WHATSTHAT_EXPORT Message
{
public:
    Message();
    Message(const Message& rhs);
    ~Message();

    Message& operator=(const Message& rhs);
    bool operator==(const Message& rhs) const;

    QString text() const;
    QDateTime dateTime() const;

    // FIXME: Having the author be a QString is strange. We need to map it to contacts!
    QString author() const;

    static Message createTextMessage(const QString& text);
    static Message createTextMessage(const QString& text, const QDateTime& dt, const QString& author);
private:
    class Private;
    Private* d;
};
}

#endif // WHATSTHAT_MESSAGE_H
