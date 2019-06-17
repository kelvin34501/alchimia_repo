#include "configuretestdialog.h"
#include "ui_configuretestdialog.h"
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"
#include <QFileDialog>

ConfigureTestDialog::ConfigureTestDialog(TestCFG test_cfg, QWidget *parent, ModelControl *mc) :
    QDialog(parent),
    ui(new Ui::ConfigureTestDialog)
{
    ui->setupUi(this);
    this->mc = mc;
    this->test_cfg = test_cfg;

    connect(ui->saveDirBrowseButton, SIGNAL(clicked()), this, SLOT(browseSaveDir()));

    update();
}

ConfigureTestDialog::~ConfigureTestDialog()
{
    delete ui;
}

void ConfigureTestDialog::browseSaveDir(){
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::Directory);
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->saveDirLineEdit->setText(files.front());
    }
}

void ConfigureTestDialog::update(){
    ModelCFG tmp_m_cfg = mc->getCurrentModelCFG();
    DataCFG tmp_d_cfg = mc->getCurrentDataCFG();

    ui->fileNameLineEdit->setText(QString::fromStdString(test_cfg.file_name));
    ui->saveDirLineEdit->setText(QString::fromStdString(test_cfg.save_dir));

    ui->archiLabel->setText(QString::fromStdString(tmp_m_cfg.archi_path));
    ui->weightLabel->setText(QString::fromStdString(tmp_m_cfg.weight_path));
    ui->datasetLabel->setText(QString::fromStdString(tmp_d_cfg.dataset));
}

TestCFG ConfigureTestDialog::TestConfiguration()
{
    test_cfg.file_name = ui->fileNameLineEdit->text().toStdString();
    test_cfg.save_dir = ui->saveDirLineEdit->text().toStdString();

    return test_cfg;
}
