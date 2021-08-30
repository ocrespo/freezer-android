import QtQuick 2.15
import QtQuick.Controls 2.5

ApplicationWindow {
    width: 540
    height: 960
    visible: true
    //visibility: Window.FullScreen

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: FreezerPage {}
    }
}
