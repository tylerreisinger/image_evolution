#ifndef MIPMAPDIALOG_H_
#define MIPMAPDIALOG_H_

#include <QDialog>

#include <memory>

#include "MipmapSettings.h"

namespace Ui {
    class MipmapDialog;
}

class MipmapDialog: public QDialog {
    Q_OBJECT

public:
    MipmapDialog(const MipmapSettings& values, QWidget* parent = nullptr);
    ~MipmapDialog();

    MipmapDialog(const MipmapDialog& other) = delete;
    MipmapDialog(MipmapDialog&& other) noexcept = delete;
    MipmapDialog& operator =(const MipmapDialog& other) = delete;
    MipmapDialog& operator =(MipmapDialog&& other) noexcept = delete;

    void set_values(const MipmapSettings& values);
    const MipmapSettings& values() const {return m_accepted_values;}

signals:
    void values_accepted();
    
private:

    void update_is_adaptive_scaling_enabled(bool val);

    void setup_signals();
    void update_ui();
    void on_accept();

    void on_adaptive_scaling_checked(int val);

    MipmapSettings m_values;
    MipmapSettings m_accepted_values;

    std::unique_ptr<Ui::MipmapDialog> ui;
};

#endif
