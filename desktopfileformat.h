#ifndef DESKTOPFILEFORMAT_H
#define DESKTOPFILEFORMAT_H

#include <QSettings>

#define DESKTOP_GROUP_ENTRY_NAME            "Desktop Entry"
#define DESKTOP_KEY_NAME                    "Name"
#define DESKTOP_KEY_GENERIC_NAME            "GenericName"
#define DESKTOP_KEY_VERSION                 "Version"
#define DESKTOP_KEY_TERMINAL                "Terminal"
#define DESKTOP_KEY_CATEGORIES              "Categories"
#define DESKTOP_KEY_TYPE                    "Type"
#define DESKTOP_KEY_PATH                    "Path"
#define DESKTOP_KEY_ICON                    "Icon"
#define DESKTOP_KEY_EXEC                    "Exec"
#define DESKTOP_KEY_TRY_EXEC                "TryExec"
#define DESKTOP_KEY_COMMENT                 "Comment"
#define DESKTOP_KEY_KEYWORDS                "Keywords"
#define DESKTOP_KEY_NO_DISPLAY              "NoDisplay"
#define DESKTOP_KEY_NOT_SHOW_IN             "NotShowIn"
#define DESKTOP_KEY_ONLY_SHOWN_IN           "OnlyShowIn"
#define DESKTOP_KEY_HIDDEN                  "Hidden"

bool desktopFileRead(QIODevice &device, QSettings::SettingsMap &map);
bool desktopFileWrite(QIODevice &device, const QSettings::SettingsMap &map);

#endif // DESKTOPFILEFORMAT_H
