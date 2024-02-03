#include "rawwordtransrator.h"
#include <QDebug>
#include <QIODevice>
#include <QTextStream>
#include <QRegExp>
#include <stdexcept>


RawWordTransrator::RawWordTransrator() {}

// QMap<QString,QStringList> fname_to_strlst;
void RawWordTransrator::register_file(QFileInfo file_info)
{
    auto file = QFile(file_info.absoluteFilePath());

    //　ファイルが開けない場合
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << QString("file not open");
    }

    QTextStream tx(&file);
    QStringList strLst;
    QString line;
    QRegExp re_comment("//.*");
    QRegExp re_ifndefj("#ifndef.*");
    QRegExp re_define("#define.*");
    QRegExp re_extinclude("#include.*<.*>");
    QRegExp re_endif("#endif.*");
    QRegExp re_comment_rep("//.*$");
    QRegExp re_space_corone_space("\\s*:\\s*");

    QStringList rawStrings;
    while(!tx.atEnd()) {
        line = tx.readLine();
        line = line.trimmed();

        // 文字列が空ならばパス
        if(""==line) continue;
        if("Q_OBJECT"==line) continue;

        // 正規表現でパス
        if(re_comment.exactMatch(line))    continue;
        if(re_ifndefj.exactMatch(line))    continue;
        if(re_define.exactMatch(line))     continue;
        if(re_extinclude.exactMatch(line)) continue;
        if(re_endif.exactMatch(line))      continue;
        line = line.replace(re_comment_rep,"");
        line = line.replace(re_space_corone_space,":");

        // Listにpush
        rawStrings.push_back(line);
    }
    // データ構造構築
    fnameToRawStrLst[file_info.fileName()] = rawStrings;
}

QMap<QString, QStringList> RawWordTransrator::getFnameToRawStr()
{
    return fnameToRawStrLst;
}

QStringList RawWordTransrator::getFileNames()
{
    QStringList lstStr = fnameToRawStrLst.keys();
    return lstStr;
}

QStringList RawWordTransrator::getFileNameToHeaderList(QString fileName)
{
    //　キーがない場合例がを出すよ
    if (!fnameToRawStrLst.contains(fileName)) {
        throw std::runtime_error("RawWordTransrator::get_file_name_to_header_raws(QString file_name)でfname_to_strlstに含まれないキー（ファイル名）が使われました);");
    }
    return fnameToRawStrLst[fileName];
}
