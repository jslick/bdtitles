#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chapterswidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void readChapters();

private:
    ChaptersWidget* chaptersWidget = nullptr;
};

#endif // MAINWINDOW_H
