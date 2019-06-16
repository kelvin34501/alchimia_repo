#include "trainconfigurationdialog.h"
#include "ui_trainconfigurationdialog.h"
#include "utils/configurations.h"
#include "modelcontrol/modelcontrol.h"
#include <cmath>
#include <QFileDialog>
#include <QDir>

TrainConfigurationDialog::TrainConfigurationDialog(TrainCFG cfg, QString msg, int page, QWidget *parent, ModelControl *mc) :
    QDialog(parent),
    ui(new Ui::TrainConfigurationDialog)
{
    ui->setupUi(this);
    this->mc = mc;
    train_cfg = cfg;

    connect(ui->LoadModelButton, SIGNAL(clicked()), mc, SLOT(configureModel()));
    connect(ui->LoadDataButton, SIGNAL(clicked()), mc, SLOT(configureData()));
    connect(ui->LogDirBrowseButton, SIGNAL(clicked()), this, SLOT(browseLogDir()));
    connect(ui->SaveDirBrowseButton, SIGNAL(clicked()), this, SLOT(browseSaveDir()));
    connect(ui->BatchSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateBatchSlider(int)));
    connect(ui->SplitSlider, SIGNAL(valueChanged(int)), this, SLOT(updateSplitSlider(int)));
    // connect(ui->SplitLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateSplitText(QString)));

    metrics.insert("acc", ui->acc);
    metrics.insert("ce", ui->ce);
    metrics.insert("mse", ui->mse);
    metrics.insert("mae", ui->mae);
    metrics.insert("msle", ui->msle);
    metrics.insert("mape", ui->mape);
    metrics.insert("cosine", ui->cosine);

    ui->Message->setText(msg);
    ui->TrainTab->setCurrentIndex(page);

    update();
}

TrainConfigurationDialog::~TrainConfigurationDialog()
{
    delete ui;
}


void TrainConfigurationDialog::browseSaveDir(){
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::Directory);
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->SaveDirLineEdit->setText(files.front());
    }
}

void TrainConfigurationDialog::browseLogDir(){
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::Directory);
    if (fileDialog.exec()){
        QStringList files = fileDialog.selectedFiles();
        ui->LogDirLineEdit->setText(files.front());
    }
}

void TrainConfigurationDialog::updateBatchSlider(int){
    int tmp_batch = ui->BatchSizeSlider->value();
    QString tmp_str = QString::number((int)ldexp(1.0, tmp_batch), 10);
    train_cfg.batch_size = tmp_str.toStdString();
    ui->BatchSizeLineEdit->setText(tmp_str);
}

void TrainConfigurationDialog::updateSplitSlider(int){
    int tmp_split = ui->SplitSlider->value();
    QString tmp_str = QString::number((double)tmp_split / ui->SplitSlider->maximum(), 'g', 2);
    train_cfg.validation_split = tmp_str.toStdString();
    ui->SplitLineEdit->setText(tmp_str);
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

    for(int i=0; i<train_cfg.metrics.size(); i++)
    {
        cout << train_cfg.metrics[i] << endl;
        metrics[train_cfg.metrics[i]]->setChecked(true);
//        ui->MetricsButtons->findChild<QCheckBox*>(QString::fromStdString(train_cfg.metrics[i]));//->setChecked(true);
    }

    tmp_batch = atoi(train_cfg.batch_size.data());
    ui->BatchSizeSlider->setValue(log((double)tmp_batch) / log(2.0));
    ui->BatchSizeLineEdit->setText(QString::fromStdString(train_cfg.batch_size));

    tmp_split = atof(train_cfg.validation_split.data());
    ui->SplitSlider->setValue((int)(tmp_split*100));
    ui->SplitLineEdit->setText(QString::fromStdString(train_cfg.validation_split));

    ui->EpochsLineEdit->setText(QString::fromStdString(train_cfg.epochs));

    ui->ShuffleCheckBox->setChecked(train_cfg.shuffle == "True");

    ui->LogDirLineEdit->setText(QString::fromStdString(train_cfg.tb_cfg.log_dir));

    ui->ModelNameLineEdit->setText(QString::fromStdString(train_cfg.model_name));
    ui->SaveDirLineEdit->setText(QString::fromStdString(train_cfg.save_weight_dir));
    ui->ReuseCheckBox->setChecked(train_cfg.reuse_weight);

    ui->ArchiLabel->setText(QString::fromStdString(tmp_m_cfg.archi_path));
    ui->WeightLabel->setText(QString::fromStdString(tmp_m_cfg.weight_path));
    ui->DatasetLabel->setText(QString::fromStdString(tmp_d_cfg.dataset));
}

TrainCFG TrainConfigurationDialog::TrainConfiguration(){
    train_cfg.optimizer = ui->OptimizerComboBox->currentText().toStdString();
    train_cfg.loss = ui->LossComboBox->currentText().toStdString();

//    QList<QCheckBox*> metrics = ui->MetricsButtons->findChildren<QCheckBox*>(QRegExp("*"));
//    QList<QCheckBox*> metrics = ui->MetricsButtons->
//    cout << metrics.size() << endl;
    train_cfg.metrics.clear();
    for (QMap<string, QCheckBox*>::const_iterator i=metrics.constBegin();
         i!=metrics.constEnd(); i++) {
        if(i.value()->isChecked())
        {
            train_cfg.metrics.push_back(i.key());
            cout << i.key() << endl;
        }
    }

    // batch size and validation split already set in slot functions
    train_cfg.epochs = ui->EpochsLineEdit->text().toStdString();
    train_cfg.shuffle = ((ui->ShuffleCheckBox->isChecked())?"True":"False");

    train_cfg.tb_cfg.log_dir = ui->LogDirLineEdit->text().toStdString();

    train_cfg.model_name = ui->ModelNameLineEdit->text().toStdString();
    train_cfg.save_weight_dir = ui->SaveDirLineEdit->text().toStdString();
    train_cfg.reuse_weight = ui->ReuseCheckBox->isChecked();

    return train_cfg;
}





























