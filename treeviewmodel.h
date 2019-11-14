#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QVector>
#include <QList>
#include <QVariant>
#include <country.h>
#include <mobileoperator.h>
#include <QStandardItem>

struct UObjects {

    Country m_Country;
    MobileOperator m_MobOper;
    QIcon m_Icon;
};

class TreeItem {
    private:

        UObjects m_Data;
        bool m_IsCountry;
        TreeItem *m_ParentItem;
        QList <TreeItem*> m_childItems;
        QVector <QVariant> m_ItemData;

    public:
        TreeItem (const UObjects &data, const bool isCountry, TreeItem *parentItem = nullptr);
        ~TreeItem();

        void appendChild(TreeItem *child); //Добавить узел-потомок
        TreeItem *child(int row); //Вернуть дочерний элемент
        int childCount() const; //Количество дочерних элементов
        int columnCount() const; //Вернуть количество столбцов элемента
        QVariant data () const;
        int childNumber() const;
        const UObjects getObject() const noexcept;
        bool updateMobOperName(const QString &name) noexcept;
//        const QModelIndex& getCountryIndex

        TreeItem *parentItem(); //Вернуть родительский элемент
        void setIcon(const QIcon icon) noexcept;
        bool isCountry() const noexcept;
        TreeItem* findCountry(const int mcc) const noexcept;
        bool insertMobOperator(const MobileOperator &mobOper) noexcept;
        bool removeMobOperator(const MobileOperator &mobOper) noexcept;
        int getCountryRowPosition(const int mcc) noexcept;
};


class TreeModel : public QAbstractItemModel {
 Q_OBJECT

    private:
        void setupModelData(const QVector<Country> &countries, const QVector<MobileOperator> &mobOperator, TreeItem *parent);
        TreeItem *getItem(const QModelIndex &index) const;
        TreeItem *m_RootItem;

    public:
        TreeModel(const QVector<Country> &countries, QVector<MobileOperator> &mobOperator, QObject *parent = nullptr);
        ~TreeModel() override;

        QVariant data(const QModelIndex &index, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        TreeItem* getMobOper(const QModelIndex &index);
        bool updateMobOperator(const QModelIndex &index, QString &name);
        const TreeItem* findCountry(const int mcc) const noexcept;
        bool insertMobOperator(const MobileOperator &mobOperator) noexcept;
        bool removeMobOperator(const QModelIndex& index, const MobileOperator &mobOperator) noexcept;
};

#endif // TREEVIEWMODEL_H
