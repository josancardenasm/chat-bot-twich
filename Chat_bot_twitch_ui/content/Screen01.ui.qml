

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import Chat_bot_twitch_ui

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#1a1a1a"

    Image {
        id: image
        x: 777
        y: 180
        width: 346
        height: 346
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectFit
    }

    TextField {
        id: textField
        x: 850
        y: 675
        placeholderText: qsTr("Username")
    }

    RoundButton {
        id: roundButton
        x: 860
        y: 774
        width: 180
        height: 40
        text: "Connect"
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
