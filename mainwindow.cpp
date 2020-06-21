#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ftd2xx.h"

#include "QTime"
#include "QDebug"
#include "QTimer"
#include <QMessageBox>
#include <Qfile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //open and set style sheet
    QFile f(":/style.qss" );
    if( f.open( QFile::ReadOnly ) )
    {
    QString ssheet = QLatin1String( f.readAll() );
    this->setStyleSheet( ssheet );
    }

    gpio_timer = new QTimer(this);
    connect(gpio_timer, SIGNAL(timeout()), this, SLOT(ftdi_gpio_read_handler()));

    connect(ui->Scan_pb,SIGNAL(clicked()),this,SLOT(ftdi_scan()));
    connect(ui->Connect_pb,SIGNAL(clicked()),this,SLOT(mpsse_setup()));

    connect(ui->Output_set_gpioh0_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh0_pb->setChecked(1);
        ftdi_pinMode(0,1,0); // pin:0 port:high:1 Mode:0 Output
        //ui->state_gpioh0_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh1_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh1_pb->setChecked(1);
        ftdi_pinMode(1,1,0); // pin:1 port:high:1 Mode:0 Output
        //ui->state_gpioh1_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh2_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh2_pb->setChecked(1);
        ftdi_pinMode(2,1,0); // pin:2 port:high:1 Mode:0 Output
        //ui->state_gpioh2_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh3_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh3_pb->setChecked(1);
        ftdi_pinMode(3,1,0); // pin:3 port:high:1 Mode:0 Output
        //ui->state_gpioh3_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh4_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh4_pb->setChecked(1);
        ftdi_pinMode(4,1,0); // pin:4 port:high:1 Mode:0 Output
        //ui->state_gpioh4_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh5_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh5_pb->setChecked(1);
        ftdi_pinMode(5,1,0); // pin:5 port:high:1 Mode:0 Output
        //ui->state_gpioh5_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh6_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh6_pb->setChecked(1);
        ftdi_pinMode(6,1,0); // pin:6 port:high:1 Mode:0 Output
        //ui->state_gpioh6_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpioh7_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpioh7_pb->setChecked(1);
        ftdi_pinMode(7,1,0); // pin:7 port:high:1 Mode:0 Output
        //ui->state_gpioh7_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpiol0_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpiol0_pb->setChecked(1);
        ftdi_pinMode(0,0,0); // pin:0 port:low:0 Mode:0 Output
        //ui->state_gpiol0_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpiol2_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpiol2_pb->setChecked(1);
        ftdi_pinMode(2,0,0); // pin:1 port:low:0 Mode:0 Output
        //ui->state_gpiol2_pb->setCheckable(1);
    });

    connect(ui->Output_set_gpiol3_pb, &QPushButton::clicked, [this]()
    {
        ui->Output_set_gpiol3_pb->setChecked(1);
        ftdi_pinMode(3,0,0); // pin:2 port:low:0 Mode:0 Output
        //ui->state_gpiol3_pb->setCheckable(1);
    });


    connect(ui->Input_set_gpioh0_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh0_pb->setChecked(1);
        ftdi_pinMode(0,1,1); // pin:0 port:high:1 Mode:1 Input
        //ui->state_gpioh0_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh1_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh1_pb->setChecked(1);
        ftdi_pinMode(1,1,1); // pin:1 port:high:1 Mode:1 Input
        //ui->state_gpioh1_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh2_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh2_pb->setChecked(1);
        ftdi_pinMode(2,1,1); // pin:2 port:high:1 Mode:1 Input
        //ui->state_gpioh2_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh3_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh3_pb->setChecked(1);
        ftdi_pinMode(3,1,1); // pin:3 port:high:1 Mode:1 Input
        //ui->state_gpioh3_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh4_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh4_pb->setChecked(1);
        ftdi_pinMode(4,1,1); // pin:4 port:high:1 Mode:1 Input
        //ui->state_gpioh4_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh5_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh5_pb->setChecked(1);
        ftdi_pinMode(5,1,1); // pin:5 port:high:1 Mode:0 Input
        //ui->state_gpioh5_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh6_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh6_pb->setChecked(1);
        ftdi_pinMode(6,1,1); // pin:6 port:high:1 Mode:1 Input
        //ui->state_gpioh6_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpioh7_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpioh7_pb->setChecked(1);
        ftdi_pinMode(7,1,1); // pin:7 port:high:1 Mode:1 Input
        //ui->state_gpioh7_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpiol0_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpiol0_pb->setChecked(1);
        ftdi_pinMode(0,0,1); // pin:0 port:low:0 Mode:1 Input
        //ui->state_gpiol0_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpiol2_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpiol2_pb->setChecked(1);
        ftdi_pinMode(2,0,1); // pin:1 port:low:0 Mode:1 Input
        //ui->state_gpiol2_pb->setCheckable(0);
    });

    connect(ui->Input_set_gpiol3_pb, &QPushButton::clicked, [this]()
    {
        ui->Input_set_gpiol3_pb->setChecked(1);
        ftdi_pinMode(3,0,1); // pin:2 port:low:0 Mode:1 Input
        //ui->state_gpiol3_pb->setCheckable(0);
    });

    //state push button

    connect(ui->state_gpioh0_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(0,1,ui->state_gpioh0_pb->isChecked());
    });

    connect(ui->state_gpioh1_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(1,1,ui->state_gpioh1_pb->isChecked());
    });

    connect(ui->state_gpioh2_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(2,1,ui->state_gpioh2_pb->isChecked());
    });

    connect(ui->state_gpioh3_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(3,1,ui->state_gpioh3_pb->isChecked());
    });

    connect(ui->state_gpioh4_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(4,1,ui->state_gpioh4_pb->isChecked());
    });

    connect(ui->state_gpioh5_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(5,1,ui->state_gpioh5_pb->isChecked());
    });

    connect(ui->state_gpioh6_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(6,1,ui->state_gpioh6_pb->isChecked());
    });

    connect(ui->state_gpioh7_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(7,1,ui->state_gpioh7_pb->isChecked());
    });

    connect(ui->state_gpiol0_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(0,0,ui->state_gpiol0_pb->isChecked());
    });

    connect(ui->state_gpiol2_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(2,0,ui->state_gpiol2_pb->isChecked());
    });

    connect(ui->state_gpiol3_pb, &QPushButton::clicked, [this]()
    {
        ftdi_pinOut(3,0,ui->state_gpiol3_pb->isChecked());
    });



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
        {
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
            else
            {
                ui->InputOutput_widget->setEnabled(1);
                gpio_timer->start(1000);
            }
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

void MainWindow::ftdi_pinMode(uint8_t pin, uint8_t port, uint8_t mode)
{
    uint8_t * ptr;
    static uint8_t input_h_mask ;
    static uint8_t input_l_mask ;
    static uint8_t output_h_mask ;
    static uint8_t output_l_mask ;

    QPushButton * gpio_output_selectors[8];

    uint8_t * input_mask;
    uint8_t * output_mask;

    if(port == 1)
    {
        ptr = (uint8_t *) &gpioh_mode;
        output_mask = &output_h_mask;
        input_mask = &input_h_mask;
        gpio_output_selectors[0]= ui->state_gpioh0_pb;
        gpio_output_selectors[1]= ui->state_gpioh1_pb;
        gpio_output_selectors[2]= ui->state_gpioh2_pb;
        gpio_output_selectors[3]= ui->state_gpioh3_pb;
        gpio_output_selectors[4]= ui->state_gpioh4_pb;
        gpio_output_selectors[5]= ui->state_gpioh5_pb;
        gpio_output_selectors[6]= ui->state_gpioh6_pb;
        gpio_output_selectors[7]= ui->state_gpioh7_pb;


    }
    else if(port == 0)
    {
        ptr = (uint8_t *) &gpiol_mode;
        output_mask = &output_l_mask;
        input_mask = &input_l_mask;

        gpio_output_selectors[0]= ui->state_gpiol0_pb;
        gpio_output_selectors[1]= nullptr;
        gpio_output_selectors[2]= ui->state_gpiol2_pb;
        gpio_output_selectors[3]= ui->state_gpiol3_pb;
        gpio_output_selectors[4]= nullptr;
        gpio_output_selectors[5]= nullptr;
        gpio_output_selectors[6]= nullptr;
        gpio_output_selectors[7]= nullptr;
    }

    ptr[pin] = mode;

/*
    qDebug()<<"gpioh_mode";
    qDebug()<<gpioh_mode.h0;
    qDebug()<<gpioh_mode.h1;
    qDebug()<<gpioh_mode.h2;
    qDebug()<<gpioh_mode.h3;
    qDebug()<<gpioh_mode.h4;
    qDebug()<<gpioh_mode.h5;
    qDebug()<<gpioh_mode.h6;
    qDebug()<<gpioh_mode.h7;

    qDebug()<<"gpiol_mode";
    qDebug()<<gpiol_mode.l0;
    qDebug()<<gpiol_mode.NU1;
    qDebug()<<gpiol_mode.l2;
    qDebug()<<gpiol_mode.l3;
    qDebug()<<gpiol_mode.NU4;
    qDebug()<<gpiol_mode.NU5;
    qDebug()<<gpiol_mode.NU6;
    qDebug()<<gpiol_mode.NU7;
*/

    for(int i=0;i<8;i++)
    {
        if(gpio_output_selectors[i]!=nullptr && gpio_output_selectors[i]->isChecked())
        {
            *output_mask |= 1<<i;
        }
        else *output_mask &= ~(1<<i);

        if(ptr[i]==-1)//not set yet, default: input
        {
            *input_mask = ~(1<<i) ;
        }
        else if(ptr[i]==0) // output
        {
            *input_mask = *input_mask | (1<<i) ;
        }
        else if(ptr[i]==1) // input
        {
            *input_mask = *input_mask & ~(1<<i) ;
        }
    }

    qDebug()<<"input mask:"<<QString("%1").arg(*input_mask,0,16);

    dwNumBytesToSend = 0;
    if(port == 0)
    {
        OutputBuffer[dwNumBytesToSend++] = '\x80';
        OutputBuffer[dwNumBytesToSend++] = (*(output_mask)<<4 &0xF0)|(*(output_mask)>>4 & 0x0F);
        OutputBuffer[dwNumBytesToSend++] = (*(input_mask)<<4 &0xF0)|(*(input_mask)>>4 & 0x0F);
    }
    else if(port == 1)
    {
        OutputBuffer[dwNumBytesToSend++] = '\x82';
        OutputBuffer[dwNumBytesToSend++] = *output_mask & 0xFF;
        OutputBuffer[dwNumBytesToSend++] = *input_mask & 0xFF;
    }

    qDebug()<<QString("%1 %2 %3").arg(OutputBuffer[0],0,16).arg(OutputBuffer[1],0,16).arg(OutputBuffer[2],0,16);
    ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent); // Send off the BAD commands
    dwNumBytesToSend = 0; //Clear output buffer

}

