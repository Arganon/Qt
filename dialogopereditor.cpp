#include "dialogopereditor.h"
#include "ui_dialogopereditor.h"
#include "treeviewmodel.h"
#include "databaseupdater.h"
#include "country.h"
#include "mobileoperator.h"
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>

DialogOperEditor::DialogOperEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOperEditor)
{
    ui->setupUi(this);
}

DialogOperEditor::DialogOperEditor(TreeModel *treeModel, DataBaseUpdater *dbUpdater, QWidget *parent) :
    QDialog(parent),
    m_TreeModel(treeModel),
    m_DbUpdater(dbUpdater),
    ui(new Ui::DialogOperEditor)
{
    ui->setupUi(this);
}

DialogOperEditor::~DialogOperEditor()
{
    delete ui;
}

bool DialogOperEditor::setName(const QString &name) {
    m_NameMobOper = name;
    ui->lineEditName->setText(name);
}

bool DialogOperEditor::setMCC(const int &mcc) {
    m_Mcc = mcc;
    ui->lineEditMCC->setText(QString::number(mcc));
}

bool DialogOperEditor::setMNC(const int &mnc) {
    m_Mnc = mnc;
    ui->lineEditMNC->setText(QString::number(mnc));
}

bool DialogOperEditor::update() {
    TreeItem *item = m_TreeModel->getMobOper(m_DbUpdater->getModelIndex());
    if (!item->isCountry()) {
        paintCountryFlag(item->parentItem());
        setName(item->getObject().m_MobOper.getName());
        setMCC(item->getObject().m_MobOper.getMcc());
        setMNC(item->getObject().m_MobOper.getMnc());
        freezeMccMnc();
        exec();
    }
}

bool DialogOperEditor::create() {
    m_IsCreateMode = true;
    ui->lineEditMCC->setValidator(new QIntValidator(0, 1000, this));
    ui->lineEditMNC->setValidator(new QIntValidator(0, 1000, this));
    unfreezeMccMnc();
    exec();
}

void DialogOperEditor::freezeMccMnc() {
    ui->lineEditMCC->setReadOnly(true);
    ui->lineEditMNC->setReadOnly(true);
}

void DialogOperEditor::unfreezeMccMnc() {
    ui->lineEditMCC->setReadOnly(false);
    ui->lineEditMNC->setReadOnly(false);
}

bool DialogOperEditor::createObject() {
    m_NameMobOper = ui->lineEditName->text();
    m_Mcc = ui->lineEditMCC->text().toInt();
    m_Mnc = ui->lineEditMNC->text().toInt();

    MobileOperator mobOperator(m_Mcc, m_Mnc, m_NameMobOper);
    bool result = false;
    if (true == (result = m_TreeModel->insertMobOperator(mobOperator))) {
        if (false == (result = m_DbUpdater->insertMobOperatorToDB(mobOperator))) {
            m_TreeModel->removeMobOperator(m_DbUpdater->getModelIndex(), mobOperator);
        }
    }
    return result;
}

void DialogOperEditor::updateObject() {
    QString newName = ui->lineEditName->text();
    if (m_NameMobOper != newName) {
        MobileOperator tempMobOper = m_TreeModel->getMobOper(m_DbUpdater->getModelIndex())->getObject().m_MobOper;
        if (true == m_TreeModel->updateMobOperator(m_DbUpdater->getModelIndex(), newName)) {
            tempMobOper.setName(newName);
            if (false == m_DbUpdater->updateMobOperatorInDB(tempMobOper)) {
                m_TreeModel->updateMobOperator(m_DbUpdater->getModelIndex(), m_NameMobOper);
            }
        }
    }
}

void DialogOperEditor::on_lineEditMCC_editingFinished()
{
    if (!isCountryExist()) {
        QMessageBox::critical(this, "Something going wrong...", "Please, write correct MCC. Database doesn't include country with empty/invalid MCC.");
    }
}

bool DialogOperEditor::isCountryExist() {
    const TreeItem* item = m_TreeModel->findCountry(ui->lineEditMCC->text().toInt());

    if (nullptr != item) {
        paintCountryFlag(item);
        return true;
    }

    ui->FlagLogo->clear();
    ui->lineEditMCC->clear();

    return false;
}

void DialogOperEditor::paintCountryFlag(const TreeItem *item) noexcept {
    if (item->isCountry()) {
        QIcon icon = item->getObject().m_Icon;
        ui->FlagLogo->setPixmap(icon.pixmap(icon.availableSizes().first()));
    }
}

void DialogOperEditor::on_pushButton_2_clicked()
{
    if (m_IsCreateMode) {
        if (isCountryExist()) {
            if (createObject()) {
                close();
            }
            else {
                QMessageBox::critical(this, "Something going wrong...", "Please, write correct MCC. Database doesn't include country with empty/invalid MCC.");
            }
        }
        else {
            QMessageBox::critical(this, "Something going wrong...", "Please, write correct MCC. Database doesn't include country with empty/invalid MCC.");
        }
    }
    else {
        updateObject();
        close();
    }
}

void DialogOperEditor::on_pushButton_3_clicked()
{
    if (!m_IsCreateMode) {
        MobileOperator tempMobOper = m_TreeModel->getMobOper(m_DbUpdater->getModelIndex())->getObject().m_MobOper;
        m_TreeModel->removeMobOperator(m_DbUpdater->getModelIndex(), tempMobOper);
        m_DbUpdater->removeMobOperatorFromDB(tempMobOper);
        close();
    }
}
