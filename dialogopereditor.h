#ifndef DIALOGOPEREDITOR_H
#define DIALOGOPEREDITOR_H

#include <QDialog>

class DataBaseUpdater;
class TreeModel;
class TreeItem;
class QModelIndex;

namespace Ui {
class DialogOperEditor;
}

class DialogOperEditor : public QDialog
{
    Q_OBJECT

    private:
        TreeModel *m_TreeModel;
        DataBaseUpdater *m_DbUpdater;
        QModelIndex *m_Index;
        Ui::DialogOperEditor *ui;
        bool m_IsCreateMode{false};
        QString m_NameMobOper;
        int m_Mcc;
        int m_Mnc;

        bool createObject();
        void updateObject();
        void freezeMccMnc();
        void unfreezeMccMnc();
        bool isCountryExist();
        void paintCountryFlag(const TreeItem *item) noexcept;

    public:
        DialogOperEditor(QWidget *parent = nullptr);
        DialogOperEditor(TreeModel *treeModel, DataBaseUpdater *dbUpdater, QWidget *parent = nullptr);
        ~DialogOperEditor();

        bool setName(const QString &name);
        bool setMCC(const int &mcc);
        bool setMNC(const int &mnc);
        bool update();
        bool create();

    private slots:
        void on_lineEditMCC_editingFinished();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
};

#endif // DIALOGOPEREDITOR_H
