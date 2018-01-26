#include "grayscalemordialog.h"
#include "ui_grayscalemordialog.h"
#include "mainwindow.h"
#include "cvAlgorithms.h"
#include <QMessageBox>
#include <QFileDialog>

GrayScaleMorDialog::GrayScaleMorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrayScaleMorDialog)
{
    ui->setupUi(this);

    tmp = ((MainWindow *)parent)->getImage();

    sizeGroup = new QButtonGroup();
    sizeGroup->addButton(ui->size2Button);
    sizeGroup->addButton(ui->size3Button);
    sizeGroup->addButton(ui->size4Button);

    typeGroup = new QButtonGroup();
    typeGroup->addButton(ui->dilationButton);
    typeGroup->addButton(ui->erosionButton);
    typeGroup->addButton(ui->openButton);
    typeGroup->addButton(ui->closeButton);
    typeGroup->addButton(ui->reconstructButton);
    typeGroup->addButton(ui->watershedButton);

    ui->ele11->setValidator(new QIntValidator(0,1));
    ui->ele12->setValidator(new QIntValidator(0,1));
    ui->ele21->setValidator(new QIntValidator(0,1));
    ui->ele22->setValidator(new QIntValidator(0,1));
    ui->ele13->setValidator(new QIntValidator(0,1));
    ui->ele14->setValidator(new QIntValidator(0,1));
    ui->ele23->setValidator(new QIntValidator(0,1));
    ui->ele24->setValidator(new QIntValidator(0,1));
    ui->ele31->setValidator(new QIntValidator(0,1));
    ui->ele32->setValidator(new QIntValidator(0,1));
    ui->ele33->setValidator(new QIntValidator(0,1));
    ui->ele34->setValidator(new QIntValidator(0,1));
    ui->ele41->setValidator(new QIntValidator(0,1));
    ui->ele42->setValidator(new QIntValidator(0,1));
    ui->ele43->setValidator(new QIntValidator(0,1));
    ui->ele44->setValidator(new QIntValidator(0,1));

    connect(sizeGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeSize()));
    connect(typeGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeType()));

    connect(ui->conformButton, &QPushButton::clicked, this, &GrayScaleMorDialog::conform);
    connect(ui->cancelButton, &QPushButton::clicked, this, &GrayScaleMorDialog::cancel);

    ui->size2Button->setChecked(true);

    changeSize();
}

GrayScaleMorDialog::~GrayScaleMorDialog()
{
    delete ui;
}

