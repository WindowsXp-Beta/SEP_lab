#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this))
{
    ui->setupUi(this);
    setCentralWidget(view);
    connect(ui->actionopen, &QAction::triggered, this, &MainWindow::readFiles);
    scene->setSceneRect(-10, -10, 20, 20);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Box *item = battleField.field[i][j];
            scene->addItem(item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFiles()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Application"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
            return;
        }
        QTextStream in(&file);
        QString line;
        line = in.readLine();//get N
        int number = line.toInt();
        while( !(line = in.readLine()).isNull() ){
            number--;
            if(number < 0){
                break;
            }
            QStringList range = line.split(' ');
            int x1 = range.at(0).toInt();
            int y1 = range.at(1).toInt();
            int x2 = range.at(2).toInt();
            int y2 = range.at(3).toInt();
            for(int i = x1; i <= x2; i++){
                for(int j = y1; j <= y2; j++){
                    battleField.field[i][j]->type = Box::Enemy;
                    battleField.maze[j + 1][i + 1] = 1;
                }
            }
        }
    }
    drawMap();
}

void MainWindow::drawMap()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Box *item = battleField.field[i][j];
            item->update();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_P){
        bool flag = battleField.findPath();
        if(flag) {
            drawMap();
        } else {
            QMessageBox::information(this, tr("error"), tr("cannot find path"));
        }
    }
}
