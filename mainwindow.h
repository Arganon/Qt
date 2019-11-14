#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "country.h"
#include "daofactory.h"
#include "entitybuilder.h"
#include "mobileoperator.h"
#include "treeviewmodel.h"

#include "dialogopereditor.h"
#include <QMainWindow>
#include <QtGui>
#include <QTreeView>

class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
            Ui::MainWindow *ui;
            QTreeView *m_TreeView;
            TreeModel *m_ItemModel;
            DaoFactory *m_DaoFactory;
            void setUpObjects() noexcept;
            QPushButton* m_AddButton;

            void updateButtonsPosition() noexcept;


    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        virtual void resizeEvent(QResizeEvent *event) override;

    private slots:
        void onButtonClicked();
        void on_treeView_doubleClicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
