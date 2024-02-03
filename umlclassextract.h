#ifndef UMLCLASSEXTRACT_H
#define UMLCLASSEXTRACT_H
#include <QStringList>

class UmlClassExtract
{
public:
    UmlClassExtract(UmlClassExtract &&) = delete;
    UmlClassExtract(const UmlClassExtract &) = delete;

    /**
     *　文字列リストを読み込む
     */
    UmlClassExtract(QStringList);
private:
    enum class Mode{
        None,Public,Private,Protected
    };

    Mode current_mode = Mode::None;

};

#endif // UMLCLASSEXTRACT_H
