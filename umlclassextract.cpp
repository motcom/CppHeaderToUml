#include "umlclassextract.h"
#include <QDebug>
#include <QRegExp>
#include <iostream>

UmlClassExtract::UmlClassExtract(QStringList strLst)
{
    int flag_inner_braket = false;
    int braket_count = 0;
    QRegExp reg_public("^public:$|^signals:$");
    QRegExp reg_private("^private:$|^private.*slots:$");
    QRegExp reg_protected("^protected:$");
    QRegExp reg_include("#include.*$");
    QRegExp reg_braket_left(".*\\{.*");
    QRegExp reg_braket_right(".*\\}.*");
    QRegExp reg_delete_semicoron(";$");
    QRegExp reg_class_coron_delete(":.*$");
    QRegExp reg_commnet(R"(//.*$)");
    QRegExp reg_comment_start(R"(/\*.*)");
    QRegExp reg_comment_end(R"(\*/.*)");


    bool comment_flag = false;

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

        // include skip
        if(reg_include.exactMatch(tmp_str)) continue;
        // 1行コメントの後ろを削除
        tmp_str = tmp_str.replace(reg_commnet,"");
        // コメントスタート
        if(reg_comment_start.exactMatch(tmp_str)) comment_flag = true;
        if(reg_comment_end.exactMatch(tmp_str)) {
            comment_flag = false;
            continue;
        }
        if (comment_flag) {
            continue;
        }



        // 内部ブラケットの内容を消す start -------------------------------------------
        if((braket_count >1) && reg_braket_left.exactMatch(tmp_str)){
            tmp_str = tmp_str.replace("{","");
            flag_inner_braket = true;
        }
        if((braket_count >1) && reg_braket_right.exactMatch(tmp_str)) {
            tmp_str = tmp_str.replace("}","");
            flag_inner_braket = false;
        }
        if(flag_inner_braket) continue;
        // 内部ブラケットの内容を消す end   -------------------------------------------

        if(braket_count == 0) current_mode = Mode::None;

        // コロン削除
        tmp_str = tmp_str.replace(reg_class_coron_delete,"");

        tmp_str = tmp_str.replace("struct ","class ");
        // アクセスラベル付加と出力
        if(current_mode==Mode::Public){
            std::cout <<"+ " <<tmp_str.toStdString() << std::endl;
        }else if(current_mode==Mode::Private){
            std::cout <<"- " <<tmp_str.toStdString() << std::endl;
        }else if(current_mode==Mode::Protected){
            std::cout <<"# " <<tmp_str.toStdString() << std::endl;
        }else{
            std::cout << tmp_str.toStdString() << std::endl;
        }

    }
}




