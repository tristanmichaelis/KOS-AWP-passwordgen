#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generator.h"

#define PASSWORD_MINLENGTH 1
#define PASSWORD_MAXLENGTH 99

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    inline void on_pushButton_generate_clicked() { generate_passwords(); };

    inline void on_radioButton_lower_clicked() { handle_active_button(); };
    inline void on_radioButton_upper_clicked() { handle_active_button(); };
    inline void on_radioButton_numbers_clicked() { handle_active_button(); };
    inline void on_radioButton_special_clicked() { handle_active_button(); };

    inline void on_spinBox_length_valueChanged(int) { check_spinbox_minmax();};

    inline void on_spinBox_lower_valueChanged(int) { restrict_characters(); };
    inline void on_spinBox_upper_valueChanged(int) { restrict_characters(); };
    inline void on_spinBox_numbers_valueChanged(int) { restrict_characters(); };
    inline void on_spinBox_special_valueChanged(int) { restrict_characters(); };

private:
    Ui::MainWindow *ui;
    void handle_active_button();
    void restrict_characters();
    void check_spinbox_minmax();
    void generate_passwords();
    void mytest();
};

template<typename Func> void for_every_charset(const Func& f);

#endif // MAINWINDOW_H
