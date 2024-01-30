#ifndef RAWWORDTRANSRATOR_H
#define RAWWORDTRANSRATOR_H
#include <QMap>
#include <QString>
#include <QStringList>
#include <QFileInfo>

class RawWordTransrator
{
public:
    RawWordTransrator();
    void register_file(QFileInfo file_info);
    QMap<QString,QStringList> get_fname_to_strlst();
    QStringList get_file_names();
    QStringList get_file_name_to_header_raws(QString file_name);
private:
    QMap<QString,QStringList> fname_to_strlst;

};

#endif // RAWWORDTRANSRATOR_H
