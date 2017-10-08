#ifndef SIMULATOR_TEST_H
#define SIMULATOR_TEST_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QPushButton>

class Simulator_Test : public QWidget
{
    Q_OBJECT

public:
    Simulator_Test(QWidget *parent = 0);
    ~Simulator_Test();

private:
    QNetworkAccessManager *m_nam;

    QPushButton *m_initJobBtn;
    QPushButton *m_GetPricesTechnicalJob_getDataByIdBtn;
    QPushButton *m_GetPricesTechnicalJobResponceBtn;
    QPushButton *m_GetPricesTechnicalJob_Deactivated_Request_getDataByIdBtn;
    QPushButton *m_GetPricesTechnicalJob_Deactivated_ResponseBtn;
    QPushButton *m_TransferJobToDms_Request_getDataByIdBtn;
    QPushButton *m_TransferJobToDms_ResponseBtn;
    QPushButton *m_TransferJobToErepko_ResponseBtn;
    QPushButton *m_FinishOrderResponseBtn;
    QPushButton *m_GetInvoiceCodesRequest_getDataByIdBtn;
    QPushButton *m_GetInvoiceCodesResponseBtn;
    QPushButton *m_RunVerificationRequest_getDataByIdBtn;
    QPushButton *m_RunVerificationResponseBtn;
    QPushButton *m_GetLocalOperationsRequest_getDataByIdBtn;
    QPushButton *m_GetLocalOperationsResponseBtn;
    QPushButton *m_ServiceFault_from_DMSBtn;
    QPushButton *m_ServiceFault_from_XENTRY_PortalBtn;

    QPushButton *m_ConnectPartsListAndOrderRequestBtn;
    QPushButton *m_GetDetailsFromPartsSearchRequestBtn;
    QPushButton *m_GetPricesPartsResponseBtn;

    void setupUi();

    void parseXml(QByteArray replyString);
    QByteArray gUncompress(const QByteArray &data);
    QByteArray gzipDecompress( QByteArray compressData );

private slots:
    void finished(QNetworkReply *reply);
    void sslErrorIgnore(QNetworkReply* qnr, const QList<QSslError> & errlist);
    void authenticationNeeded(QNetworkReply*,QAuthenticator*);
    void testFunc();

    void initJobRequest();
    void GetPricesTechnicalJob_getDataByIdSlot();
    void GetPricesTechnicalJobResponceSlot();
    void GetPricesTechnicalJob_Deactivated_Request_getDataByIdSlot();
    void GetPricesTechnicalJob_Deactivated_ResponseSlot();
    void TransferJobToDms_Request_getDataByIdSlot();
    void TransferJobToDms_ResponseSlot();
    void TransferJobToErepko_ResponseSlot();
    void FinishOrderResponseSlot();
    void GetInvoiceCodesRequest_getDataByIdSlot();
    void GetInvoiceCodesResponseSlot();
    void RunVerificationRequest_getDataByIdSlot();
    void RunVerificationResponseSlot();
    void GetLocalOperationsRequest_getDataByIdSlot();
    void GetLocalOperationsResponseSlot();
    void ServiceFault_from_DMSSlot();
    void ServiceFault_from_XENTRY_PortalSlot();

    void ConnectPartsListAndOrderRequestSlot();
    void GetDetailsFromPartsSearchRequestSlot();
    void GetPricesPartsResponseSlot();

    void createInitJobXml();
};

#endif // SIMULATOR_TEST_H
