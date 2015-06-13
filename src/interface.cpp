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

#include "interface.h"
#include "whatsappjsinterface.h"

#include <QGuiApplication>
#include <QStandardPaths>
#include <QKeyEvent>
#include <QWindow>
#include <QDir>

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineProfile>

#include <QtWebChannel/QWebChannel>

#include "whatsappjsinterface.h"

using namespace WhatsThat;

class CustomWebPage : public QWebEnginePage {
public:
    CustomWebPage(QWebEngineProfile* profile, QObject* parent = 0)
        : QWebEnginePage(profile, parent)
    {}

    void runJavaScriptFile(const QString& path) {
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        Q_ASSERT(file.isOpen());
        QString contents = QString::fromUtf8(file.readAll());

        runJavaScript(contents);
    }
protected:
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID) {
        qDebug() << "JS Error:" << sourceID << lineNumber << message << "\r";
    }
};

class Interface::Private {
public:

    QWebEngineView* m_view;
    CustomWebPage* m_page;
    WhatsAppJsInterface* m_jsInterface;
};

WhatsThat::Interface::Interface(QObject* parent)
    : QObject(parent)
    , d(new Private)
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/whatsthat");
    QDir().mkpath(dataPath);

    QWebEngineProfile* profile = new QWebEngineProfile(this);
    profile->setHttpUserAgent("Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2224.3 Safari/537.36");
    profile->setCachePath(dataPath + "/cache");
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentStoragePath(dataPath + "/storage");
    profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

    d->m_page = new CustomWebPage(profile, this);
    d->m_view = new QWebEngineView();
    d->m_view->setPage(d->m_page);
    d->m_view->load(QUrl("https://web.whatsapp.com"));
    d->m_view->show();

    connect(d->m_view, &QWebEngineView::loadFinished, [&](bool) {
        d->m_page->runJavaScriptFile(":/qtwebchannel/qwebchannel.js");
        d->m_page->runJavaScriptFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "whatsthat/jquery.js"));
        d->m_page->runJavaScriptFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "whatsthat/webChan.js"));
    });

    d->m_jsInterface = new WhatsAppJsInterface(this);

    QWebChannel* chan = new QWebChannel();
    d->m_page->setWebChannel(chan);

    chan->registerObject("whatsAppInterface", d->m_jsInterface);
    connect(d->m_jsInterface, &WhatsAppJsInterface::nativeInjectKeyboardEvent, [&]() {
        QWindow* window = d->m_view->windowHandle();
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " ");
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Space, Qt::NoModifier, " ");
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, "");
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier, "");
            QGuiApplication::sendEvent(window, event);
        }
    });

    // FIXME: This emits too many signals!
    connect(d->m_jsInterface, &WhatsAppJsInterface::loaded, this, &Interface::loaded);
}

WhatsThat::Interface::~Interface()
{
    delete d->m_view;
    delete d;
}

ChatListJob* Interface::generateChatList()
{
    return 0;
}
