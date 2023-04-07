import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: root

    /*header: ToolBar {
        Label {
            text: qsTr("Freezer")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }*/

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: filterFreezerModel
        delegate: ItemDelegate {
            text: model.name
            width: listView.width - listView.leftMargin - listView.rightMargin
            onClicked: root.StackView.view.push("qrc:/ui/ItemPage.qml", { inConversationWith: modelData })

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
