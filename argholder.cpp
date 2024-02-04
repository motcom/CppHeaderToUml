#include "argholder.h"
#include <QDir>

ArgHolder::ArgHolder(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
}


bool ArgHolder::check()
{
    if (this->argc != 2) return false;
    resultPath = QString(this->argv[1]);

    // currentパスを渡す
    if (resultPath == "."){
        resultPath = QDir::currentPath();
    }
    if (!QDir(resultPath).exists()) return false;
    return true;
}

QString ArgHolder::get_dir_path()
{
    return resultPath;
}
