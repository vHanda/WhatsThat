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

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineProfile>

#include <QtWebChannel/QWebChannel>

#include "whatsappjsinterface.h"

class CustomWebPage : public QWebEnginePage {
public:
    CustomWebPage(QWebEngineProfile* profile, QObject* parent = 0)
        : QWebEnginePage(profile, parent)
    {}

protected:
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID) {
        qDebug() << "JS:" << lineNumber << message;
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
        qDebug() << "Loaded";

        {
            QFile file(":/qtwebchannel/qwebchannel.js");
            file.open(QIODevice::ReadOnly);
            QString contents = QString::fromUtf8(file.readAll());

            page.runJavaScript(contents);
        }

        // FIXME: We need to load jQuery as well!
        {
            QFile file("webChan.js");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QString contents = QString::fromUtf8(file.readAll());

            qDebug() << "Running" << contents;
            page.runJavaScript(contents);
        }
    });


    QWebChannel* chan = new QWebChannel();
    page.setWebChannel(chan);

    WhatsAppJsInterface interface;
    chan->registerObject("whatsAppInterface", &interface);

    // We shouldn't need to have to call 'emit' in order to interact with the interface
    // there probably should be a wrapper on top of this that converts it into a nice C++
    // interface
    emit interface.showContactListInvoked();

    return app.exec();
}
