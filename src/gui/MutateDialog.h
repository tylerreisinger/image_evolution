#ifndef MUTATEDIALOG_H_
#define MUTATEDIALOG_H_

#include <QDialog>

#include <memory>

#include "Mutator.h"

namespace Ui {
    class MutateDialog;
}

class MutateDialog: public QDialog {
    Q_OBJECT

public:
    MutateDialog(const Mutator& mutator, QWidget* parent = 0);
    ~MutateDialog();

    MutateDialog(const MutateDialog& other) = delete;
    MutateDialog(MutateDialog&& other) noexcept = delete;
    MutateDialog& operator =(const MutateDialog& other) = delete;
    MutateDialog& operator =(MutateDialog&& other) noexcept = delete;

    const Mutator& mutator() const {return *m_accepted_mutator;}

    void set_mutator(const Mutator& mutator);

signals:
    void values_accepted();

private:
    void setup_signals();

    void update_ui();
    void update_replace_values();

    void on_accept();

    std::unique_ptr<Mutator> m_mutator;
    std::unique_ptr<Mutator> m_accepted_mutator;
    std::unique_ptr<Ui::MutateDialog> ui;
};

#endif
