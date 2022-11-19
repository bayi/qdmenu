import QtQuick 2.12

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
    signal toggleNoDisplay()

    property string placeholderText: qsTr("Enter application/command/name")

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
        focus: true
        anchors.fill: parent
        horizontalAlignment: "AlignHCenter"
        color: settings.get("input/textcolor", "#000000")

        font.pixelSize: settings.getNumber("input/fontsize", 16)
        font.bold: settings.getBool("input/fontbold", true)

        onTextEdited: debounce(input.text)
        onAccepted: itemSelected(input.text)
        Keys.onPressed:
        {
            if (event.key === Qt.Key_Escape) Qt.quit();
            if (event.key === Qt.Key_Left) { event.accepted = true; moveLeft(); }
            if (event.key === Qt.Key_Right) { event.accepted = true; moveRight() }
            if (event.key === Qt.Key_Down) { event.accepted = true; moveDown(); }
            if (event.key === Qt.Key_Up) { event.accepted = true; moveUp();}
            if (event.key === Qt.Key_Home) moveHome();
            if (event.key === Qt.Key_End) moveEnd();
            if (event.key === Qt.Key_Control) { toggleNoDisplay(); }
        }

        Text {
            id: placeholder
            color: "grey"
            visible: !input.text /* && !input.activeFocus */
            text: placeholderText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

}
