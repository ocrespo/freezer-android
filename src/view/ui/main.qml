import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    width: 540
    height: 960
    visible: true
    //visibility: Window.FullScreen
    Action {
           id: navigateBackAction
           icon.name: stackView.depth > 1 ? "back" : "drawer"
           onTriggered: {
               if (stackView.depth > 1) {
                   stackView.pop()
                   listView.currentIndex = -1
               } else {
                   drawer.open()
               }
           }
       }
    header: ToolBar {
            Material.foreground: "white"

            RowLayout {
                spacing: 20
                anchors.fill: parent

                ToolButton {
                    action: navigateBackAction
                }

                Label {
                    id: titleLabel
                    text: listView.currentItem ? listView.currentItem.text : "Gallery"
                    font.pixelSize: 20
                    elide: Label.ElideRight
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }

                ToolButton {
                    action: optionsMenuAction

                    Menu {
                        id: optionsMenu
                        x: parent.width - width
                        transformOrigin: Menu.TopRight

                        Action {
                            text: "Settings"
                            onTriggered: settingsDialog.open()
                        }
                        Action {
                            text: "Help"
                            onTriggered: help()
                        }
                        Action {
                            text: "About"
                            onTriggered: aboutDialog.open()
                        }
                    }
                }
            }
        }
    Drawer {
            id: drawer
            width: Math.min(window.width, window.height) / 3 * 2
            height: window.height
            interactive: stackView.depth === 1

            ListView {
                id: listView
                focus: true
                currentIndex: -1
                anchors.fill: parent

                delegate: ItemDelegate {
                    width: listView.width
                    text: model.title
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        listView.currentIndex = index
                        stackView.push(model.source)
                        drawer.close()
                    }
                }

              
                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: FreezerPage {}
    }

}