void GrayScaleMorDialog::changeSize()
{
    if (ui->size2Button->isChecked()) {
        ui->ele11->setVisible(true);
        ui->ele12->setVisible(true);
        ui->ele21->setVisible(true);
        ui->ele22->setVisible(true);
        ui->ele13->setVisible(false);
        ui->ele14->setVisible(false);
        ui->ele23->setVisible(false);
        ui->ele24->setVisible(false);
        ui->ele31->setVisible(false);
        ui->ele32->setVisible(false);
        ui->ele33->setVisible(false);
        ui->ele34->setVisible(false);
        ui->ele41->setVisible(false);
        ui->ele42->setVisible(false);
        ui->ele43->setVisible(false);
        ui->ele44->setVisible(false);

        ui->ele11->setText(QString::number(1));
        ui->ele12->setText(QString::number(1));
        ui->ele21->setText(QString::number(1));
        ui->ele22->setText(QString::number(1));
    }
    else if (ui->size3Button->isChecked()) {
        ui->ele11->setVisible(true);
        ui->ele12->setVisible(true);
        ui->ele21->setVisible(true);
        ui->ele22->setVisible(true);
        ui->ele13->setVisible(true);
        ui->ele14->setVisible(false);
        ui->ele23->setVisible(true);
        ui->ele24->setVisible(false);
        ui->ele31->setVisible(true);
        ui->ele32->setVisible(true);
        ui->ele33->setVisible(true);
        ui->ele34->setVisible(false);
        ui->ele41->setVisible(false);
        ui->ele42->setVisible(false);
        ui->ele43->setVisible(false);
        ui->ele44->setVisible(false);

        ui->ele11->setText(QString::number(1));
        ui->ele12->setText(QString::number(1));
        ui->ele21->setText(QString::number(1));
        ui->ele22->setText(QString::number(1));
        ui->ele13->setText(QString::number(1));
        ui->ele23->setText(QString::number(1));
        ui->ele31->setText(QString::number(1));
        ui->ele32->setText(QString::number(1));
        ui->ele33->setText(QString::number(1));
    }
    else if (ui->size4Button->isChecked()) {
        ui->ele11->setVisible(true);
        ui->ele12->setVisible(true);
        ui->ele21->setVisible(true);
        ui->ele22->setVisible(true);
        ui->ele13->setVisible(true);
        ui->ele14->setVisible(true);
        ui->ele23->setVisible(true);
        ui->ele24->setVisible(true);
        ui->ele31->setVisible(true);
        ui->ele32->setVisible(true);
        ui->ele33->setVisible(true);
        ui->ele34->setVisible(true);
        ui->ele41->setVisible(true);
        ui->ele42->setVisible(true);
        ui->ele43->setVisible(true);
        ui->ele44->setVisible(true);

        ui->ele11->setText(QString::number(1));
        ui->ele12->setText(QString::number(1));
        ui->ele21->setText(QString::number(1));
        ui->ele22->setText(QString::number(1));
        ui->ele13->setText(QString::number(1));
        ui->ele14->setText(QString::number(1));
        ui->ele23->setText(QString::number(1));
        ui->ele24->setText(QString::number(1));
        ui->ele31->setText(QString::number(1));
        ui->ele32->setText(QString::number(1));
        ui->ele33->setText(QString::number(1));
        ui->ele34->setText(QString::number(1));
        ui->ele41->setText(QString::number(1));
        ui->ele42->setText(QString::number(1));
        ui->ele43->setText(QString::number(1));
        ui->ele44->setText(QString::number(1));
    }
}

void GrayScaleMorDialog::changeType()
{
    MainWindow *w = (MainWindow *)parentWidget();
    cv::Mat mat = Algo::QImage2cvMat(tmp);
    cv::Mat result;

    std::vector<std::vector<int>> kernel;
    if (ui->size2Button->isChecked()) {
        std::vector<int> line1;
        std::vector<int> line2;
        line1.push_back(ui->ele11->text().toInt());
        line1.push_back(ui->ele12->text().toInt());
        line2.push_back(ui->ele21->text().toInt());
        line2.push_back(ui->ele22->text().toInt());
        kernel.push_back(line1);
        kernel.push_back(line2);
    }
    else if (ui->size3Button->isChecked()) {
        std::vector<int> line1;
        std::vector<int> line2;
        std::vector<int> line3;
        line1.push_back(ui->ele11->text().toInt());
        line1.push_back(ui->ele12->text().toInt());
        line1.push_back(ui->ele13->text().toInt());
        line2.push_back(ui->ele21->text().toInt());
        line2.push_back(ui->ele22->text().toInt());
        line2.push_back(ui->ele23->text().toInt());
        line3.push_back(ui->ele31->text().toInt());
        line3.push_back(ui->ele32->text().toInt());
        line3.push_back(ui->ele33->text().toInt());
        kernel.push_back(line1);
        kernel.push_back(line2);
        kernel.push_back(line3);
    }
    else if (ui->size4Button->isChecked()) {
        std::vector<int> line1;
        std::vector<int> line2;
        std::vector<int> line3;
        std::vector<int> line4;
        line1.push_back(ui->ele11->text().toInt());
        line1.push_back(ui->ele12->text().toInt());
        line1.push_back(ui->ele13->text().toInt());
        line1.push_back(ui->ele14->text().toInt());
        line2.push_back(ui->ele21->text().toInt());
        line2.push_back(ui->ele22->text().toInt());
        line2.push_back(ui->ele23->text().toInt());
        line2.push_back(ui->ele24->text().toInt());
        line3.push_back(ui->ele31->text().toInt());
        line3.push_back(ui->ele32->text().toInt());
        line3.push_back(ui->ele33->text().toInt());
        line3.push_back(ui->ele34->text().toInt());
        line4.push_back(ui->ele41->text().toInt());
        line4.push_back(ui->ele42->text().toInt());
        line4.push_back(ui->ele43->text().toInt());
        line4.push_back(ui->ele44->text().toInt());
        kernel.push_back(line1);
        kernel.push_back(line2);
        kernel.push_back(line3);
        kernel.push_back(line4);
    }
    if (ui->dilationButton->isChecked()) {
        result = Algo::grayDilation(mat, kernel);
    }
    else if (ui->erosionButton->isChecked()) {
        result = Algo::grayErosion(mat, kernel);
    }
    else if (ui->openButton->isChecked()) {
        result = Algo::grayOpen(mat, kernel);
    }
    else if (ui->closeButton->isChecked()) {
        result = Algo::grayClose(mat, kernel);
    }
    else if (ui->reconstructButton->isChecked()) {
        result = morphologicalReconstruct(mat, kernel);
    }
    else if (ui->watershedButton->isChecked()) {
        result = Algo::watershed(mat);
    }
    QImage image = Algo::cvMat2QImage(result);
    w->setImage(image);
    w->showTemp();
}

