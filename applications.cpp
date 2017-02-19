#include "applications.h"
#include <QDir>
#include <QtConcurrent/QtConcurrent>

const int Applications::NameRole = Qt::UserRole + 1;
const int Applications::IconRole = Qt::UserRole + 2;
const int Applications::ExecRole = Qt::UserRole + 3;
const int Applications::TerminalRole = Qt::UserRole + 4;

Applications::Applications(QObject *parent) :
    QAbstractListModel(parent)
{
    parserRunning = true;
    QFuture<void> future = QtConcurrent::run(this, &Applications::parseApplications);
}

Applications::~Applications()
{
    qDeleteAll(this->m_internalData);
    this->m_internalData.clear();
    this->m_data.clear();
}

void Applications::parseApplications()
{
    this->m_files.append(this->readFolder(QDir::homePath() + APPLICATIONS_LOCAL_PATH));
    this->m_files.append(this->readFolder(APPLICATIONS_PATH));

    foreach(QString file, this->m_files)
    {
        DesktopFile* app = new DesktopFile(file);
        if (!app->noDisplay())
        {
            m_internalData.append(app);
            this->add(app);
        }
    }
    this->m_files.clear();
    this->sort();

    emit ready();
    parserRunning = false;
}

QStringList Applications::readFolder(QString folder)
{
    QDir dir(folder);
    QFileInfoList file_list = dir.entryInfoList(
                QStringList(APPLICATIONS_FILES), QDir::Files | QDir::Readable);

    QStringList files;
    foreach(QFileInfo file, file_list)
    {
        if (this->m_files.filter(file.fileName()).count() == 0)
        {
            files.append(file.absoluteFilePath());
        }
    }
    return files;
}

void Applications::add(DesktopFile *item)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(item);
    endInsertRows();
    emit countChanged(m_data.size());
}

void Applications::sort()
{
    std::sort(this->m_data.begin(), this->m_data.end(),
              [](const DesktopFile* left, const DesktopFile* right) -> bool
    {
        return QString::compare(left->name(),right->name(), Qt::CaseInsensitive) < 0;
    });
}

DesktopFile* Applications::get(int index) const
{
    return m_data.at(index);
}

void Applications::filter(QString search)
{
    if (parserRunning) return;
    beginRemoveRows(QModelIndex(), 0, m_data.size());
    m_data.clear();
    endRemoveRows();
    foreach(DesktopFile* file, m_internalData)
    {
        if(file->name().contains(search,Qt::CaseInsensitive)
                || file->comment().contains(search, Qt::CaseInsensitive))
        {
            this->add(file);
        }
    }
    this->sort();
}

int Applications::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

QVariant Applications::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > (m_data.size()-1) )
        return QVariant();

    DesktopFile* obj = m_data.at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
        case NameRole:
            return QVariant::fromValue(obj->name());
        break;

        case IconRole:
            return QVariant::fromValue(obj->icon());

        case ExecRole:
            return QVariant::fromValue(obj->exec());

        case TerminalRole:
            return QVariant::fromValue(obj->terminal());

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> Applications::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(IconRole, QByteArray("icon"));
    roles.insert(ExecRole, QByteArray("exec"));
    roles.insert(TerminalRole, QByteArray("terminal"));
    return roles;
}
