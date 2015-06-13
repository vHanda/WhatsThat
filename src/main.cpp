/*
 * Copyright (C) 2015 Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QThread>
#include <QKeyEvent>
#include <QWindow>

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineProfile>

#include <QtWebChannel/QWebChannel>

#include "whatsappjsinterface.h"
#include "console.h"

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

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/kde-whatsapp");
    QDir().mkpath(dataPath);

    QWebEngineProfile profile;
    profile.setHttpUserAgent("Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2224.3 Safari/537.36");
    profile.setCachePath(dataPath + "/cache");
    profile.setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile.setPersistentStoragePath(dataPath + "/storage");
    profile.setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

    CustomWebPage page(&profile);

    QWebEngineView view;
    view.setPage(&page);
    view.load(QUrl("https://web.whatsapp.com"));
    view.show();

    QObject::connect(&view, &QWebEngineView::loadFinished, [&](bool) {
        page.runJavaScriptFile(":/qtwebchannel/qwebchannel.js");
        page.runJavaScriptFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "whatsapptest/jquery.js"));
        page.runJavaScriptFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "whatsapptest/webChan.js"));
    });


    QWebChannel* chan = new QWebChannel();
    page.setWebChannel(chan);

    WhatsAppJsInterface interface;
    chan->registerObject("whatsAppInterface", &interface);

    QObject::connect(&interface, &WhatsAppJsInterface::nativeInjectKeyboardEvent, [&]() {
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " ");
            QWindow* window = view.windowHandle();
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Space, Qt::NoModifier, " ");
            QWindow* window = view.windowHandle();
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, "");
            QWindow* window = view.windowHandle();
            QGuiApplication::sendEvent(window, event);
        }
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier, "");
            QWindow* window = view.windowHandle();
            QGuiApplication::sendEvent(window, event);
        }
    });

    // We shouldn't need to have to call 'emit' in order to interact with the interface
    // there probably should be a wrapper on top of this that converts it into a nice C++
    // interface

    QThread thread;
    thread.start();

    Console console(&interface);
    console.moveToThread(&thread);

    QTimer::singleShot(0, &console, SLOT(startLoop()));

    return app.exec();
}
