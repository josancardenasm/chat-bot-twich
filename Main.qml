// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.5
import QtQuick.Controls 6.5

Window {
    id: mainWindow
    width: 1920
    height: 1080

    visible: true
    title: "Chat_bot_twich_ui"

    //Screen definitions
    Component {
        id: loginScreen
        Screen01 {
            id: screen01
            width: mainWindow.width
            height: mainWindow.height

            onButtonClickedSignal: {
                console.log("Botón en Screen01 pulsado desde el QML principal")
                stackView.replace(authScreen);
            }
        }
    }

    Component {
        id: authScreen

        AuthorizationForm
        {
            id: authScreen01
            width: mainWindow.width
            height: mainWindow.height

            //button handlers
            onButtonSendClicked:
            {
                stackView.replace(mainScreen);
            }
        }
    }

    Component {
        id: mainScreen

        MainScreenForm
        {
            id: mainScreen01
            width: mainWindow.width
            height: mainWindow.height

            //button handlers
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginScreen.createObject()
    }


}

