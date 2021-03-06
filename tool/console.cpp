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

#include "console.h"

extern "C" {
    #include "linenoise.h"
}

#include <QDebug>
#include <QByteArray>
#include <QCoreApplication>

#include <iostream>
#include <stdio.h>

using namespace WhatsThat;

Console::Console(WhatsThat::Interface* interface, QObject* parent)
    : QThread(parent)
    , m_interface(interface)
{
    connect(interface, &Interface::loaded, [&]() {
        QTextStream stream(stdout);
        stream << "Loaded\r\n";
    });
    connect(interface, &Interface::authRequired, [&](const QString& img) {
        QTextStream stream(stdout);
        stream << "Needs Auth: " << img << "\r\n";
    });

    /*
    connect(m_interface, &WhatsAppJsInterface::chatListChanged, [&]() {
        QVariantList list = m_interface->chatList().toList();

        QTextStream stream(stdout);
        for (int i = 0; i < list.size(); i++) {
            QVariantMap map = list[i].toMap();

            const QString title = map.value("title").toString();
            stream << "[" << i << "] " << title << "\r\n";
        }
    });

    connect(m_interface, &WhatsAppJsInterface::messageListChanged, [&]() {
        QVariantList list = m_interface->messageList().toList();

        QTextStream stream(stdout);
        for (int i = 0; i < list.size(); i++) {
            QVariantMap map = list[i].toMap();

            const QString date = map.value("date").toString();
            const QString time = map.value("time").toString();
            const QString author = map.value("author").toString();
            const QString text = map.value("text").toString();

            stream << "[" << date << " " << time << "] " << author << ": " << text << "\r\n";
        }
    });
    */
}

void Console::run()
{
    char* line = 0;

    while ((line = ::linenoise("> ")) != 0) {
        QByteArray input(line);
        free(line);

        if (input.isEmpty())
            continue;

        linenoiseHistoryAdd(input.constData());

        if (input == "quit") {
            QMetaObject::invokeMethod(QCoreApplication::instance(), "quit", Qt::QueuedConnection);
            return;
        }

        QMetaObject::invokeMethod(this, "handleCommand", Qt::QueuedConnection, Q_ARG(QByteArray, input));
    }
}
void Console::handleCommand(const QByteArray& input)
{
    QTextStream stream(stdout);

    if (input == "show") {
        QMetaObject::invokeMethod(m_interface, "show", Qt::QueuedConnection);
        return;
    }
    if (input == "hide") {
        QMetaObject::invokeMethod(m_interface, "hide", Qt::QueuedConnection);
        return;
    }

    if (input == "chatList") {
        auto job = m_interface->generateChatList();
        connect(job, &ChatListJob::done, [this](ChatListJob* listJob) {
            m_chatList = listJob->chatList();

            QTextStream stream(stdout);
            for (int i = 0; i < m_chatList.size(); i++) {
                Chat* chat = m_chatList.at(i);
                stream << "[" << i << "] " << chat->title() << "\r\n";

                connect(chat, &Chat::messageReceived, [](Chat* chat, const Message& msg) {
                    QTextStream stream(stdout);
                    stream << "Received [Chat: " << chat->title() << "] ["
                           << msg.dateTime().toString(Qt::ISODate) << " " << msg.author() << "] "
                           << msg.text() << "\r\n";
                });
            }
        });
        return;
    }

    if (input.startsWith("send")) {
        QString str = QString::fromUtf8(input.mid(5));
        QTextStream stream(&str);

        int index;
        stream >> index;
        QString text = stream.readAll().mid(1);

        Chat* chat = m_chatList.at(index);
        Message msg = Message::createTextMessage(text);
        auto job = chat->sendMessage(msg);
        connect(job, &SendMessageJob::done, [](SendMessageJob* job) {
            Q_UNUSED(job);
        });
    }
        /*
        if (input == "showContactList") {
            QMetaObject::invokeMethod(m_interface, "showContactListInvoked", Qt::QueuedConnection);
        }
        else if (input == "hideContactList") {
            QMetaObject::invokeMethod(m_interface, "hideContactListInvoked", Qt::QueuedConnection);
        }
        else if (input == "chatList") {
            QMetaObject::invokeMethod(m_interface, "populateChatList", Qt::QueuedConnection);
        }
        else if (input.startsWith("chat")) {
            int index = input.mid(5).simplified().toInt();
            QVariantMap map = m_interface->chatList().toList()[index].toMap();

            QString id = map.value("id").toString();
            QMetaObject::invokeMethod(m_interface, "setCurrentChat", Qt::QueuedConnection, Q_ARG(QString, id));
        }
        else if (input == "messageList") {
            QMetaObject::invokeMethod(m_interface, "populateMessageList", Qt::QueuedConnection);
        }
        else if (input.startsWith("send")) {
            QString message = input.mid(5).trimmed();

            QMetaObject::invokeMethod(m_interface, "sendMessage", Qt::QueuedConnection, Q_ARG(QString, message));
        }
        else {
            qDebug() << "Unknown command\r";
        }
        */
}


