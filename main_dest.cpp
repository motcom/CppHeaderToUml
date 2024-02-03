
#ifdef TEST_MODE
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QIODevice>
#include <QString>
#include "rawwordtransrator.h"
#include "umlclassrelation.h"
//#include "umlclassextract.h"
int main()
{

    auto path_a = QString("C:/Users/user/Documents/QtProject/viewer/mainwidget.h");
    auto path_b = QString("C:/Users/user/Documents/QtProject/viewer/loadimageagent.h");
    auto path_c = QString("C:/Users/user/Documents/QtProject/viewer/imagerender.h");
    auto path_d = QString("C:/Users/user/Documents/QtProject/viewer/imagedatainfo.h");
    auto path_f = QString("C:/Users/user/Documents/QtProject/viewer/imagelistmanager.h");
    QFileInfo file_info_a(path_a);
    QFileInfo file_info_b(path_b);
    QFileInfo file_info_c(path_c);
    QFileInfo file_info_d(path_d);
    QFileInfo file_info_f(path_f);

    RawWordTransrator raw_word_trans;
    raw_word_trans.register_file(file_info_a);
    raw_word_trans.register_file(file_info_b);
    raw_word_trans.register_file(file_info_c);
    raw_word_trans.register_file(file_info_d);
    raw_word_trans.register_file(file_info_f);


    auto keys = raw_word_trans.getFileNames();
    UmlClassRelation umlClsRelation;
    for(auto &k:keys) {
        umlClsRelation.registerFileStringLst(
            k,raw_word_trans.getFileNameToHeaderList(k)
            );
    }

    umlClsRelation.createData();


}
#endif
