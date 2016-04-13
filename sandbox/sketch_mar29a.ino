


void serial1_enable_TX_tristate(bool bEnable)
{
    if (bEnable) CORE_PIN1_CONFIG = PORT_PCR_DSE | PORT_PCR_ODE | PORT_PCR_MUX(3); // set Open Drain Enabled
    else         CORE_PIN1_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); // set Slew Rate Enabled
}

void serial2_enable_TX_tristate(bool bEnable)
{
    if (bEnable) CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_ODE | PORT_PCR_MUX(3); // set Open Drain Enabled
    else         CORE_PIN10_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); // set Slew Rate Enabled
}

void serial3_enable_TX_tristate(bool bEnable)
{
    if (bEnable) CORE_PIN8_CONFIG = PORT_PCR_DSE | PORT_PCR_ODE | PORT_PCR_MUX(3); // set Open Drain Enabled
    else         CORE_PIN8_CONFIG = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3); // set Slew Rate Enabled
}

// Open Serial1 at 1 mega baud and in tristate mode
void Dynamixel_Serial1_Open()
{
    Serial1.begin(1000000, SERIAL_8N1);
    e
    serial1_enable_TX_tristate(true);
}

// Send the instruction packet to the Dynamixel servo and then switch the TX pin back to tristate
void Dynamixel_Serial1_Write(byte* data, int count)
{
    serial1_enable_TX_tristate(false);            

    for (int i=0; i<count; i++)
    { 
        Serial1.write(data[i]);
    }

    Serial1.flush(); // waits until the last data byte has been sent
    serial1_enable_TX_tristate(true);            
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    byte data[] = { 0x00 };
    Dynamixel_Serial1_Write(data, 1);
    delay(1);
}