cv::Mat GrayScaleMorDialog::morphologicalReconstruct(cv::Mat mat, std::vector<std::vector<int>>& kernel)
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setText("请选择重构算法：");
    msgBox->setStyleSheet("QMessageBox{background-color:rgb(65, 65, 65);}"
                          "QMessageBox QLabel{color:rgb(221, 221, 221);qproperty-alignment: AlignCenter;}"
                          "QPushButton{border:2px groove rgb(221, 221, 221);"
                          "border-radius: 6px;color:rgb(221, 221, 221);padding: 2px 5px;}"
                          "QPushButton:hover{border:2px groove rgb(221, 221, 221);"
                          "color: rgb(83, 83, 83);background-color: rgb(221, 221, 221);}"
                          "QPushButton:pressed{border:2px groove rgb(70, 160, 245);"
                          "color: rgb(221, 221, 221);background-color: rgb(70, 160, 245);}");
    QPushButton *btn_dilation = msgBox->addButton("测地膨胀", QMessageBox::ActionRole);
    QPushButton *btn_erosion = msgBox->addButton("测地腐蚀", QMessageBox::ActionRole);
    btn_dilation->setCursor(Qt::PointingHandCursor);
    btn_erosion->setCursor(Qt::PointingHandCursor);
    msgBox->exec();
    if (msgBox->clickedButton() == btn_dilation) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开图片"), ".", tr("Images (*.png *.xpm *.jpg *.bmp *.jpeg)"));
        QImage addImage;
        if (!fileName.isEmpty()) {
            if(!addImage.load(fileName)) {
                QMessageBox::information(this, tr("Error"), tr("打开图像失败!"));
                return mat;
            }
            cv::Mat add = Algo::QImage2cvMat(addImage);
            if (mat.type() != add.type()) {
                QMessageBox::information(this, tr("Error"), tr("图像通道不匹配！"));
                return mat;
            }
            return Algo::grayGeodesticDilation(mat, add, kernel);
        }
    }
    else if (msgBox->clickedButton() == btn_erosion) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开图片"), ".", tr("Images (*.png *.xpm *.jpg *.bmp *.jpeg)"));
        QImage addImage;
        if (!fileName.isEmpty()) {
            if(!addImage.load(fileName)) {
                QMessageBox::information(this, tr("Error"), tr("打开图像失败!"));
                return mat;
            }
            cv::Mat add = Algo::QImage2cvMat(addImage);
            if (mat.type() != add.type()) {
                QMessageBox::information(this, tr("Error"), tr("图像通道不匹配！"));
                return mat;
            }
            return Algo::grayGeodesticErosion(mat, add, kernel);
        }
    }
    return mat;
}

void GrayScaleMorDialog::conform()
{
    MainWindow *w = (MainWindow *)parentWidget();
    w->showImage();
    isConform = true;
    this->close();
}

void GrayScaleMorDialog::cancel()
{
    this->close();
}

void GrayScaleMorDialog::closeEvent(QCloseEvent *e)
{
    if (!isConform) {
        MainWindow *w = (MainWindow *)parentWidget();
        w->setImage(tmp);
        w->showTemp();
    }
    e->accept();
}
