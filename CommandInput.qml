import QtQuick 2.0

Item
{
    signal itemSelected(string text)
    signal searchChanged(string text)
    signal moveUp()
    signal moveDown()
    signal moveLeft()
    signal moveRight()

    BorderImage
    {
        source: "/styles/lineedit.png"
        anchors.fill: parent
        border.left: 10; border.top: 10
        border.right: 10; border.bottom: 10
    }

    TextInput
    {
        id: input
        anchors.centerIn: parent
        focus: true
        font.pixelSize: 24
        font.bold: true
        onTextChanged: searchChanged(input.text)

        Keys.onPressed:
        {
            if (event.key === Qt.Key_Escape)
                close();
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
                itemSelected(input.text);
            if (event.key === Qt.Key_Left)
            {
                event.accepted = true
                moveLeft()
            }
            if (event.key === Qt.Key_Right)
            {
                event.accepted = true
                moveRight()
            }
            if (event.key === Qt.Key_Down)
            {
                event.accepted = true
                moveDown()
            }
            if (event.key === Qt.Key_Up)
            {
                event.accepted = true
                moveUp()
            }
        }
    }

}
