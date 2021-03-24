/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     cutefish <cutefishos@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "meuikit.h"
#include "thememanager.h"
#include "iconthemeprovider.h"
#include "shadowhelper/windowshadow.h"
#include "blurhelper/windowblur.h"
#include "windowhelper.h"
#include "iconitem.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQuickStyle>

void MeuiKit::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("MeuiKit"));

    // Set base URL to the plugin URL
    engine->setBaseUrl(baseUrl());

    // For system icons
    engine->addImageProvider(QStringLiteral("icontheme"), new IconThemeProvider());
}

void MeuiKit::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("MeuiKit"));

    qmlRegisterSingletonType<ThemeManager>("MeuiKit.Core", 1, 0, "ThemeManager", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new ThemeManager;
    });

    qmlRegisterType<WindowShadow>(uri, 1, 0, "WindowShadow");
    qmlRegisterType<WindowBlur>(uri, 1, 0, "WindowBlur");
    qmlRegisterType<WindowHelper>(uri, 1, 0, "WindowHelper");
    qmlRegisterType<IconItem>(uri, 1, 0, "IconItem");

    qmlRegisterSingletonType(componentUrl(QStringLiteral("Theme.qml")), uri, 1, 0, "Theme");
    qmlRegisterSingletonType(componentUrl(QStringLiteral("Units.qml")), uri, 1, 0, "Units");

    qmlRegisterType(componentUrl(QStringLiteral("BusyIndicator.qml")), uri, 1, 0, "BusyIndicator");
    qmlRegisterType(componentUrl(QStringLiteral("Icon.qml")), uri, 1, 0, "Icon");
    qmlRegisterType(componentUrl(QStringLiteral("MouseHover.qml")), uri, 1, 0, "MouseHover");
    qmlRegisterType(componentUrl(QStringLiteral("PopupTips.qml")), uri, 1, 0, "PopupTips");
    qmlRegisterType(componentUrl(QStringLiteral("RoundedRect.qml")), uri, 1, 0, "RoundedRect");
    qmlRegisterType(componentUrl(QStringLiteral("Toast.qml")), uri, 1, 0, "Toast");
    qmlRegisterType(componentUrl(QStringLiteral("Window.qml")), uri, 1, 0, "Window");
    qmlRegisterType(componentUrl(QStringLiteral("WindowButton.qml")), uri, 1, 0, "WindowButton");

    qmlProtectModule(uri, 1);
}

QUrl MeuiKit::componentUrl(const QString &fileName) const
{
    return QUrl(QStringLiteral("qrc:/meui/kit/") + fileName);
}
