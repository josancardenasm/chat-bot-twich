

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
//import Chat_bot_twich_ui

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    color: "#0F0F0F"

    Button {
        id: connectButton
        width: 230
        height: 92
        text: qsTr("Conectar")
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 30
        flat: false
        highlighted: false
        checkable: true
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            // Emitir una señal cuando se hace clic en el botón
            buttonClickedSignal()
        }
    }

    Text {
        id: label
        color: "#ffffff"
        text: qsTr("Chat Bot Twich")
        anchors.top: connectButton.bottom
        //font.family: Constants.font.family
        anchors.topMargin: -207
        font.bold: true
        font.pointSize: 50
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }

    signal buttonClickedSignal()

}
