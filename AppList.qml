import QtQuick 2.10
import QtQuick.Controls 2.0
// import Applications 1.0

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
    function filter(text) { apps.setFilterName(text) }

    property int itemWidth: list.cellWidth - (list.padding / 2)
    property int itemHeight: list.cellHeight - (list.padding / 2)

    Component
    {
        id: highlight
        Rectangle
        {
            color: settings.get("icons/selectcolor", "#2d75af")
            radius: 8
            width: itemWidth
            height: itemHeight
            x: list.currentItem ? list.currentItem.x : 0
            y: list.currentItem ? list.currentItem.y : 0
            Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
            Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
        }
    }

    GridView
    {
        id: list

        property int widthDivider: (parent.width < parent.height) ? settings.getNumber("icons/rows", 8) : settings.getNumber("icons/cols", 8)
        property int heightDivider: (parent.width < parent.height) ? settings.getNumber("icons/cols", 8) : settings.getNumber("icons/rows", 8)
        property int padding: settings.getNumber("icons/padding", 32)

        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        model: apps
        highlight: highlight
        highlightFollowsCurrentItem: true
        clip: true
        cacheBuffer: 64

        cellHeight: Math.floor(parent.height / heightDivider)
        cellWidth: Math.floor(parent.width / widthDivider)

        add: Transition {
            ParallelAnimation {
                NumberAnimation { properties: "scale, opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuad }
                NumberAnimation { properties: "x,y"; from: 0; duration: 200 }
            }
        }

        addDisplaced: Transition {
            ParallelAnimation {
                NumberAnimation { properties: "scale, opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuad }
                NumberAnimation { properties: "x,y"; from: 0; duration: 200 }
            }
        }

        remove: Transition {
            ParallelAnimation {
                NumberAnimation { properties: "scale, opacity"; to: 0; duration: 200; easing.type: Easing.InOutQuad }
                NumberAnimation { properties: "x,y"; to: 0; duration: 200 }
            }
        }

        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200 }
        }

        populate: Transition {
            NumberAnimation { properties: "scale, opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuad }
        }

        delegate: Column
        {
            property variant item: model
            id: listItem
            Item {
                width: itemWidth
                height: itemHeight
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        if (list.currentIndex === index && list.currentItem.item)
                            itemSelected(list.currentItem.item)
                        list.currentIndex = index
                    }
                }

                Image
                {
                    id: icon
                    source: model.icon
                    cache: true
                    height: settings.getNumber("icons/width", 64)
                    width: settings.getNumber("icons/height", 64)
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: settings.get("icons/topmargin", 8)
                }

                Label
                {
                    id: label
                    text: model.name_localized
                    color: settings.get("icons/textcolor", "#ffffff")
                    width: parent.width
                    wrapMode:  Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.Fit
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: icon.bottom
                    anchors.topMargin: settings.get("icons/texttopmargin", 8)
                }
            }
        }
    }
}
