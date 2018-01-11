import QtQuick 2.5
import Applications 1.0

Item
{
    signal itemSelected(variant app)

    function current() { return list.currentItem != null ? list.currentItem.item : null}
    function up() { list.moveCurrentIndexUp() }
    function down() { list.moveCurrentIndexDown() }
    function left() { list.moveCurrentIndexLeft() }
    function right() { list.moveCurrentIndexRight() }
    function filter(text) { apps.filter(text) }

    Applications { id: apps }

    Component
    {
        id: highlight
        Rectangle
        {
            width: list.cellWidth; height: list.cellHeight
            color: "#2d75af"; radius: 5
            x: list.currentItem.x
            y: list.currentItem.y
            Behavior on x { SpringAnimation { spring: 4; damping: 0.25 } }
            Behavior on y { SpringAnimation { spring: 4; damping: 0.25 } }
        }
    }

    GridView
    {
        id: list
        anchors.fill: parent
        anchors.margins: 32
        model: apps
        highlight: highlight
        highlightFollowsCurrentItem: true
        clip:true
        cacheBuffer: 12

        add: Transition { NumberAnimation { properties: "x,y" } }
        move: Transition { NumberAnimation { properties: "x,y" } }

        delegate: Column
        {
            property variant item: model

            id: listItem
            width: 80
            height: 96

            Image
            {
                height: 64
                width: 64
                anchors.horizontalCenter: parent.horizontalCenter
                source: model.icon

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
            }

            Text
            {
                text: model.name
                color: "#ffffff"
                width: 80
                height: 32
                wrapMode: Text.Wrap
                clip: true
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

}
