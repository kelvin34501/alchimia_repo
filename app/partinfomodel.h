#ifndef PARTINFOMODEL_H
#define PARTINFOMODEL_H

#include <QStandardItemModel>
#include <map>
#include <string>


class PartInfoModel : public QStandardItemModel
{
public:
    void storePartInfo(const std::map<std::string, std::string> &info);
};

#endif // PARTINFOMODEL_H
