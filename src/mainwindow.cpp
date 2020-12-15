#include "mainwindow.h"
#include "ui_mainwindow.h"

generator g_gen;
std::vector<std::tuple<QSpinBox *, std::__cxx11::basic_string<char>>> g_gui_charset_mapping;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Initialize UI
    ui->setupUi(this);
    ui->buttonGroup->setId(ui->radioButton_lower, 0);   // 0000 -- Bitmasking
    ui->buttonGroup->setId(ui->radioButton_upper, 1);   // 0001
    ui->buttonGroup->setId(ui->radioButton_numbers, 3); // 0011 <-- Default
    ui->buttonGroup->setId(ui->radioButton_special, 7); // 0111

    // Create mapping between generator charset and GUI options.
    g_gui_charset_mapping = {
        std::make_tuple(ui->spinBox_lower, PasswordConstants::c_lowercase),
        std::make_tuple(ui->spinBox_upper, PasswordConstants::c_uppercase),
        std::make_tuple(ui->spinBox_numbers, PasswordConstants::c_numbers),
        std::make_tuple(ui->spinBox_special, PasswordConstants::c_special)
    };

    // Refresh generator (to match GUI)
    handle_active_button();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate_passwords()
{
    for(std::string s : g_gen.generateMultiplePasswords(ui->spinBox_amount->value()))
    {
        ui->textEdit_output->append(QString::fromUtf8(s.c_str()));
        /*
         * ToDo: file handling
         */
    }
}

void MainWindow::handle_active_button()
{
    int selectedButton = ui->buttonGroup->checkedId();
    std::string charset = "";

    // Use Bitmasking to enable spinboxes
    ui->spinBox_upper->setEnabled(selectedButton & 1);
    ui->spinBox_numbers->setEnabled(selectedButton & 2);
    ui->spinBox_special->setEnabled(selectedButton & 4);

    // Use Bitmasking to fallthrough the default charset
    switch (selectedButton){
    case 7:
        charset.append(PasswordConstants::c_special);
        [[fallthrough]];
    case 3:
        charset.append(PasswordConstants::c_numbers);
        [[fallthrough]];
    case 1:
        charset.append(PasswordConstants::c_uppercase);
        [[fallthrough]];
    default:
        charset.append(PasswordConstants::c_lowercase);
    }

    g_gen.setCharSet(charset);      // Set the default character set
    restrict_characters();          // Finally take care of obligatory characters
}

void MainWindow::restrict_characters()
{
    g_gen.clearObligatoryChars();                               // Reset generators restrictions
    check_spinbox_minmax();                                     // Assure, that all lengths are valid

    for_every_charset([&] (QSpinBox * sb, std::__cxx11::basic_string<char> charset) {
        if(sb->isEnabled())
        {
            g_gen.addObligatoryChars(sb->value(), charset);     // Add enabled restrictions to the generator
        }
    });
}

void MainWindow::check_spinbox_minmax()
{
    int minimum_length = 0;

    // Should the minimum length now go above PASSWORD_MAXLENGTH, set the spinbox´s value to 0.
    // After potential 0-setting, add its value to minimum_length
    for_every_charset([&] (QSpinBox *sb, std::__cxx11::basic_string<char>) {
        if(sb->isEnabled())
        {
            if (minimum_length + sb->value() > PASSWORD_MAXLENGTH)
            {
                sb->setValue(0);
            }
            minimum_length += sb->value();
        }
    });

    // Set Minimum of the Length spinbox to its lowest possible value and refresh the generator
    ui->spinBox_length->setMinimum(minimum_length >= PASSWORD_MINLENGTH ? minimum_length : PASSWORD_MINLENGTH);
    g_gen.setLength(ui->spinBox_length->value());

    // Restrict Maximum Length of every spinbox, so that in total it's not possible to go above PASSWORD_MAXLENGTH
    for_every_charset([&] (QSpinBox * sb, std::__cxx11::basic_string<char>) {
        sb->setMaximum(PASSWORD_MAXLENGTH + sb->value() - minimum_length);
    });
}

template<typename Func> void for_every_charset(const Func& f) {
    // Loops through every < spinbox, characters > from the global charset vector
    for (std::tuple<QSpinBox *, std::__cxx11::basic_string<char>> t : g_gui_charset_mapping)
    {
        QSpinBox *sb;
        std::string charset;
        tie(sb, charset) = t;

        // Execute passed functions with (spinbox, charset)
        f(sb, charset);
    }
}
