

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 1920
    height: 1080
    color: "#392e5c"

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

        ListView {
            id: chatList
            x: 0
            y: 0
            width: parent.width
            height: parent.height - chatListToolBar.height
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
                    id: row2
                    spacing: 10

                    CheckBox {
                        id: chatCheckBox
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
}
