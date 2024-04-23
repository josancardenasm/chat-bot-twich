import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    id: chatMsgItem
    width: 1000
    height: mainLayout.height
    property string userName: "UserName"
    property string msg: "Text message"
    property int itemIndex: -1

    signal removeButtonClicked(int idx)

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
                Rectangle
                {
                    id: deleteButton
                    color: rectangle.color
                    Layout.topMargin: 5
                    height: 16
                    width: 16
                    Image {
                        id: deleteButtonImg
                        source: "resources/icon_trash.svg"
                        anchors.fill: parent

                        MouseArea{
                            id: removeButtonMA
                            anchors.fill: parent
                            onPressed:
                            {
                                deleteButton.color = "grey"
                            }
                            onReleased:
                            {
                                deleteButton.color = rectangle
                            }
                            onClicked:
                            {
                                chatMsgItem.removeButtonClicked(itemIndex);
                            }
                        }
                    }
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
