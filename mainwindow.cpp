#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeviewmodel.h"
#include "qsqldbcountrydao.h"
#include "qsqldbmobileoperatordao.h"
#include "databaseupdater.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUpObjects();
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setModel(m_ItemModel);
    m_AddButton = new QPushButton("Add Element", ui->treeView);
    connect(m_AddButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    updateButtonsPosition();
    resizeEvent(nullptr);
    ui->treeView->update();
}

MainWindow::~MainWindow()
{
    delete m_ItemModel;
    delete ui;
    delete m_AddButton;
}

void MainWindow::setUpObjects() noexcept {
    m_DaoFactory = DaoFactory::getInstance();
    auto countryDao = m_DaoFactory->createCountryDao();
    auto vecOfCountries = countryDao->findAll();

    auto mobOperatorsDao = m_DaoFactory->createMobileOperatorDao();
    auto vecOfMobOperators = mobOperatorsDao->findAll();

    m_ItemModel = new TreeModel(vecOfCountries, vecOfMobOperators);

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    DataBaseUpdater *dbUpdater = new DataBaseUpdater(&index);
    DialogOperEditor *window = new DialogOperEditor(m_ItemModel, dbUpdater);
    window->update();
    delete window;
    delete dbUpdater;
}

void MainWindow::onButtonClicked() {
    DataBaseUpdater *dbUpdater = new DataBaseUpdater();
    DialogOperEditor *window = new DialogOperEditor(m_ItemModel, dbUpdater);
    window->create();
    ui->treeView->setModel(m_ItemModel);

    delete window;
    delete dbUpdater;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    updateButtonsPosition();
}

void MainWindow::updateButtonsPosition() noexcept{
    QRect geometry = ui->treeView->geometry();
    m_AddButton->setGeometry({geometry.width() - m_AddButton->geometry().width(),
                                      geometry.height() - m_AddButton->geometry().height(),
                                      m_AddButton->geometry().width(),
                                      m_AddButton->geometry().height()});
}
