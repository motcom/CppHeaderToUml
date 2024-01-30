#include "argholder.h"
#include <QDir>

ArgHolder::ArgHolder(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
}


bool ArgHolder::check()
{
    if (this->argc != 1) return false;
    QString tmp_path = QString(this->argv[1]);
    if (!QDir(tmp_path).exists()) return false;
    return true;
}

QString ArgHolder::get_dir_path()
{
    return argv[1];
}
