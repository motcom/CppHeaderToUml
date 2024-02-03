#ifndef RAWWORDTRANSRATOR_H
#define RAWWORDTRANSRATOR_H
#include <QMap>
#include <QString>
#include <QFileInfo>
#include <Qlist>

class RawWordTransrator
{
public:
    RawWordTransrator();
    void register_file(QFileInfo file_info);
    QMap<QString,QStringList> getFnameToRawStr();
    QStringList getFileNames();
    QStringList getFileNameToHeaderList(QString fileName);
private:
    QMap<QString,QStringList> fnameToRawStrLst;

};

#endif // RAWWORDTRANSRATOR_H
