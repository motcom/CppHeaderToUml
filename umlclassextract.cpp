#include "umlclassextract.h"
#include <QDebug>
#include <QRegExp>

UmlClassExtract::UmlClassExtract(QStringList strLst)
{
    int braket_count = 0;
    QRegExp reg_public("^public:$|^signals:$");
    QRegExp reg_private("^private:$|^private.*slots:$");
    QRegExp reg_protected("^protected:$");
    QRegExp reg_include("#include.*$");
    QRegExp reg_braket_left(".*\\{.*");
    QRegExp reg_braket_right(".*\\}.*");
    QRegExp reg_delete_semicoron(";$");
    QRegExp reg_class_coron_delete(":.*$");

    for(auto itr = strLst.begin();itr != strLst.end();itr++) {
        // セミコロン消去
        QString tmp_str = itr->replace(reg_delete_semicoron,"");

        // ブラケットカウンタ
        if(reg_braket_left.exactMatch(tmp_str)) {
            braket_count++;
        }
        if(reg_braket_right.exactMatch(tmp_str)) {
            braket_count--;
        }

        // モードセレクタ
        if(reg_public.exactMatch(tmp_str)) {
            current_mode = Mode::Public;
            continue;
        }
        if(reg_private.exactMatch(tmp_str)) {
            current_mode = Mode::Private;
            continue;
        }
        if(reg_protected.exactMatch(tmp_str)) {
            current_mode = Mode::Protected;
            continue;
        }

        if(reg_include.exactMatch(tmp_str)) continue;
        if(braket_count == 0) current_mode = Mode::None;

        // コロン削除
        tmp_str = tmp_str.replace(reg_class_coron_delete,"");

        tmp_str = tmp_str.replace("struct ","class ");
        // アクセスラベル付加と出力
        if(current_mode==Mode::Public){
            qDebug().noquote() <<"+ " <<tmp_str;
        }else if(current_mode==Mode::Private){
            qDebug().noquote() <<"- " <<tmp_str;
        }else if(current_mode==Mode::Protected){
            qDebug().noquote() <<"# " <<tmp_str;
        }else{
            qDebug().noquote() << tmp_str;
        }

    }
}




