/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#ifdef SAILFISHAPP
//FIXME, get path properly.
#include <sailfishapp.h>
#else
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QUrl>
#endif

#ifdef HAS_BOOSTER
// use SailfishOS booster (see desktop file)
// X-Nemo-Application-Type=silica-qt5
#include <QScopedPointer>
#include <MDeclarativeCache>
#endif

#ifdef SAILFISHAPP // Example 1: use libsailfishapp
int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/cmakesample.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    return SailfishApp::main(argc, argv);
}

#else // Example 2: generic example without using libsailfishapp
Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifdef HAS_BOOSTER
    QScopedPointer<QGuiApplication> app_ptr(MDeclarativeCache::qApplication(argc, argv));
    QGuiApplication& app = *app_ptr;
    QScopedPointer<QQuickView> view_ptr();
    QQuickView& view = *view_ptr;
#else
    QGuiApplication app(argc, argv);
    QQuickView view;
#endif

    app.setOrganizationName(QStringLiteral("cmakesample"));
    app.setOrganizationDomain(QStringLiteral("cmakesample"));
    app.setApplicationName(QStringLiteral("cmakesample"));
    app.setApplicationVersion(QStringLiteral("1.0"));

    // this allows for translucency in your main view
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQmlEngine& engine = *(view.engine());
    QObject::connect(&engine, &QQmlEngine::quit, &app, &QGuiApplication::quit);
    engine.addImportPath("/usr/share/cmakesample/qml");

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile("/usr/share/cmakesample/qml/cmakesample_generic.qml"));
    view.showFullScreen();

    return app.exec();
}
#endif
