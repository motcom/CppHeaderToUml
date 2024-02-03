#include "umlclassrelation.h"
#include <QDebug>


UmlClassRelation::UmlClassRelation()
{
    regInclude = QRegularExpression(R"(#include(.*)\.h)");

}

void UmlClassRelation::registerFileStringLst(QString fileName,QStringList strLst)
{
    file_StrLst[fileName] = strLst;
}


void UmlClassRelation::createClsSmallCase() {
    // class name relation

    QRegularExpression regCls("(?=.*(class|struct))");;
    QRegularExpression regNotenum(".*enum.*");
    QRegularExpression delPublicAnddelClass("class|public|struct|{|}");


    auto keys = file_StrLst.keys();

    for (auto &k:keys) {
        // ファイル名出力
        auto smallFileName = k.split(".")[0];

        // ファイル内の文字列検索
        for (auto &val:file_StrLst[k]) {
            // クラス宣言が見つかった
            if(regCls.match(val).hasMatch())
            {
                // enumを排除
                if(regNotenum.match(val).hasMatch()) continue;

                auto strClsNorm = val.replace(delPublicAnddelClass,"").replace(" ","").trimmed();
                auto splitClass = strClsNorm.split(":");

                if(splitClass.count() == 1) {
                    classNameSmallCase_NormalCase[smallFileName]  = strClsNorm; // smallNormalMap
                }else{
                    QString result;
                    QTextStream stream(&result);
                    for (auto &extClsName :splitClass[1].split(",") ) {
                        classNameSmallCase_NormalCase[smallFileName] = splitClass[0]; //smallNormalMap
                        stream << splitClass[0] << "--|>" <<extClsName;
                        className_ExtendLst.push_back(result);
                    }
                }
            }
        }
    }
}

void UmlClassRelation::headerRelation() {
    // header relation
    auto keys =file_StrLst.keys();
    for(auto &k : keys) {
        auto srcHeader = k.split(".")[0];
        QString result;
        QTextStream stream(&result);
        for(auto &val : file_StrLst[k]) {
            // include header match
            if(regInclude.match(val).hasMatch()) {
                auto dstHeader = regInclude.match(val).captured(1).replace("\"","").trimmed();
                auto src = classNameSmallCase_NormalCase[srcHeader];
                auto dst = classNameSmallCase_NormalCase[dstHeader];
                headerRelation_ExtendLst.push_back( src + "-->" + dst);
            }
        }
    }

}

void UmlClassRelation::createData()
{
    createClsSmallCase();
    headerRelation();
    // output;
    for(auto &clsExtend :className_ExtendLst){
        qDebug().noquote() << clsExtend;
    }
    for(auto &headExtend:headerRelation_ExtendLst) {
        qDebug().noquote() << headExtend;
    }


}

