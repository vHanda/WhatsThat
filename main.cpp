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

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>

/*
class UserAgentWebPage : public QWebPage
{
public:
    explicit UserAgentWebPage(QObject* parent = 0) : QWebPage(parent) {}
private:
    QString userAgentForUrl(const QUrl &url) const {
        qDebug() << url;
        return QLatin1String("Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36");
    }
};
*/

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWebEngineView view;
    view.load(QUrl("https://web.whatsapp.com"));
    view.show();

    QObject::connect(&view, &QWebEngineView::loadFinished, [&](bool) {
        qDebug() << "Loaded";
    });
    return app.exec();
}
