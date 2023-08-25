void setup() 
{
  Serial1.setTX(28);
  Serial1.setRX(29);
  Serial1.begin(9600);
  for (int i=0; i<10; i++) {
    Serial1.println(i);
    delay(1);
  }
  Serial1.println("Demo - Gamepad");

  TinyUSB_Device_Init(0);
  usb_hid.begin();
  // wait until device mounted
  while( !TinyUSBDevice.mounted() ) 
  {
    Serial1.print(".");
    delay(1);
  };
  Serial1.println("");
  Serial1.println("Device connected");    
  while (true); 
}

void loop() {}