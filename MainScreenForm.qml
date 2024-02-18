

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

import com.geeking.qmlcomponents 1.0

Rectangle {
    width: 1920
    height: 1080
    color: "#0F0F0F"

    property color textWhiteColor: "#F0EEF1";

    Connections {
        target: twichircclient
        onConnected: {
            console.debug("Ey! Que estoy conectado!");
            connectionStatus.color = "green"
            //stackView.replace(mainScreen);
        }

        onDisconnected: {
            console.debug("Ey! Que estoy desconectado!");
            connectionStatus.color = "red"
        }
    }

    ChatMsgModel
    {
        id: chatMsgModel
        twichIRCClient: twichircclient
    }

    ColumnLayout
    {
        id: mainLayout
        spacing: 0
        anchors.fill: parent
        RowLayout
        {
            id: buttonsLayout
            spacing: 5
            Layout.leftMargin: 10
            Layout.bottomMargin: 5
            Layout.topMargin: 5

            Rectangle {
                id: connectionStatus
                width: 20
                height: width
                radius: width
                color: "red"
            }

            TextField {
                id: userField
                width: 350
                height: 40
                placeholderText: qsTr("User")
            }

            TextField {
                id: chatRoom
                width: 350
                height: 40
                placeholderText: qsTr("Chatroom")
            }

            Button {
                id: connectButton
                height: 40
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

        }

        RowLayout
        {
            id: screensLayout
            spacing: 5
            Layout.leftMargin: 10
            Layout.bottomMargin: 5
            Layout.topMargin: 5
            Layout.rightMargin: 10

            Rectangle {
                visible: false
                id: filterList
                Layout.preferredWidth: 400
                Layout.fillHeight: true
                color: "black"

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

            Rectangle {
                id: rectangle1
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "black"

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
                    width: parent.width
                    height: parent.height - chatListToolBar.height

                    ListView {
                        id: chatList
                        width: parent.width
                        height: parent.height
                        spacing: 20
                        // model: chatMsgModel
                        clip: true
                        model: ListModel {
                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José"
                            }

                            ListElement {
                                userName: "Grey"
                                msg: "Hola hola que pasa don pepito, hola que pasa don José\n Hola Hols que pasa"
                            }
                        }


                        delegate: Item {
                            id: delegate
                            required property var model
                            width: chatList.width
                            height: row2.height

                            Rectangle {
                                radius: 10
                                opacity: 0.5
                                color: "grey"
                                anchors.fill: parent
                            }

                            RowLayout {
                                id: row2
                                spacing: 10
                                Layout.topMargin: 5
                                Layout.bottomMargin: 5
                                Layout.fillWidth: true

                                // Layout.rightMargin: 10

                                CheckBox {
                                    Layout.leftMargin: 10
                                    id: chatCheckBox
                                }

                                Text {
                                    id: chat_msg_text
                                    Layout.rightMargin: 10

                                    width: delegate.width - 50
                                    wrapMode: Text.Wrap
                                    text: delegate.model.userName + ": " + delegate.model.msg
                                    font.pointSize: 15
                                    color: textWhiteColor
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
