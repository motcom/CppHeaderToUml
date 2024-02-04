#ifndef ARGHOLDER_H
#define ARGHOLDER_H
#include <QString>

class ArgHolder
{
public:
    ArgHolder(const ArgHolder &) = delete;
    ArgHolder(ArgHolder &&) = delete;

    ArgHolder(int argc,char**argv);

    /**
     * @brief 与えられた引数が正しいかどうかチェックする
     * @return bool
     */
    bool check();

    /**
     * @brief ディレクトリパスの安全な取得
     * @return QString ディレクトリのパス
     */
    QString get_dir_path();

private:
    QString resultPath;

    int argc;
    char** argv;
};

#endif // ARGHOLDER_H


