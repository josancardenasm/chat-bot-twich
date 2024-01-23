import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: qsTr("Chat Bot Twich")
    color: "indigo"


    BusyIndicator {
        visible: true//!spotifyApi.isAuthenticated
        anchors.centerIn: parent
    }

    TwichAPI {

    }
//     ListView {
//         id: chatList
//         anchors.fill: parent
//         model: chatModel
//         delegate: Item {
//             width: parent.width
//             Text {
//                 text: modelData
//             }
//         }
//     }

//     Row {
//         spacing: 10

//         TextField {
//             id: keywordInput
//             placeholderText: "Palabra clave"
//         }

//         Button {
//             text: "Agregar"
//             onClicked: {
//                 if (keywordInput.text !== "") {
//                     chatbot.addKeyword(keywordInput.text)
//                     keywordInput.text = ""
//                 }
//             }
//         }
//     }

// //    Chatbot {
// //        id: chatbot
// //        onMessageReceived: {
// //            chatModel.append({ "message": message });
// //        }
// //    }

//     ListModel {
//         id: chatModel
//     }
}
