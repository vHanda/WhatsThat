/*
 * <one line to give the library's name and an idea of what it does.>
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

#ifndef WHATSTHAT_CHATLISTJOB_H
#define WHATSTHAT_CHATLISTJOB_H

#include "whatsthat_export.h"
#include <QObject>

namespace WhatsThat {

class Chat;

class WHATSTHAT_EXPORT ChatListJob : public QObject
{
    Q_OBJECT
public:
    explicit ChatListJob(QObject* parent = 0);
    ~ChatListJob();

    QList<Chat*> chatList() const;

Q_SIGNALS:
    void done();

private:
    ChatListJob(const ChatListJob& rhs) = delete;
    ChatListJob& operator=(const ChatListJob& rhs) = delete;

    class Private;
    Private* d;
};
}

#endif // WHATSTHAT_CHATLISTJOB_H
