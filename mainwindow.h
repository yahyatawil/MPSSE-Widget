#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ftd2xx.h"
#include "QTableWidget"
#include "QRadioButton"
#include "QTimer"

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
    QTimer* gpio_timer;
    uint8_t device_num = -1 ;

    struct {
        uint8_t h0 = -1 ;
        uint8_t h1 = -1 ;
        uint8_t h2 = -1 ;
        uint8_t h3 = -1 ;
        uint8_t h4 = -1 ;
        uint8_t h5 = -1 ;
        uint8_t h6 = -1 ;
        uint8_t h7 = -1 ;
    } gpioh_mode;

    struct{
        uint8_t l0 = -1 ;
        uint8_t NU1=  1 ; // wait input
        uint8_t l2 = -1 ;
        uint8_t l3 = -1 ;
        uint8_t NU4=  0 ; //cs output
        uint8_t NU5 = 0 ; //clk output
        uint8_t NU6 = 1 ; //DI input
        uint8_t NU7 = 0 ; //DO output
    } gpiol_mode;


    void Sleep(uint32_t delay_ms);

private slots:
    void ftdi_scan();
    void mpsse_setup();
    void on_Devices_t_itemClicked(QTableWidgetItem *item);
    void ftdi_pinMode(uint8_t pin, uint8_t port, uint8_t mode);
    void ftdi_pinOut(uint8_t pin, uint8_t port, uint8_t state);
    void ftdi_gpio_read_handler();

};
#endif // MAINWINDOW_H
