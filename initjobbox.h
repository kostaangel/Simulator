#ifndef INITJOBBOX_H
#define INITJOBBOX_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>

class InitJobBox : public QDialog
{
    Q_OBJECT
public:
    explicit InitJobBox(QWidget *parent = 0);

    QString createInitJobXml();

private:
    QString m_daimlerUser;
    QString m_dmsUser;

    QLineEdit *m_orderIdEdit;
    QDateTimeEdit *m_receptionDate;
    QDateTimeEdit *m_returnDate;
    QLineEdit *m_serviceAdvisorFirstNameEdit;
    QLineEdit *m_serviceAdvisorLastNameEdit;

    QLineEdit *m_FinOrVinEdit;
    QDateEdit *m_FirstRegistrationDate;
    QLineEdit *m_OdometerReadingEdit;
    QLineEdit *m_OperatingHoursEdit;
    QLineEdit *m_RegistrationNumberEdit;

    QLineEdit *m_customerFirstNameEdit;
    QLineEdit *m_customerLastNameEdit;
    QLineEdit *m_customerPhoneNumberEdit;

    QPushButton *m_initJobBtn;
    QPushButton *m_cancelBtn;

private slots:
    void initBtnPressed();
};

#endif // INITJOBBOX_H
