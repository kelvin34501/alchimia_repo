#include "partinfomodel.h"


/*!
\fn void PartInfoModel::cachePartInfo(const std::map<std::string, std::string> &info)
\brief Store a copy of a Part's parameters in the QStandardItemModel.
*/
void PartInfoModel::storePartInfo(const std::map<std::string, std::string> &info)
{
    setColumnCount(2);
    QStandardItem *parentItem = invisibleRootItem();
    for (auto i = info.begin(); i != info.end(); ++i)
        parentItem->appendRow({new QStandardItem(i->first.c_str()),
                               new QStandardItem(i->second.c_str())});
    setHorizontalHeaderLabels({"Parameter", "Value"});
}