void MainWindow::ftdi_pinOut(uint8_t pin, uint8_t port, uint8_t state)
{
    ftdi_pinMode(pin,port,0);
}

void MainWindow::ftdi_gpio_read_handler()
{
    QPushButton * gpio_output_selectors[8];

    gpio_output_selectors[0]= ui->state_gpiol0_pb;
    gpio_output_selectors[1]= nullptr;
    gpio_output_selectors[2]= ui->state_gpiol2_pb;
    gpio_output_selectors[3]= ui->state_gpiol3_pb;
    gpio_output_selectors[4]= nullptr;
    gpio_output_selectors[5]= nullptr;
    gpio_output_selectors[6]= nullptr;
    gpio_output_selectors[7]= nullptr;

    OutputBuffer[dwNumBytesToSend++] = '\x81';
    ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
    dwNumBytesToSend = 0; //Clear output buffer
    Sleep(10);
    do {
        ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);
    } while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK)); //or Timeout

    ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead); //Read out the data from input buffer
    for (uint8_t i = 0; i < dwNumBytesRead ; i++)
    {
        qDebug()<<"L"<<QString("l-%1").arg(InputBuffer[i],0,16) ;
    }

    for(int pin=0;pin<4;pin++)
    {
        if(pin == 1) continue;

        if(InputBuffer[0] & ((BYTE)(1<<(4+pin))))
        {
            gpio_output_selectors[pin]->setChecked(1);
        }
        else
        {
            gpio_output_selectors[pin]->setChecked(0);
        }
    }

    gpio_output_selectors[0]= ui->state_gpioh0_pb;
    gpio_output_selectors[1]= ui->state_gpioh1_pb;
    gpio_output_selectors[2]= ui->state_gpioh2_pb;
    gpio_output_selectors[3]= ui->state_gpioh3_pb;
    gpio_output_selectors[4]= ui->state_gpioh4_pb;
    gpio_output_selectors[5]= ui->state_gpioh5_pb;
    gpio_output_selectors[6]= ui->state_gpioh6_pb;
    gpio_output_selectors[7]= ui->state_gpioh7_pb;

    OutputBuffer[dwNumBytesToSend++] = '\x83';
    ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
    dwNumBytesToSend = 0; //Clear output buffer
    Sleep(10);
    do {
        ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);
    } while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK)); //or Timeout


    ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead); //Read out the data from input buffer
//    for (uint8_t i = 0; i < dwNumBytesRead ; i++)
//    {
//        qDebug()<<"H"<<QString("h-%1").arg(InputBuffer[i],0,16) ;
//    }

    for(int pin=0;pin<8;pin++)
    {
        if(InputBuffer[0] & ((BYTE)(1<<pin)))
        {
            gpio_output_selectors[pin]->setChecked(1);
        }
        else
        {
            gpio_output_selectors[pin]->setChecked(0);
        }
    }
}
