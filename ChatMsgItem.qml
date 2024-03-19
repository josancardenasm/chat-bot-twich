import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    width: 1000
    height: mainLayout.height
    property string userName: "UserName"
    property string msg: "Text message"

    Rectangle {
        radius: 25
        id: rectangle
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        color: "#1A1A1A"

        Item
        {
            id: colorId
            height: parent.height
            Rectangle
            {
                color: "lightgrey"
                width: 2 * rectangle.radius
                height: parent.height
                radius: rectangle.radius
            }

            Rectangle
            {
                height: parent.height
                width: rectangle.radius
                x: rectangle.radius
                color: rectangle.color
            }
        }

        ColumnLayout
        {
            id:mainLayout
            x: rectangle.radius
            width: parent.width - 2*x
            RowLayout {
                id: headerLayout
                Text {
                    id: textUser
                    text: userName + ":"
                    Layout.topMargin: 10
                    Layout.leftMargin: 10
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    font.styleName: "Semibold"
                    color: "white"
                    Layout.fillWidth: true
                }
                CheckBox {
                    id: checkBox
                    visible: false
                    topPadding: 10
                }
            }

            Text {
                id: textMsg
                text: qsTr(msg)
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                lineHeightMode: Text.ProportionalHeight
                wrapMode: Text.Wrap
                font.styleName: "Light"
                //bottomPadding: 10
                Layout.bottomMargin: 10
                //Layout.topMargin: 10
                Layout.leftMargin: 10
                Layout.fillWidth: true
                fontSizeMode: Text.FixedSize
                color: "white"
            }
        }
    }
}
