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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QThread>

#include "interface.h"
#include "chatlistjob.h"
#include "sendmessagejob.h"
#include "chat.h"

class Console : public QThread
{
    Q_OBJECT
public:
    Console(WhatsThat::Interface* interface, QObject* parent = 0);

public Q_SLOTS:
    void run();

private Q_SLOTS:
    void handleCommand(const QByteArray& command);

private:
    WhatsThat::Interface* m_interface;
    QList<WhatsThat::Chat*> m_chatList;
};

#endif // CONSOLE_H
