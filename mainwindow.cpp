//
// Created by airlc on 2020/3/18.
//
#include <QAction>
#include <QCheckBox>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QtSerialPort/QSerialPort>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QDebug>
#include <QTextBrowser>
#include <QtWidgets/QFileDialog>
#include <QTimer>
#include <QtCore/QSettings>
#include <QtCore/QProcess>
#include <QStatusBar>
#include <QSplitter>
#include <QRadioButton>
#include <QButtonGroup>
#include <QtSerialPort/QSerialPortInfo>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), receiveCount(0), sendCount(0) {

    initUi();
}

MainWindow::~MainWindow() {

}

void MainWindow::initUi() {

    setWindowTitle(tr("串口调试工具"));

    setMinimumSize(1280, 900);

    serialRadioButton = new QRadioButton(tr("串口"), this);
    tcpServerRadioButton = new QRadioButton("TCP(服务器)", this);
    tcpClientRadioButton = new QRadioButton("TCP(客户端)", this);
    bridgeRadioButton = new QRadioButton(tr("桥接"), this);
    serialBridgeRadioButton = new QRadioButton(tr("转发"), this);

    serialRadioButton->setChecked(true);

    serialRadioButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tcpServerRadioButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tcpClientRadioButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    bridgeRadioButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    readWriterButtonGroup = new QButtonGroup;
    readWriterButtonGroup->addButton(serialRadioButton);
    readWriterButtonGroup->addButton(tcpServerRadioButton);
    readWriterButtonGroup->addButton(tcpClientRadioButton);
    readWriterButtonGroup->addButton(bridgeRadioButton);
    readWriterButtonGroup->addButton(serialBridgeRadioButton);

    auto readWriterButtonLayout = new QGridLayout;
    readWriterButtonLayout->addWidget(serialRadioButton, 0, 0);
    readWriterButtonLayout->addWidget(bridgeRadioButton, 0, 1);
    readWriterButtonLayout->addWidget(tcpServerRadioButton, 1, 0);
    readWriterButtonLayout->addWidget(tcpClientRadioButton, 1, 1);
    readWriterButtonLayout->addWidget(serialBridgeRadioButton, 2, 0);


    auto readWriterButtonGroupBox = new QGroupBox(tr("打开模式"));
    readWriterButtonGroupBox->setLayout(readWriterButtonLayout);

    auto serialPortNameLabel = new QLabel(tr("串口"), this);

    serialPortNameComboBox = new QComboBox(this);
    serialPortNameLabel->setBuddy(serialPortNameComboBox);

    auto *serialPortBaudRateLabel = new QLabel(tr("波特率"), this);
    serialPortBaudRateComboBox = new QComboBox(this);
    serialPortBaudRateComboBox->addItems(QStringList()
                                                 << "1200"
                                                 << "2400"
                                                 << "4800"
                                                 << "9600"
                                                 << "19200"
                                                 << "38400"
                                                 << "25600"
                                                 << "57600"
                                                 << "115200"
                                                 << "256000"
    );
    serialPortBaudRateLabel->setBuddy(serialPortBaudRateComboBox);


    auto serialPortDataBitsLabel = new QLabel(tr("数据位"), this);
    serialPortDataBitsComboBox = new QComboBox(this);
    serialPortDataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
    serialPortDataBitsLabel->setBuddy(serialPortDataBitsComboBox);

    auto serialPortStopBitsLabel = new QLabel(tr("停止位"), this);
    serialPortStopBitsComboBox = new QComboBox(this);
    serialPortStopBitsLabel->setBuddy(serialPortStopBitsComboBox);
    serialPortStopBitsComboBox->addItem(tr("1"), QSerialPort::OneStop);
    serialPortStopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    serialPortStopBitsComboBox->addItem(tr("2"), QSerialPort::TwoStop);

    auto serialPortParityLabel = new QLabel(tr("校验位"), this);
    serialPortParityComboBox = new QComboBox(this);
    serialPortParityComboBox->addItem(tr("无校验"), QSerialPort::NoParity);
    serialPortParityComboBox->addItem(tr("奇校验"), QSerialPort::OddParity);
    serialPortParityComboBox->addItem(tr("偶校验"), QSerialPort::EvenParity);
    serialPortParityComboBox->addItem(tr("空校验"), QSerialPort::SpaceParity);
    serialPortParityComboBox->addItem(tr("标志校验"), QSerialPort::MarkParity);
    serialPortParityLabel->setBuddy(serialPortParityComboBox);


    auto serialPortSettingsGridLayout = new QGridLayout;
    serialPortSettingsGridLayout->addWidget(serialPortNameLabel, 0, 0);
    serialPortSettingsGridLayout->addWidget(serialPortNameComboBox, 0, 1);
    serialPortSettingsGridLayout->addWidget(serialPortBaudRateLabel, 1, 0);
    serialPortSettingsGridLayout->addWidget(serialPortBaudRateComboBox, 1, 1);
    serialPortSettingsGridLayout->addWidget(serialPortDataBitsLabel, 2, 0);
    serialPortSettingsGridLayout->addWidget(serialPortDataBitsComboBox, 2, 1);
    serialPortSettingsGridLayout->addWidget(serialPortStopBitsLabel, 3, 0);
    serialPortSettingsGridLayout->addWidget(serialPortStopBitsComboBox, 3, 1);
    serialPortSettingsGridLayout->addWidget(serialPortParityLabel, 4, 0);
    serialPortSettingsGridLayout->addWidget(serialPortParityComboBox, 4, 1);

    auto secondSerialPortNameLabel = new QLabel(tr("串口"), this);


    secondSerialPortNameComboBox = new QComboBox(this);
    secondSerialPortNameLabel->setBuddy(secondSerialPortNameComboBox);

    auto *secondSerialPortBaudRateLabel = new QLabel(tr("波特率"), this);
    secondSerialPortBaudRateComboBox = new QComboBox(this);
    secondSerialPortBaudRateComboBox->addItems(QStringList()
                                                       << "1200"
                                                       << "2400"
                                                       << "4800"
                                                       << "9600"
                                                       << "19200"
                                                       << "38400"
                                                       << "25600"
                                                       << "57600"
                                                       << "115200"
                                                       << "256000"
    );
    secondSerialPortBaudRateLabel->setBuddy(secondSerialPortBaudRateComboBox);


    auto secondSerialPortDataBitsLabel = new QLabel(tr("数据位"), this);
    secondSerialPortDataBitsComboBox = new QComboBox(this);
    secondSerialPortDataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
    secondSerialPortDataBitsLabel->setBuddy(secondSerialPortDataBitsComboBox);

    auto secondSerialPortStopBitsLabel = new QLabel(tr("停止位"), this);
    secondSerialPortStopBitsComboBox = new QComboBox(this);
    secondSerialPortStopBitsLabel->setBuddy(secondSerialPortStopBitsComboBox);
    secondSerialPortStopBitsComboBox->addItem(tr("1"), QSerialPort::OneStop);
    secondSerialPortStopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    secondSerialPortStopBitsComboBox->addItem(tr("2"), QSerialPort::TwoStop);

    auto secondSerialPortParityLabel = new QLabel(tr("校验位"), this);
    secondSerialPortParityComboBox = new QComboBox(this);
    secondSerialPortParityComboBox->addItem(tr("无校验"), QSerialPort::NoParity);
    secondSerialPortParityComboBox->addItem(tr("奇校验"), QSerialPort::OddParity);
    secondSerialPortParityComboBox->addItem(tr("偶校验"), QSerialPort::EvenParity);
    secondSerialPortParityComboBox->addItem(tr("空校验"), QSerialPort::SpaceParity);
    secondSerialPortParityComboBox->addItem(tr("标志校验"), QSerialPort::MarkParity);
    secondSerialPortParityLabel->setBuddy(secondSerialPortParityComboBox);


    auto secondSerialPortSettingsGridLayout = new QGridLayout;
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortNameLabel, 0, 0);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortNameComboBox, 0, 1);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortBaudRateLabel, 1, 0);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortBaudRateComboBox, 1, 1);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortDataBitsLabel, 2, 0);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortDataBitsComboBox, 2, 1);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortStopBitsLabel, 3, 0);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortStopBitsComboBox, 3, 1);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortParityLabel, 4, 0);
    secondSerialPortSettingsGridLayout->addWidget(secondSerialPortParityComboBox, 4, 1);

    auto firstSerialSettingsWidget = new QWidget();
    firstSerialSettingsWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    firstSerialSettingsWidget->setLayout(serialPortSettingsGridLayout);

    auto secondSerialSettingsWidget = new QWidget();
    secondSerialSettingsWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    secondSerialSettingsWidget->setLayout(secondSerialPortSettingsGridLayout);

    auto serialTabWidget = new QTabWidget(this);
    serialTabWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    serialTabWidget->addTab(firstSerialSettingsWidget, tr("第一串口设置"));
    serialTabWidget->addTab(secondSerialSettingsWidget, tr("第二串口设置"));

    openSerialButton = new QPushButton(tr("打开"), this);
    refreshSerialButton = new QPushButton(tr("刷新串口列表"), this);

    auto serialOpenRefreshLayout = new QHBoxLayout;
    serialOpenRefreshLayout->addWidget(openSerialButton);
    serialOpenRefreshLayout->addWidget(refreshSerialButton);

    tcpAddressLineEdit = new QLineEdit(this);
    tcpAddressLineEdit->setMaximumWidth(100);
    tcpAddressLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    tcpPortLineEdit = new QLineEdit(this);
    tcpPortLineEdit->setMaximumWidth(50);
    tcpPortLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    tcpClientLabel = new QLabel(this);

    auto tcpEditLayout = new QHBoxLayout;
    tcpEditLayout->addWidget(tcpAddressLineEdit);
    tcpEditLayout->addWidget(tcpPortLineEdit);
    auto tcpLayout = new QVBoxLayout;
    tcpLayout->addStretch();
    tcpLayout->addLayout(tcpEditLayout);
    tcpLayout->addWidget(tcpClientLabel);
    tcpLayout->addStretch();

    auto tcpGroupBox = new QGroupBox(tr("TCP设置"));
    tcpGroupBox->setLayout(tcpLayout);

    addLineReturnCheckBox = new QCheckBox(tr("自动换行"), this);
    displayReceiveDataAsHexCheckBox = new QCheckBox(tr("十六进制显示"), this);
    addReceiveTimestampCheckBox = new QCheckBox(tr("添加时间戳"), this);
    pauseReceiveCheckBox = new QCheckBox(tr("暂停接收"), this);
    saveReceiveDataButton = new QPushButton(tr("保存数据"), this);
    clearReceiveDataButton = new QPushButton(tr("清除显示"), this);

    auto receiveSettingLayout = new QGridLayout;
    receiveSettingLayout->addWidget(addLineReturnCheckBox, 0, 0);
    receiveSettingLayout->addWidget(displayReceiveDataAsHexCheckBox, 0, 1);
    receiveSettingLayout->addWidget(addReceiveTimestampCheckBox, 1, 0);
    receiveSettingLayout->addWidget(pauseReceiveCheckBox, 1, 1);

    receiveSettingLayout->addWidget(saveReceiveDataButton, 2, 0);
    receiveSettingLayout->addWidget(clearReceiveDataButton, 2, 1);

    auto receiveSettingGroupBox = new QGroupBox(tr("接收设置"));
    receiveSettingGroupBox->setLayout(receiveSettingLayout);

    receiveDataBrowser = new QTextBrowser(this);
    receiveDataBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto receiveDataLayout = new QVBoxLayout;
    receiveDataLayout->addWidget(receiveDataBrowser);
    auto receiveDataGroupBox = new QGroupBox(tr("数据接收显示"));
    receiveDataGroupBox->setLayout(receiveDataLayout);
    receiveDataGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    sendHexCheckBox = new QCheckBox(tr("十六进制发送"), this);
    displaySendDataCheckBox = new QCheckBox(tr("显示发送数据"), this);
    displaySendDataAsHexCheckBox = new QCheckBox(tr("十六进制显示"), this);


    autoSendCheckBox = new QCheckBox(tr("自动发送"), this);
    auto sendIntervalLabel = new QLabel(tr("间隔(毫秒)"), this);
    sendIntervalLineEdit = new QLineEdit(this);
    sendIntervalLineEdit->setMaximumWidth(50);
    sendIntervalLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    sendIntervalLabel->setBuddy(sendIntervalLineEdit);

    auto emptyLineDelayLabel = new QLabel(tr("空行间隔(毫秒)"), this);
    emptyLineDelayLindEdit = new QLineEdit(this);
    emptyLineDelayLindEdit->setMaximumWidth(50);
    emptyLineDelayLindEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    emptyLineDelayLabel->setBuddy(emptyLineDelayLindEdit);

    auto emptyLineDelayLayout = new QHBoxLayout;
    emptyLineDelayLayout->addWidget(emptyLineDelayLabel);
    emptyLineDelayLayout->addWidget(emptyLineDelayLindEdit);

    auto autoSendLayout = new QHBoxLayout;
    autoSendLayout->addWidget(autoSendCheckBox);
    autoSendLayout->addWidget(sendIntervalLabel);
    autoSendLayout->addWidget(sendIntervalLineEdit);

    auto autoSendSettingsLayout = new QVBoxLayout;
    autoSendSettingsLayout->addLayout(autoSendLayout);
    autoSendSettingsLayout->addLayout(emptyLineDelayLayout);
    auto autoSendGroupBox = new QGroupBox("自动发送设置");
    autoSendGroupBox->setLayout(autoSendSettingsLayout);

    loopSendCheckBox = new QCheckBox(tr("循环发送"), this);
    resetLoopSendButton = new QPushButton(tr("重置计数"), this);
    currentSendCountLineEdit = new QLineEdit(this);
    currentSendCountLineEdit->setText("0");
    currentSendCountLineEdit->setMaximumWidth(30);
    currentSendCountLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    auto currentSendCountLabel = new QLabel(tr("计数"), this);
    currentSendCountLabel->setBuddy(currentSendCountLineEdit);
    auto divideLabel = new QLabel(tr("/"), this);
    totalSendCountLabel = new QLabel(tr("0"), this);

    auto loopLayout1 = new QHBoxLayout;
    loopLayout1->addWidget(loopSendCheckBox);
    loopLayout1->addWidget(resetLoopSendButton);

    auto sendCountLayout = new QHBoxLayout;
    sendCountLayout->setAlignment(Qt::AlignLeft);
    sendCountLayout->addWidget(currentSendCountLabel);
    sendCountLayout->addWidget(currentSendCountLineEdit);
    sendCountLayout->addWidget(divideLabel);
    sendCountLayout->addWidget(totalSendCountLabel);

    auto loopSendLayout = new QVBoxLayout;
    loopSendLayout->addLayout(loopLayout1);
    loopSendLayout->addLayout(sendCountLayout);
    auto loopSendGroupBox = new QGroupBox(tr("循环发送设置"), this);
    loopSendGroupBox->setLayout(loopSendLayout);

    saveSentDataButton = new QPushButton(tr("保存数据"), this);
    clearSentDataButton = new QPushButton(tr("清除显示"), this);

    auto sendSettingLayout = new QGridLayout;
    sendSettingLayout->addWidget(sendHexCheckBox, 0, 0, 1, 2);
    sendSettingLayout->addWidget(displaySendDataCheckBox, 1, 0);
    sendSettingLayout->addWidget(displaySendDataAsHexCheckBox, 1, 1);
    sendSettingLayout->addWidget(saveSentDataButton, 2, 0);
    sendSettingLayout->addWidget(clearSentDataButton, 2, 1);

    auto sendSettingGroupBox = new QGroupBox(tr("发送设置"));
    sendSettingGroupBox->setLayout(sendSettingLayout);

    frameInfoSettingButton = new QPushButton(tr("设置数据帧信息"), this);
    sendFrameButton = new QPushButton(tr("发送下一帧"), this);

    auto frameLayout = new QVBoxLayout;
    frameLayout->addWidget(frameInfoSettingButton);
    frameLayout->addWidget(sendFrameButton);


    auto frameGroupBox = new QGroupBox(tr("按帧发送"));
    frameGroupBox->setLayout(frameLayout);

    auto lineGroupBox = new QGroupBox(tr("按行发送"));
    sendLineButton = new QPushButton(tr("发送下一行"));
    auto lineLayout = new QVBoxLayout;
    lineLayout->addWidget(sendLineButton);
    lineGroupBox->setLayout(lineLayout);

    auto fixBytesGroupBox = new QGroupBox(tr("按固定字节发送"));

    auto byteCountLabel = new QLabel(tr("每次发送字节数"), this);
    byteCountLineEdit = new QLineEdit(this);
    byteCountLineEdit->setMaximumWidth(50);
    byteCountLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    byteCountLabel->setBuddy(byteCountLineEdit);

    auto byteCountLayout = new QHBoxLayout;
    byteCountLayout->addWidget(byteCountLabel);
    byteCountLayout->addWidget(byteCountLineEdit);

    sendFixBytesButton = new QPushButton(tr("发送下一帧"), this);

    auto sendBytByteCountLayout = new QVBoxLayout;
    sendBytByteCountLayout->addLayout(byteCountLayout);
    sendBytByteCountLayout->addWidget(sendFixBytesButton);
    fixBytesGroupBox->setLayout(sendBytByteCountLayout);

    auto optionSendLayout = new QVBoxLayout;
    optionSendLayout->addWidget(frameGroupBox);
    optionSendLayout->addWidget(lineGroupBox);
    optionSendLayout->addWidget(fixBytesGroupBox);

    optionSendLayout->setSizeConstraint(QLayout::SetFixedSize);

    sendDataBrowser = new QTextBrowser(this);
    sendDataBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto sendDataLayout = new QVBoxLayout;
    sendDataLayout->addWidget(sendDataBrowser);
    auto sendDataGroupBox = new QGroupBox(tr("数据发送显示"));
    sendDataGroupBox->setLayout(sendDataLayout);
    sendDataGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto dataBrowserSplitter = new QSplitter(this);
    dataBrowserSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dataBrowserSplitter->addWidget(receiveDataGroupBox);
    dataBrowserSplitter->addWidget(sendDataGroupBox);

    sendTextEdit = new QTextEdit(this);
    sendTextEdit->setMinimumHeight(100);
    sendTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);


    sendAllButton = new QPushButton(tr("全部发送"));

    auto sendButtonLayout = new QVBoxLayout;
    sendButtonLayout->setAlignment(Qt::AlignBottom);
    sendButtonLayout->addWidget(sendAllButton);

    sendButtonLayout->setSizeConstraint(QLayout::SetFixedSize);

    auto sendLayout = new QHBoxLayout;
    sendLayout->addLayout(optionSendLayout);
    sendLayout->addWidget(sendTextEdit);
    sendLayout->addLayout(sendButtonLayout);

    sendLayout->setSizeConstraint(QLayout::SetFixedSize);

    auto mainVBoxLayout1 = new QVBoxLayout;
    mainVBoxLayout1->setSizeConstraint(QLayout::SetFixedSize);
    mainVBoxLayout1->addWidget(readWriterButtonGroupBox);
    mainVBoxLayout1->addWidget(serialTabWidget);
    mainVBoxLayout1->addWidget(tcpGroupBox);
    mainVBoxLayout1->addLayout(serialOpenRefreshLayout);
    mainVBoxLayout1->addWidget(receiveSettingGroupBox);
    mainVBoxLayout1->addWidget(sendSettingGroupBox);
    mainVBoxLayout1->addWidget(autoSendGroupBox);
    mainVBoxLayout1->addWidget(loopSendGroupBox);
    mainVBoxLayout1->addStretch();

    auto mainVBoxLayout2 = new QVBoxLayout;
    mainVBoxLayout2->addWidget(dataBrowserSplitter);
    mainVBoxLayout2->addLayout(sendLayout);

    auto widget = new QWidget(this);

    auto mainLayout = new QHBoxLayout;

    mainLayout->addLayout(mainVBoxLayout1);
    mainLayout->addLayout(mainVBoxLayout2);

    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}
