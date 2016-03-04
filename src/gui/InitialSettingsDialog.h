#ifndef INITIALSETTINGSDIALOG_H_
#define INITIALSETTINGSDIALOG_H_

#include <QDialog>

#include <memory>

#include "InitialSetings.h"

namespace Ui {
    class InitialSettingsDialog;
}

class InitialSettingsDialog: public QDialog {
    Q_OBJECT

public:
    InitialSettingsDialog(const InitialSettings& values,
            QWidget* parent = nullptr);
    ~InitialSettingsDialog();

    InitialSettingsDialog(const InitialSettingsDialog& other) = delete;
    InitialSettingsDialog(InitialSettingsDialog&& other) noexcept = delete;
    InitialSettingsDialog& operator =(const InitialSettingsDialog& other) = delete;
    InitialSettingsDialog& operator =(InitialSettingsDialog&& other) noexcept = delete;

    void set_values(const InitialSettings& values);
    const InitialSettings& values() const {return m_accepted_initial_settings;}

signals:
    void values_accepted();

private:

    void setup_signals();

    void update_ui();

    void on_accept();

    InitialSettings m_initial_settings;
    InitialSettings m_accepted_initial_settings;

    std::unique_ptr<Ui::InitialSettingsDialog> ui;    
};

#endif
