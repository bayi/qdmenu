import QtQuick 2.12
import QtQuick.Controls 2.12

Item
{
    signal itemSelected(variant app)

    function current() { return apps.get(list.model.index(list.currentIndex, 0)); }
    function up() { list.moveCurrentIndexUp() }
    function down() { list.moveCurrentIndexDown() }
    function left() { list.moveCurrentIndexLeft() }
    function right() { list.moveCurrentIndexRight() }
    function home() { list.currentIndex = 0 }
    function end() { list.currentIndex = list.count - 1 }
    function filter(text) { apps.setFilterName(text) }
    function toggleNoDisplay() { apps.toggleFilterShowNoDisplay() }

    property int itemWidth: list.cellWidth - (list.padding / 2)
    property int itemHeight: list.cellHeight - (list.padding / 2)

    Component
    {
        id: highlight
        Rectangle
        {
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

        remove: Transition {
            ParallelAnimation {
                NumberAnimation { properties: "scale"; from: 1; to: 0; duration: 250; easing.type: Easing.InOutQuad }
            }
        }

        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 250 }
        }

        populate: Transition {
            NumberAnimation { properties: "scale"; from: 0; to: 1; duration: 250; easing.type: Easing.InOutQuad }
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
                    hoverEnabled: true
                    // onEntered: list.currentIndex = index
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
                    text: model.display
                    color: settings.get("icons/textcolor", "#ffffff")
                    width: parent.width
                    wrapMode:  Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.Fit
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: settings.get("icons/bottommargin", 8)
                }
            }
        }
    }
}
