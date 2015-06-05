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

class WhatsAppJsInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList contactList READ contactList NOTIFY contactListChanged)

    Q_PROPERTY(QVariant chatList READ chatList WRITE setChatList NOTIFY chatListChanged)
    Q_PROPERTY(QString currentChat READ currentChat WRITE setCurrentChat NOTIFY currentChatChanged)
public:
    explicit WhatsAppJsInterface(QObject* parent = 0);

    QVariantList contactList() const {
        return m_contactList;
    }

    QVariant chatList() const {
        return m_chatList;
    }

    void setChatList(const QVariant& var) {
        m_chatList = var;
        Q_EMIT chatListChanged();
    }

    QString currentChat() const;

Q_SIGNALS:
    void showContactListInvoked();
    void hideContactListInvoked();
    void populateChatList();

    void contactListChanged();
    void chatListChanged();
    void currentChatChanged();

public Q_SLOTS:
    void showContactListCallback();
    void hideContactListCallback();

    void setCurrentChat(const QString& chatId);

private:
    QVariantList m_contactList;

    QVariant m_chatList;
    QString m_currentChat;
};

#endif // WHATSAPPWEBINTERFACE_H
