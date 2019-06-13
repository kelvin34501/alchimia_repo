#include "trainconfigurationdialog.h"
#include "ui_trainconfigurationdialog.h"
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"
#include <cmath>

TrainConfigurationDialog::TrainConfigurationDialog(TrainCFG cfg, QWidget *parent, ModelControl *mc) :
    QDialog(parent),
    ui(new Ui::TrainConfigurationDialog)
{
    ui->setupUi(this);
    this->mc = mc;
    train_cfg = cfg;
    update();

    connect(ui->LoadModelButton, SIGNAL(clicked()), mc, SLOT(configureModel()));
    connect(ui->LoadDataButton, SIGNAL(clicked()), mc, SLOT(configureData()));

    connect(ui->SaveDirBrowseButton, SIGNAL(clicked()), this, SLOT(browseSaveDir()));
    connect(ui->BatchSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateBatchSlider(int)));
    connect(ui->SplitSlider, SIGNAL(valueChanged(int)), this, SLOT(updateSplitSlider(int)));
    connect(ui->SplitLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateSplitText(QString)));
}

TrainConfigurationDialog::~TrainConfigurationDialog()
{
    delete ui;
}


void TrainConfigurationDialog::browseSaveDir(){

}

void TrainConfigurationDialog::updateBatchSlider(int){

}

void TrainConfigurationDialog::updateSplitSlider(int){

}

void TrainConfigurationDialog::updateSplitText(QString){

}

void TrainConfigurationDialog::update(){
    int opt_id = 0;
    int loss_id = 0;
    int tmp_batch;
    double tmp_split;
    ModelCFG tmp_m_cfg = mc->getCurrentModelCFG();
    DataCFG tmp_d_cfg = mc->getCurrentDataCFG();

    opt_id = ui->OptimizerComboBox->findText(QString::fromStdString(train_cfg.optimizer));
    ui->OptimizerComboBox->setCurrentIndex(((opt_id >= 0)?opt_id:0));

    loss_id = ui->LossComboBox->findText(QString::fromStdString(train_cfg.loss));
    ui->LossComboBox->setCurrentIndex(((loss_id >= 0)?loss_id:0));

    // TODO: update metrics

    tmp_batch = atoi(train_cfg.batch_size.data());
    ui->BatchSizeSlider->setValue(log((double)tmp_batch) / log(2.0));
    ui->BatchSizeLineEdit->setText(QString::fromStdString(train_cfg.batch_size));

    tmp_split = atof(train_cfg.validation_split.data());
    ui->SplitSlider->setValue((int)(tmp_split*100));
    ui->SplitLineEdit->setText(QString::fromStdString(train_cfg.validation_split));

    ui->EpochsLineEdit->setText(QString::fromStdString(train_cfg.epochs));

    ui->ShuffleCheckBox->setChecked(train_cfg.shuffle == "True");

    ui->ModelNameLineEdit->setText(QString::fromStdString(train_cfg.model_name));
    ui->SaveDirLineEdit->setText(QString::fromStdString(train_cfg.save_weight_dir));
    ui->ReuseCheckBox->setChecked(train_cfg.reuse_weight);

    ui->ArchiLabel->setText(QString::fromStdString(tmp_m_cfg.archi_path));
    ui->WeightLabel->setText(QString::fromStdString(tmp_m_cfg.weight_path));
    ui->DatasetLabel->setText(QString::fromStdString(tmp_d_cfg.dataset));
}
