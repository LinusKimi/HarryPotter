//
// Created by airlc on 2020/3/18.
//

#ifndef TOOLS_MAINWINDOW_H
#define TOOLS_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "FrameInfoDialog.h"

class QPushButton;

class QComboBox;

class QTextBrowser;

class QCheckBox;

class QLineEdit;

class QLabel;

class QTextEdit;

class QTimer;

class SerialSettings;

class AbstractReadWriter;

class QRadioButton;

class QButtonGroup;

class SerialController;

struct RunConfig {
    QString lastDir;
    QString lastFilePath;
};

class MainWindow: public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    enum class SerialType {
        Normal = 1,
        TcpServer,
        TcpClient,
        Bridge,
        SerialBridge,
    };

    void initUi();


public:

signals:



public slots:





private:


    enum class AutoSendState {
        NotStart, Sending, Finish
    };

    RunConfig *runConfig{nullptr};

    //状态栏
    QLabel *statusBarReadBytesLabel;
    QLabel *statusBarWriteBytesLabel;
    QPushButton *statusBarResetCountButton;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *validateDataAct;
    QAction *convertDataAct;

    AbstractReadWriter *_readWriter{nullptr};

    qint64 sendCount{0};
    qint64 receiveCount{0};

    QRadioButton *serialRadioButton;
    QRadioButton *tcpServerRadioButton;
    QRadioButton *tcpClientRadioButton;
    QRadioButton *bridgeRadioButton;
    QRadioButton *serialBridgeRadioButton;

    QButtonGroup *readWriterButtonGroup;

    // 串口设置
    QComboBox *serialPortNameComboBox;
    QComboBox *serialPortBaudRateComboBox;
    QComboBox *serialPortParityComboBox;
    QComboBox *serialPortDataBitsComboBox;
    QComboBox *serialPortStopBitsComboBox;
    QPushButton *openSerialButton;
    QPushButton *refreshSerialButton;

    // 第二串口设置
    QComboBox *secondSerialPortNameComboBox;
    QComboBox *secondSerialPortBaudRateComboBox;
    QComboBox *secondSerialPortParityComboBox;
    QComboBox *secondSerialPortDataBitsComboBox;
    QComboBox *secondSerialPortStopBitsComboBox;

    // TCP设置
    QLineEdit *tcpAddressLineEdit;
    QLineEdit *tcpPortLineEdit;
    QLabel *tcpClientLabel;

    // 接收设置
    QCheckBox *addLineReturnCheckBox;
    QCheckBox *displayReceiveDataAsHexCheckBox;
    QCheckBox *pauseReceiveCheckBox;
    QPushButton *saveReceiveDataButton;
    QPushButton *clearReceiveDataButton;
    QCheckBox *addReceiveTimestampCheckBox;

    // 发送设置
    QCheckBox *sendHexCheckBox;
    QCheckBox *displaySendDataCheckBox;
    QCheckBox *displaySendDataAsHexCheckBox;
    QCheckBox *autoSendCheckBox;
    QLineEdit *sendIntervalLineEdit;
    QLineEdit *emptyLineDelayLindEdit;
    QPushButton *frameInfoSettingButton;
    QPushButton *saveSentDataButton;
    QPushButton *clearSentDataButton;

    QCheckBox *loopSendCheckBox;
    QPushButton *resetLoopSendButton;
    QLineEdit *currentSendCountLineEdit;
    QLabel *totalSendCountLabel;

    FrameInfo *frameInfo;


    QTextBrowser *receiveDataBrowser;
    QTextBrowser *sendDataBrowser;

    QTextEdit *sendTextEdit;

    QPushButton *sendFrameButton;
    QPushButton *sendLineButton;
    QPushButton *sendFixBytesButton;
    QLineEdit *byteCountLineEdit;
    QPushButton *sendAllButton;

    AutoSendState autoSendState{AutoSendState::NotStart};

    QTimer *autoSendTimer{nullptr};


    SerialController *serialController{nullptr};

};


#endif //TOOLS_MAINWINDOW_H
