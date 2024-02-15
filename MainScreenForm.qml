

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

import com.geeking.qmlcomponents 1.0

Rectangle {
    width: 1920
    height: 1080
    color: "#392e5c"

    Connections {
        target: twichircclient
        onConnected: {
            console.debug("Ey! Que estoy conectado!");
            connectStatus.color = "green"
            //stackView.replace(mainScreen);
        }

        onDisconnected: {
            console.debug("Ey! Que estoy desconectado!");
            connectStatus.color = "red"
        }
    }

    TextField {
        id: keyWordTextField
        x: 100
        y: 50
        placeholderText: qsTr("Palabra clave")
    }

    Button {
        id: addButton
        x: keyWordTextField.x + keyWordTextField.width + 50
        y: keyWordTextField.y
        text: qsTr("Agregar...")
    }

    Rectangle {
        id: filterList
        x: keyWordTextField.x
        y: keyWordTextField.y + keyWordTextField.height + 50
        width: 400
        height: parent.height - y - 100
        color: "#ffffff"

        ToolBar {
            id: filtersToolBar
            x: 0
            y: parent.height - height
            width: parent.width
            height: 50
            Row {
                id: rowFilterToolbar
                anchors.fill: parent
                CheckBox {
                    id: filtersToolbarCheckBox
                    text: qsTr("Seleccionar todo")
                }

                Button {
                    id: buttonFilterErase
                    text: qsTr("Borrar")
                    highlighted: true
                    flat: false
                }

                Button {
                    id: buttonFilter
                    text: qsTr("Filtrar")
                    highlighted: true
                    flat: false
                }
            }
        }

        ListView {
            id: listView
            x: 0
            y: 0
            width: parent.width
            height: parent.height - filtersToolBar.height

            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    CheckBox {
                        id: filtersCheckBox
                    }
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                }
            }
        }
    }

    ChatMsgModel
    {
        id: chatMsgModel
        twichIRCClient: twichircclient
    }

    Rectangle {
        id: rectangle1
        x: filterList.x + filterList.width + 50
        y: filterList.y
        width: parent.width - x - 100
        height: filterList.height
        color: "#ffffff"

        ToolBar {
            id: chatListToolBar
            x: 0
            y: parent.height - height
            width: parent.width
            height: 50
            Row {
                id: rowChatToolbar
                anchors.fill: parent

                CheckBox {
                    id: chatToolbarCheckBox
                    text: qsTr("Seleccionar todo")
                }

                Button {
                    id: buttonChatErase
                    text: qsTr("Borrar")
                    highlighted: true
                    flat: false
                }
            }
        }

        ScrollView {
            width: parent.width - 10
            height: parent.height - chatListToolBar.height - 10

            ListView {
                id: chatList
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - chatListToolBar.height - 10
                spacing: 5
                model: chatMsgModel

                delegate: Item {
                    id: delegate
                    required property var model
                    x: 0
                    y: 0
                    width: parent.width
                    height: chat_msg_text.height

                    Rectangle {
                        x: 0
                        y: 0
                        opacity: 0.5
                        color: "grey"
                        anchors.fill: parent
                    }

                    Row {
                        id: row2
                        spacing: 10

                        CheckBox {
                            id: chatCheckBox
                        }

                        Text {
                            id: chat_msg_text
                            width: delegate.width - 50
                            wrapMode: Text.Wrap
                            text: delegate.model.userName + ": " + delegate.model.msg
                            anchors.verticalCenter: parent.verticalCenter
                            font.bold: true
                            font.pointSize: 18
                        }
                    }


                }
            }
        }
    }


    TextField {
        id: userField
        x: 550
        y: addButton.y
        width: 250
        height: addButton.height
        placeholderText: qsTr("User")
    }

    TextField {
        id: chatRoom
        x: 893
        y: addButton.y
        width: 350
        height: addButton.height
        placeholderText: qsTr("Chatroom")
    }

    Button {
        id: connectButton
        x: 1278
        y: addButton.y
        height: addButton.height
        text: qsTr("Conectar")

        property bool isConnected: false
        onClicked:
        {
            if(!isConnected)
            {
                twichircclient.connect(twichapi.getOauthToken(), userField.text, chatRoom.text);
                connectButton.text = "Desconectar";
                isConnected = true;
            }
            else
            {
                twichircclient.disconnect(twichapi.getOauthToken(), userField.text, chatRoom.text)
                connectButton.text = "Conectar";
                isConnected = false;
            }
        }
    }

    Rectangle {
        id: connectStatus
        x: 1433
        y: addButton.y
        width: addButton.height
        height: width
        color: "red"
    }
}
