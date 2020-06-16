#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ftd2xx.h"
#include "QTableWidget"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define MemSize 16 //define data quantity you want to send out
#define ListSize 16 //define data quantity you want to send out

const BYTE SPIDATALENGTH = 11;//3 digit command + 8 digit address
const BYTE READ = '\xC0';//110xxxxx
const BYTE WRITE = '\xA0';//101xxxxx
const BYTE WREN = '\x98';//10011xxx
const BYTE ERAL = '\x90';//10010xxx
                         //declare for BAD command
const BYTE AA_ECHO_CMD_1 = '\xAA';
const BYTE AB_ECHO_CMD_2 = '\xAB';
const BYTE BAD_COMMAND_RESPONSE = '\xFA';
//declare for MPSSE command
const BYTE MSB_RISING_EDGE_CLOCK_BYTE_OUT = '\x10';
const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_OUT = '\x11';
const BYTE MSB_RISING_EDGE_CLOCK_BIT_OUT = '\x12';
const BYTE MSB_FALLING_EDGE_CLOCK_BIT_OUT = '\x13';
const BYTE MSB_RISING_EDGE_CLOCK_BYTE_IN = '\x20';
const BYTE MSB_RISING_EDGE_CLOCK_BIT_IN = '\x22';
const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_IN = '\x24';
const BYTE MSB_FALLING_EDGE_CLOCK_BIT_IN = '\x26';

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WORD DataOutBuffer[MemSize];
    WORD DataInBuffer[MemSize];
    FT_STATUS ftStatus; //Status defined in D2XX to indicateoperation result
    FT_HANDLE ftHandle;
    BYTE OutputBuffer[512]; //Buffer to hold MPSSE commands and data to besent to FT2232H
    BYTE InputBuffer[512]; //Buffer to hold Data bytes to be read fromFT2232H
    DWORD dwClockDivisor = 29; //Value of clock divisor, SCL Frequency =60 / ((1 + 29) * 2) (MHz) = 1Mhz
    DWORD dwNumBytesToSend = 0; //Index of output buffer
    DWORD dwNumBytesSent = 0, dwNumBytesRead = 0, dwNumInputBuffer = 0;
    FT_DEVICE_LIST_INFO_NODE devInfo[ListSize];

    uint8_t device_num = -1 ;

    void Sleep(uint32_t delay_ms);

private slots:
    void ftdi_scan();
    void mpsse_setup();
    void on_Devices_t_itemClicked(QTableWidgetItem *item);
};
#endif // MAINWINDOW_H
