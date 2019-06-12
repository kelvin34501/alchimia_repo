#ifndef PARTINFOMODEL_H
#define PARTINFOMODEL_H

#include <QStandardItemModel>
#include <map>
#include <string>


class PartItem;

class PartInfoModel : public QStandardItemModel
{
public:
    bool isCached() const noexcept { return cached; }
    void setCached(bool c) noexcept { cached = c; }
    void cachePartInfo(const std::map<std::string, std::string> &info);

    const PartItem &partItem() const noexcept { return mPartItem; }

    PartInfoModel(const PartItem &pi) noexcept : mPartItem(pi) {}

private:
    /*!
    \variable PartInfoModel::cached
    \brief True if parameters of a part is stored in this model.
    */
    bool cached = false;

    /*!
    \variable PartInfoModel::partItem
    \brief The PartItem that this model belong to
    */
    const PartItem &mPartItem;
};

#endif // PARTINFOMODEL_H
