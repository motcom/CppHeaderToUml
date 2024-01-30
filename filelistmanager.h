#ifndef FILELISTMANAGER_H
#define FILELISTMANAGER_H
#include <QString>
#include <QList>
#include <QFileInfo>

class FileListManager
{
public:
    FileListManager(const FileListManager &)=delete;
    FileListManager(FileListManager &&)=delete;
    FileListManager(QString dir_path);

    QList<QFileInfo> get_file_list();
private:
    QList<QFileInfo> file_lst;
};

#endif // FILELISTMANAGER_H
