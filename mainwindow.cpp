#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ftd2xx.h"

#include "QTime"
#include "QDebug"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Scan_pb,SIGNAL(clicked()),this,SLOT(ftdi_scan()));
    connect(ui->Connect_pb,SIGNAL(clicked()),this,SLOT(mpsse_setup()));

    ui->Devices_t->setRowCount(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mpsse_setup()
{
    if(device_num == -1)
    {
        QMessageBox msgBox;
        msgBox.setText("Please select device from table first!");
        msgBox.exec();
    }
    else
    {
        ftStatus = FT_Open(device_num, &ftHandle);
        if (ftStatus != FT_OK)
        {
            qDebug()<<"Can't open FT2232H device! \n";
        }
        else
            qDebug()<<"Successfully open FT2232H device! \n";

        DWORD dwCount;

        ftStatus = FT_ResetDevice(ftHandle); //Reset USB device
                                             //Purge USB receive buffer first by reading out all old data from FT2232Hreceive buffer
        ftStatus |= FT_GetQueueStatus(ftHandle, &dwNumInputBuffer); // Get the  number of bytes in the FT2232H receive buffer
        if ((ftStatus == FT_OK) && (dwNumInputBuffer > 0))
            ftStatus |= FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead); //Read out the data from FT2232H receive buffer

        ftStatus |= FT_SetUSBParameters(ftHandle, 65535, 65535); //Set USB  request transfer size
        ftStatus |= FT_SetChars(ftHandle, false, 0, false, 0); //Disable    event and error characters
        ftStatus |= FT_SetTimeouts(ftHandle, 3000, 3000); //Sets the    read and write timeouts in 3 sec for the FT2232H
        ftStatus |= FT_SetLatencyTimer(ftHandle, 1); //Set the latency  timer
        ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x00); //Reset controller
        ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x02); //Enable MPSSE mode

        if (ftStatus != FT_OK)
        {
            qDebug()<<"fail on initialize FT2232H device ! \n";
        }

        Sleep(50); // Wait 50ms for all the USB stuff to complete and work
                   //////////////////////////////////////////////////////////////////
                   // Synchronize the MPSSE interface by sending bad commandn xAA
                   //////////////////////////////////////////////////////////////////

        dwNumBytesToSend = 0;
        OutputBuffer[dwNumBytesToSend++] = '\xAA'; //Add BAD command ＆    xAA＊
        ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent); // Send off the BAD commands
        dwNumBytesToSend = 0; //Clear output buffer

        do {
            ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer); // Get   the number of bytes in the device input buffer
        } while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK)); //or Timeout

        bool bCommandEchod = false;
        ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead); //Read out the data from input buffer
        for (dwCount = 0; dwCount < (dwNumBytesRead - 1); dwCount++) //Checkif Bad command and echo command received
        {
            if ((InputBuffer[dwCount] == BYTE('\xFA')) && (InputBuffer[dwCount + 1] == BYTE('\xAA')))
            {
                bCommandEchod = true;
                break;
            }
        }

        if (bCommandEchod == false)
        {
            qDebug()<<"fail to synchronize MPSSE with command '0xAA' \n";
        }
        //////////////////////////////////////////////////////////////////
        // Synchronize the MPSSE interface by sending bad command ＆xAB＊
        //////////////////////////////////////////////////////////////////
        //dwNumBytesToSend = 0; //Clear output buffer
        OutputBuffer[dwNumBytesToSend++] = '\xAB'; //Send BAD command ＆xAB＊
        ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent); // Send off the BAD commands
        dwNumBytesToSend = 0; //Clear output buffer

        do {
            ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer); //Getthe number of bytes in the device input buffer
        } while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK)); //or Timeout

        bCommandEchod = false;
        ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead); //Read out the data from input buffer
        for (dwCount = 0; dwCount < (dwNumBytesRead - 1); dwCount++) //Check if Bad                 command and echo command received
        {
            if ((InputBuffer[dwCount] == BYTE('\xFA')) && (InputBuffer[dwCount + 1] == BYTE('\xAB')))
            {
                bCommandEchod = true;
                break;
            }
        }
        if (bCommandEchod == false)
        {
            qDebug()<<"fail to synchronize MPSSE with command '0xAB' \n";
            /*Error, can't receive echo command , fail to synchronize MPSSE
            interface;*/
        }
    }
}

void MainWindow::Sleep(uint32_t ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::ftdi_scan()
{
    DWORD numDevs;

    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    if (ftStatus == FT_OK)
        qDebug()<<"Number of devices is %d\n"<<numDevs;

    if (numDevs > 0)
    {
        // get the device information list
        ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);

        if (ftStatus == FT_OK)
        {
            uint8_t i;

            for (i = 0; i < numDevs; i++)
            {
                uint8_t col = 0;

                ui->Devices_t->setRowCount(ui->Devices_t->rowCount()+1);

                qDebug()<<"Dev %d:\n" << i;
                qDebug()<<" Flags=0x%x\n" << devInfo[i].Flags;
                qDebug()<<" Type=0x%x\n" << devInfo[i].Type;
                qDebug()<<" ID=0x%x\n"<< devInfo[i].ID;
                qDebug()<<" LocId=0x%x\n" <<  devInfo[i].LocId;
                qDebug()<<" SerialNumber=%s\n" << devInfo[i].SerialNumber;
                qDebug()<<" Description=%s\n" << devInfo[i].Description;
                qDebug()<<" ftHandle=0x%x\n" << devInfo[i].ftHandle;

                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(QString::number(i)));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(QString::number(devInfo[i].Flags)));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(QString::number(devInfo[i].Type)));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(QString::number(devInfo[i].ID)));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(QString::number(devInfo[i].LocId)));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(devInfo[i].SerialNumber));
                ui->Devices_t->setItem(i, col++,new QTableWidgetItem(devInfo[i].Description));

            }
        }
    }
}

void MainWindow::on_Devices_t_itemClicked(QTableWidgetItem *item)
{
    qDebug()<<"connect to:"<<item->row();
    device_num = item->row();
}
