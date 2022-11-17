import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Qt.labs.folderlistmodel 1.0
import QtLocation 5.3
import Process 1.0

Window
{
    id: root
    width: Screen.width - 1 // Multimonitor fix
    height: Screen.height - 1 // Multimonitor fix
    color: settings.get("background/bgcolor", "#000000")
    title: qsTr("qdmenu")
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    Process { id: process }

    ColumnLayout
    {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        spacing: 1

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
            Layout.fillHeight: true
            onItemSelected: process.start(app.exec, app.terminal)
        }

    }
}
