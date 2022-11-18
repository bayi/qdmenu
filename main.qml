import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import Process 1.0

Window
{
    id: root
    width: Screen.width - 1 // Multimonitor fix
    height: Screen.height - 1 // Multimonitor fix
    color: settings.get("background/bgcolor", "#000000")
    title: qsTr("QDMenu")
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.WindowStaysOnTopHint
    opacity: 0

    onActiveChanged: {
        if (!active) {
            // console.log('Lost focus, exiting.')
            // Qt.quit()
        }
    }

    Process { id: process }

    NumberAnimation on opacity {
        from: 0
        to: 1
        duration: 500
        running: true
    }

    ColumnLayout
    {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        spacing: 8
        anchors.margins: 16

        CommandInput
        {
            Layout.topMargin: settings.get("background/topmargin", 16)
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: parent.width / 4
            Layout.preferredHeight: settings.getNumber("input/height", 32)
            onItemSelected:
            {
                if (applist.current() === null)
                    process.start(text, true)
                else
                    process.start(applist.current().exec, applist.current().terminal)
            }
            onMoveUp: applist.up()
            onMoveDown: applist.down()
            onMoveLeft: applist.left()
            onMoveRight: applist.right()
            onMoveHome: applist.home()
            onMoveEnd: applist.end()
            onSearchChanged: applist.filter(text)
        }

        AppList
        {
            id: applist
            Layout.preferredWidth: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            onItemSelected: process.start(app.exec, app.terminal)
        }

    }
}
