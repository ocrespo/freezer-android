import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    //visibility: Window.FullScreen
    title: qsTr("Hello World")

    ListView {
        id: listView
        width: parent.width
        height: parent.height

        Component {
            id: freezerItem
            Item {
                width: listView.width; height: 40
                Column{
                    Text{ text: itemName }
                }
            }
        }

        delegate: freezerItem

        model: ListModel {
            ListElement {
                itemName: "Grey"
            }

            ListElement {
                itemName: "Red"
            }

            ListElement {
                itemName: "Blue"
            }

            ListElement {
                itemName: "Green"
            }
        }

    }
}
