import QtQuick 2.10
import QtQuick.Controls 2.0
import Applications 1.0

Item
{
    signal itemSelected(variant app)

    function current() { return list.currentItem != null ? list.currentItem.item : null}
    function up() { list.moveCurrentIndexUp() }
    function down() { list.moveCurrentIndexDown() }
    function left() { list.moveCurrentIndexLeft() }
    function right() { list.moveCurrentIndexRight() }
    function home() { list.currentIndex = 0 }
    function end() { list.currentIndex = list.count - 1 }
    function filter(text) { apps.filter(text) }

    Applications { id: apps }

    Component
    {
        id: highlight
        Rectangle
        {
            width: list.cellWidth;
            height: list.cellHeight
            color: settings.get("icons/selectcolor", "#2d75af")
            radius: 8
            x: list.currentItem ? list.currentItem.x : 0
            y: list.currentItem ? list.currentItem.y : 0
            Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
            Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
        }
    }

    GridView
    {
        id: list

        property int widthDivider: (parent.width < parent.height) ? settings.getNumber("icons/cols", 8) : settings.getNumber("icons/rows", 8)
        property int heightDivider: (parent.width < parent.height) ? settings.getNumber("icons/rows", 8) : settings.getNumber("icons/cols", 8)
        property int padding: settings.getNumber("icons/padding", 32)

        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        anchors.margins: padding
        model: apps
        highlight: highlight
        highlightFollowsCurrentItem: true
        clip: true
        cacheBuffer: 12

        cellHeight: Math.floor(parent.height / heightDivider)
        cellWidth: Math.floor(parent.width / widthDivider)

        // add: Transition { NumberAnimation { properties: "x,y" } }
        // move: Transition { NumberAnimation { properties: "x,y" } }

        delegate: Column
        {
            property variant item: model
            id: listItem
            // scale: 0
            // opacity: 0
            GridView.onAdd: SequentialAnimation {

                PauseAnimation {
                    duration: Math.random() * 50
                }

                NumberAnimation {
                    target: listItem
                    property: "scale"
                    properties: "scale, opacity"
                    to: 1
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }

            Item {
                width: list.cellWidth
                height: list.cellHeight
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: list.currentIndex = index
                    onClicked:
                    {
                        list.currentIndex = index
                        itemSelected(list.currentItem.item)
                    }
                }

                Image
                {
                    id: icon
                    height: settings.getNumber("icons/width", 64)
                    width: settings.getNumber("icons/height", 64)
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.verticalCenter
                    source: model.icon
                }

                Label
                {
                    id: label
                    text: model.name
                    color: settings.get("icons/textcolor", "#ffffff")
                    width: parent.width
                    wrapMode:  Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.Fit
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.verticalCenter
                }
            }


        }
    }

}
