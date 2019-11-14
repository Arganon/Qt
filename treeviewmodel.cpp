#include "treeviewmodel.h"
#include <QDebug>
#include <QAbstractItemDelegate>

TreeItem::TreeItem (const UObjects &data, const bool isCountry, TreeItem *parent)
    : m_Data(data)
    , m_IsCountry(isCountry)
    , m_ParentItem(parent) {}

TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item) {
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row) {
    if (row < m_childItems.size()) {
        return m_childItems.value(row);
    }
    return nullptr;
}

int TreeItem::childCount() const {
    return m_childItems.count();
}

int TreeItem::columnCount() const {
    return 1;
}

QVariant TreeItem::data() const {
    QVariant result;
    if (m_IsCountry) {
        result = m_Data.m_Country.getName();
    }
    else {
        result = m_Data.m_MobOper.getName() + " ("
               + QString::number(m_Data.m_MobOper.getMcc()) + ", "
               + QString::number(m_Data.m_MobOper.getMnc()) + ')';
    }
    return result;
}

TreeItem *TreeItem::parentItem() {
    return m_ParentItem;
}

int TreeItem::childNumber() const {
    if (m_ParentItem) {
     return m_ParentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}

const UObjects TreeItem::getObject() const noexcept {
    return m_Data;
}

bool TreeItem::updateMobOperName(const QString &name) noexcept {
    if (isCountry()) {
        return false;
    }

    m_Data.m_MobOper.setName(name);
    return true;
}

void TreeItem::setIcon(const QIcon icon) noexcept {
    m_Data.m_Icon = icon;
}

bool TreeItem::isCountry() const noexcept {
    return m_IsCountry;
}

TreeItem* TreeItem::findCountry(const int mcc) const noexcept {
    for (auto item : m_childItems) {
        if (item->m_Data.m_Country.getMcc() == mcc) {
            return item;
        }
    }
    return nullptr;
}

bool TreeItem::insertMobOperator(const MobileOperator &mobOper) noexcept {
    auto country = findCountry(mobOper.getMcc());
    if (nullptr == country) {
        return false;
    }

    for (auto treeItem : country->m_childItems) {
        if (mobOper == treeItem->m_Data.m_MobOper) {
            return false;
        }
    }

    UObjects obj;
    obj.m_MobOper = mobOper;
    country->appendChild(new TreeItem(obj, false, country));

    return true;
}

bool TreeItem::removeMobOperator(const MobileOperator &mobOper) noexcept {
    auto country = findCountry(mobOper.getMcc());
    if (nullptr != country) {

        for (int i = 0; i < country->m_childItems.size(); ++i) {
            if (mobOper == country->m_childItems[i]->m_Data.m_MobOper) {
                country->m_childItems.removeAt(i);
                return true;
            }
        }
    }
    return false;
}

int TreeItem::getCountryRowPosition(const int mcc) noexcept {
    for (int i = 0; i < m_childItems.size(); ++i) {
        if (m_childItems[i]->m_Data.m_Country.getMcc() == mcc) {
            return i;
        }
    }
    return -1;
}






TreeModel::TreeModel(const QVector<Country> &countries, QVector<MobileOperator> &mobOperators, QObject *parent) {
    UObjects rootElement{ Country(0,"Countries and mobile operators", "0")};
    m_RootItem = new TreeItem(rootElement, true);
    setupModelData(countries, mobOperators, m_RootItem);
}

TreeModel::~TreeModel() { delete m_RootItem; }

int TreeModel::columnCount(const QModelIndex &) const {
    return m_RootItem->columnCount();
}

// Changed return item->data(index.column())  to return item->data()
QVariant TreeModel::data (const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    TreeItem *item = getItem(index);
    if (role == Qt::DecorationRole) {
        return item->getObject().m_Icon;
    }
    if (role != Qt::DisplayRole  && role != Qt::EditRole)
    {
        return QVariant();
    }
    return item->data();
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) {
            return item;
        }
    }
    return m_RootItem;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return nullptr;
    }
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}


QVariant TreeModel::headerData(int, Qt::Orientation orientation, int role) const {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
         return m_RootItem->data();
     }
     return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
     if (parent.isValid() && parent.column() != 0) {
         return QModelIndex();
     }
     TreeItem *parentItem = getItem(parent);
     TreeItem *childItem = parentItem->child(row);
     if (childItem) {
         return createIndex(row, column, childItem);
     }
     else {
         return QModelIndex();
     }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }
    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parentItem();
    if (parentItem == m_RootItem) {
        return QModelIndex();
    }
    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

void TreeModel::setupModelData(const QVector<Country> &countries, const QVector<MobileOperator> &mobOperator, TreeItem *parent) {
    QList<TreeItem*> parents;
    parents << parent;

    for (auto country : countries) {
        QIcon flag(":/flags/Countries/" + country.getCode() + ".png"); // TODO  should use Decorator
        TreeItem *countryItem = new TreeItem(UObjects{country}, true, parents.last());
        countryItem->setIcon(flag); // TODO  should use Decorator

        for (auto mobOper : mobOperator) {
            if (country.getMcc() == mobOper.getMcc()) {
                UObjects mobObj;
                mobObj.m_MobOper = mobOper;
                TreeItem *item = new TreeItem(mobObj, false, countryItem);
                countryItem->appendChild(item);
            }
        }

        parents.last()->appendChild(countryItem);
    }
}

TreeItem* TreeModel::getMobOper(const QModelIndex &index) {
    return getItem(index);
}

bool TreeModel::updateMobOperator(const QModelIndex &index, QString &name) {
    return getItem(index)->updateMobOperName(name);
}

const TreeItem* TreeModel::findCountry(const int mcc) const noexcept {
    return m_RootItem->findCountry(mcc);
}

bool TreeModel::insertMobOperator(const MobileOperator &mobOperator) noexcept {
    int countryRow = m_RootItem->getCountryRowPosition(mobOperator.getMcc());
    TreeItem *country = m_RootItem->findCountry(mobOperator.getMcc());
    QModelIndex index = createIndex(countryRow, 0, country);
    beginInsertRows(index, country->childCount()-1, country->childCount()-1);
    bool result = m_RootItem->insertMobOperator(mobOperator);
    endInsertRows();
    return result;
}

bool TreeModel::removeMobOperator(const QModelIndex& index, const MobileOperator &mobOperator) noexcept {
    beginRemoveRows(index, index.row(), index.row());
    bool result = m_RootItem->removeMobOperator(mobOperator);
    endRemoveRows();
    return result;
}
