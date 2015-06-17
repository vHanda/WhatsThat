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

#include "message.h"

using namespace WhatsThat;

class Message::Private {
public:
    QString m_text;
};

Message::Message()
    : d(new Private)
{
}

Message::~Message()
{
    delete d;
}

Message::Message(const Message& rhs)
    : d(new Private(*rhs.d))
{
}

Message& Message::operator=(const Message& rhs)
{
    delete d;
    d = new Private(*rhs.d);
    return *this;
}

bool Message::operator==(const Message& rhs) const
{
    return d->m_text == rhs.d->m_text;
}

QString Message::text() const
{
    return d->m_text;
}

// static
Message Message::createTextMessage(const QString& text)
{
    Message msg;
    msg.d->m_text = text;

    return msg;
}
