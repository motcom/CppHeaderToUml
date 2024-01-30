#include "filelistmanager.h"
#include <QDir>
#include <iostream>
FileListManager::FileListManager(QString dir_path) {
    auto dir = QDir(dir_path);
    if(!dir.exists()){
        std::cerr << "そんなディレクトリはありません" <<std::endl;
        return;
    }

    for(auto &file_info :dir.entryInfoList()) {
        if (file_info.suffix() == "h") {
            file_lst.append(file_info);
        }
    }

}

QList<QFileInfo> FileListManager::get_file_list()
{
    return file_lst;
}
