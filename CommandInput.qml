import QtQuick 2.0

Item
{
    signal itemSelected(string text)
    signal searchChanged(string text)
    signal moveUp()
    signal moveDown()
    signal moveLeft()
    signal moveRight()
    signal moveHome()
    signal moveEnd()


    Timer
    {
        property var payload: []
        id: timer
        interval: 200
        onTriggered: { doSearch(payload.text); }
    }

    function debounce(text) {
        timer.payload = { text: text};
        if (timer.running) return;
        timer.start();
    }

    function doSearch(text) {
        searchChanged(text);
    }

    Rectangle
    {
        color: settings.get("input/bgcolor", "#ffffff")
        antialiasing: true
        radius: settings.getNumber("input/borderradius", 8)
        anchors.fill: parent
        border.color: settings.get("input/bordercolor", "#6795cc")
        border.width: settings.getNumber("input/borderwidth", 2)
    }

    TextInput
    {
        id: input
        color: settings.get("input/textcolor", "#000000")
        anchors.centerIn: parent
        focus: true
        font.pixelSize: settings.getNumber("input/fontsize", 24)
        font.bold: settings.getBool("input/fontbold", true)
        onTextChanged: debounce(input.text)

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
            if (event.key === Qt.Key_Home)
            {
                moveHome()
            }
            if (event.key === Qt.Key_End)
            {
                moveEnd()
            }
        }
    }

}
