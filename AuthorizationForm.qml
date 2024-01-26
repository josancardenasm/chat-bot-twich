

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import ChatBotTwich.Twich 1.0

Rectangle {
    id: mainView
    width: 1920
    height: 1080
    color: "#392e5c"

    TwichAPI
    {
        id: twichApi
    }

    Rectangle {
        id: authUrl
        x: 250
        y: 250
        width: mainView.width - 300 - x - 50
        height: 40
        color: "#ffffff"

        TextField {
            id: text1
            width: parent.width
            height: parent.height
            text: twichApi.generateAuthURL()
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
        }
    }

    Button {
        id: sendButton
        x: mainView.width - 300
        y: authToken.y
        text: qsTr("Enviar")

        onClicked: {
            busyIndicator.running = true
            twichApi.connect()
        }
    }

    Rectangle {
        id: authToken
        x: authUrl.x
        y: authUrl.y + 300
        width: sendButton.x - x - 50
        height: 40
        color: "#ffffff"

        TextField {
            id: textInput
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            text: qsTr("Auth Token")
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
        }
    }

    Text {
        id: text2
        x: 732
        y: 169
        text: qsTr("Copia este enlace en tu navegador")
        font.pixelSize: 30
        color: "white"
    }

    Text {
        id: text3
        x: 724
        y: 478
        color: "white"
        text: qsTr("Introduce aqui to token de atorización")
        font.pixelSize: 30
    }

    BusyIndicator {
        id: busyIndicator
        x: 939
        y: 728
        visible: true
        running: false
    }

}
