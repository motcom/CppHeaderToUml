
#ifdef APP_MODE
#include "argholder.h"
#include "filelistmanager.h"
#include <iostream>
#include <QString>
#include <QFileInfo>
#include <QList>
#include "rawwordtransrator.h"
#include "umlclassrelation.h"
#include "umlclassextract.h"


int main(int argc, char *argv[])
{
    auto arg_holder = ArgHolder(argc,argv);

    if (!arg_holder.check()){
        std::cerr << u8"CPPのヘッダが含まれるディレクトリパスを入力するとPlantUml形式で出力\n"
                     "使い方: CppHeaderToUML dir_path";
    }

    auto flst_man = FileListManager(arg_holder.get_dir_path());
    QList<QFileInfo> file_lst = flst_man.get_file_list();

    // for(QFileInfo &f_info:file_lst){
        // std::cout << f_info.absoluteFilePath().toStdString().c_str() << std::endl;
    // }

    RawWordTransrator rawWordTran;
    for(auto fileInfo:file_lst ) {
        rawWordTran.register_file(fileInfo);
    }

    auto keys = rawWordTran.getFileNames();
    UmlClassRelation umlClsRelation;
    for(auto &k:keys) {
        umlClsRelation.registerFileStringLst(
            k,rawWordTran.getFileNameToHeaderList(k)
            );
    }
    umlClsRelation.createData();

    auto fname_to_raw = rawWordTran.getFnameToRawStr();
    for(auto fileName : fname_to_raw.keys())
    {
        UmlClassExtract umlClsExt(fname_to_raw[fileName]);
    }
}
#endif
