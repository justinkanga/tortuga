

#define I2C_TIMEOUT 100000

byte AckI2C(void)
{
    I2CCONbits.ACKDT = 0;          //Set for ACk
    I2CCONbits.ACKEN = 1;

    long timeout = 0;
    while(I2CCONbits.ACKEN)
        if(timeout++ == I2C_TIMEOUT)
            return 255;
    return 0;
}


unsigned int initI2C(void)
{
    //This function will initialize the I2C(1) peripheral.
    //First set the I2C(1) BRG Baud Rate.

    TRISFbits.TRISF2 = 1;
    TRISFbits.TRISF3 = 1;

    /* Turn i2c off */
    I2CCONbits.I2CEN = 0;

    //Consult the dSPIC Data Sheet for information on how to calculate the
    //Baud Rate.

   // I2CBRG = 0x004f;
    I2CBRG = 0x054f;

    //Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
    //Control, and leave the peripheral switched off.

    I2CCON = 0x1200;

    I2CRCV = 0x0000;
    I2CTRN = 0x0000;
    //Now we can enable the peripheral

    I2CCON = 0x9200;
    return 0;
}

unsigned int getI2C(void)
{
    I2CCONbits.RCEN = 1;           //Enable Master receive
    Nop();

    long timeout = 0;
    while(!I2CSTATbits.RBF)
    {
        if(timeout++ == I2C_TIMEOUT)
            return 255;
    }
    return(I2CRCV);                //Return data in buffer
}


byte StartI2C(void)
{
    //This function generates an I2C start condition and returns status
    //of the Start.
    long timeout=0;
    I2CCONbits.SEN = 1;        //Generate Start COndition
    while(I2CCONbits.SEN)
        if(timeout++ == I2C_TIMEOUT)
            return 255;

    return 0;

    //return(I2C1STATbits.S);   //Optionally return status
}

unsigned int RestartI2C(void)
{
    //This function generates an I2C Restart condition and returns status
    //of the Restart.
    long timeout=0;
    I2CCONbits.RSEN = 1;       //Generate Restart

    while(I2CCONbits.RSEN)
        if(timeout++ == I2C_TIMEOUT)
            return 255;

    return 0;

    //return(I2C1STATbits.S);   //Optional - return status
}

unsigned int StopI2C(void)
{
    //This function generates an I2C stop condition and returns status
    //of the Stop.

    I2CCONbits.PEN = 1;        //Generate Stop Condition
    long timeout=0;
    while(I2CCONbits.PEN)
        if(timeout++ == I2C_TIMEOUT)
            return 255;
    return 0;

    //return(I2C1STATbits.P);   //Optional - return status
}

unsigned int WriteI2C(unsigned char b)
{
    //This function transmits the byte passed to the function
    //while (I2C1STATbits.TRSTAT);  //Wait for bus to be idle
    I2CTRN = b;                 //Load byte to I2C1 Transmit buffer
    long timeout=0;
    while(I2CSTATbits.TBF)
        if(timeout++ == I2C_TIMEOUT)
            return 255;
    return 0;
}

unsigned int IdleI2C(void)
{
    long timeout=0;
    while(I2CSTATbits.TRSTAT)
    {
        if(timeout++ == I2C_TIMEOUT)
        {
            return 255;
        }
    }
    return 0;
}

unsigned int getsI2C(unsigned char *rdptr, unsigned char Length)
{
    while (Length --)
    {
        *rdptr++ = getI2C();        //get a single byte

        if(I2CSTATbits.BCL)        //Test for Bus collision
        {
            return(-1);
        }

        if(Length)
        {
            AckI2C();               //Acknowledge until all read
        }
    }
    return(0);
}

long readTemp(byte addr)
{
    long temp=0;
    byte rb[2];
    // 1001111

    IdleI2C();                  //wait for bus Idle
    StartI2C();                 //Generate Start condition
    WriteI2C(addr | 0x01);   //Write 1 byte - R/W bit should be 1 for read
    IdleI2C();                  //wait for bus Idle
    getsI2C(rb, 2);

    temp = rb[0]; // * 10 + (1 * rb[1])/16;;

    AckI2C();
    StopI2C();
    return temp;
}

//Kanga - Write address and color code
//reference at http://www.ti.com/lit/ds/slds157d/slds157d.pdf
void setLEDBars(byte addr, byte code){
    byte blink = code >> 3;
    byte red = (code & 0x04) >> 2;
    byte green = (code & 0x02) >> 1;
    byte blue = code & 0x01;

    int x = 0;
    IdleI2C();                  //wait for bus Idle
    StartI2C();                 //Generate Start condition
    
    WriteI2C(addr | 0x01); //Select slave for write
    IdleI2C();

    WriteI2C(0x81); //Auto-increment on all registers starting at 0x01 (Mode2)
    IdleI2C();

    blink ? WriteI2C(0x20): WriteI2C(0x00); //set DMBLNK to 1 (on) or 0 (off)
    IdleI2C();
    
    for(int i=2; i<=17; i++)
    {
        x = i % 3;
        ((red && x==2) || (green && x==0) || (blue && x==1)) ? WriteI2C(0xFF) : WriteI2C(0x00); //turn appropriate colors on/off
        IdleI2C();
    }
    StopI2C();
}

void initLEDBars(){
    IdleI2C();
    StartI2C();
    WriteI2C(0xD1);//led allcall write
    IdleI2C();
    WriteI2C(0x01);//write to Mode1 register
    IdleI2C();
    WriteI2C(0x01);//turn on oscillator
    IdleI2C();
    StopI2C();

    IdleI2C();
    StartI2C();
    WriteI2C(0xD1);//led allcall write
    IdleI2C();
    WriteI2C(0x04);//Write to global blink frequency
    IdleI2C();
    WriteI2C(0x0B);//11+1/24 = 0.5 second blink period
    IdleI2C();
    StopI2C();
}