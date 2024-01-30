

#ifdef TEST_MODE
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QIODevice>
#include "rawwordtransrator.h"
int main()
{

    auto path_a = QString("C:/Users/user/Documents/QtProject/viewer/mainwidget.h");
    auto path_b = QString("C:/Users/user/Documents/QtProject/viewer/loadimageagent.h");
    QFileInfo file_info_a(path_a);
    QFileInfo file_info_b(path_b);

    RawWordTransrator raw_word_trans;
    raw_word_trans.register_file(file_info_a);
    raw_word_trans.register_file(file_info_b);

    auto keys = raw_word_trans.get_file_names();
    for(auto &k : keys) {
        qDebug() << k;
        for(auto &v :raw_word_trans.get_file_name_to_header_raws(k)){
            qDebug() << "\t" << v;
        }
    }
}
#endif
