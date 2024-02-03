#ifndef UMLCLASSRELATION_H
#define UMLCLASSRELATION_H
#include <QStringList>
#include <QString>
#include <QMap>
#include <QRegularExpression>

class UmlClassRelation
{
public:

    UmlClassRelation(UmlClassRelation &&) = delete;
    UmlClassRelation(const UmlClassRelation &) = delete;

    UmlClassRelation();
    void registerFileStringLst(QString fileName,QStringList strLst);
    void createData();

private:
    // file名とfileの内容の文字列
    QMap<QString,QStringList> file_StrLst;

    // 各種マップ
    QMap<QString,QString> classNameSmallCase_NormalCase; // 小文字のクラスの名前と大文字のクラスの名前を結ぶ
    QStringList className_ExtendLst;      // クラス継承文字列
    QStringList headerRelation_ExtendLst; // ヘッダ関係リスト

    // 正規表現---------------------------------------

    QRegularExpression regInclude;

    // ---------------------------------------------
    void createClsSmallCase();
    void headerRelation();
};

#endif // UMLCLASSRELATION_H
