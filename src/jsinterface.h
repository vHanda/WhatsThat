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

#ifndef WHATSAPPWEBJSINTERFACE_H
#define WHATSAPPWEBJSINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QDebug>

namespace WhatsThat {

class JsInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList contactList READ contactList NOTIFY contactListChanged)

    Q_PROPERTY(QVariant chatList READ chatList WRITE setChatList NOTIFY chatListChanged)
    Q_PROPERTY(QString currentChat READ currentChat WRITE setCurrentChat NOTIFY currentChatChanged)

    Q_PROPERTY(QVariant messageList READ messageList WRITE setMessageList NOTIFY messageListChanged)
public:
    explicit JsInterface(QObject* parent = 0);

    QVariantList contactList() const {
        return m_contactList;
    }

    QVariant chatList() const;
    QString currentChat() const;
    QVariant messageList() const;

    void setChatList(const QVariant& var);
    void setMessageList(const QVariant& var);

Q_SIGNALS:
    void showContactListInvoked();
    void hideContactListInvoked();
    void populateChatList();
    void populateMessageList();

    void contactListChanged();
    void chatListChanged();
    void currentChatChanged();
    void messageListChanged();

    void loaded();

    // Sending messages
    void sendMessage(const QString& message);
    void keyboardEventInjected();

    void nativeInjectKeyboardEvent();

public Q_SLOTS:
    void showContactListCallback();
    void hideContactListCallback();

    void setCurrentChat(const QString& chatId);

    void emitLoaded();

    void jsInjectKeyboardEvent();

private:
    QVariantList m_contactList;

    QVariant m_chatList;
    QString m_currentChat;
    QVariant m_messageList;
};

}

#endif // WHATSAPPWEBINTERFACE_H
