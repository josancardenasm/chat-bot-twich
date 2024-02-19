import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    width: 1000
    height: column.height
    property string userName: "UserName"
    property string msg: "Text message"
    property string bgColor: "#1F1F1F"

    Rectangle {
        radius: 20
        id: rectangle
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        color: bgColor

        RowLayout {
            id: rowLayout
            anchors.fill: parent

            CheckBox {
                id: checkBox
            }

            ColumnLayout {
                id: column

                Text {
                    id: textUser
                    textFormat: Text.RichText
                    text: userName + ":"
                    Layout.topMargin: 10
                    Layout.leftMargin: 10
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignVCenter
                    color: "black"
                    Rectangle
                    {
                        anchors.fill: parent
                        anchors.rightMargin: -10
                        anchors.leftMargin: -10
                        z: -1
                        color: "lightgrey"

                    }
                }

                Text {
                    id: textMsg
                    text: qsTr(msg)
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignVCenter
                    lineHeightMode: Text.ProportionalHeight
                    wrapMode: Text.Wrap
                    bottomPadding: 10
                    Layout.bottomMargin: 10
                    Layout.topMargin: 10
                    Layout.fillWidth: true
                    fontSizeMode: Text.FixedSize
                    font.bold: false
                    color: "lightgrey"
                }
            }

        }
    }
}
