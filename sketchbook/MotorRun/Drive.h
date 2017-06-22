class Drive {
    const int Left_CW = 5;
    const int Left_CCW = 6;

    const int Rigth_CCW = 10;
    const int Rigth_CW = 11;

    const int ledPin = 13;
    const byte Right_Comp = 4;
    const byte Left_Comp = 0;
    const byte RightBack_Comp = 0;
    const byte LeftBack_Comp = 15;

    byte holdCommand;
    byte slowSpeed;
    long prevCm;
    int driveRight = 0;
    bool autonomous = false;

  public:
    Drive();
    void driveAutonomous();
    void driveUpdate();
    byte driveStatus();
    void runSpeed(byte );
    byte readSpeed();
    void driveSTOP();
    void driveFWD();
    void driveHold();
    void driveSlow();
    void driveResume();
    void checkValue (byte);

  private:
    byte driveSpeed = 100 ;
    boolean hold = false;
    boolean slow = false;
    byte driveDirection = 'S';  // Start in STOP mode
    byte driveCommand = 'S';  // Start drive command STOP
    void driveBACK();
    void driveRIGHT();
    void driveLEFT();
};

Drive::Drive () {
  driveSpeed = 128;
  pinMode(Left_CW, OUTPUT);
  pinMode(Left_CCW, OUTPUT);
  pinMode(Rigth_CCW, OUTPUT);
  pinMode(Rigth_CW, OUTPUT);
};


void Drive::driveHold () {
  if (hold != true) {
    holdCommand = driveDirection;
    driveDirection = 'S';  // set to stop
    checkValue(driveDirection);
    hold = true;
  }
};

void Drive::driveSlow () {
  if (slow != true) {
    slowSpeed = driveSpeed;
    driveSpeed = 144;  // set to = to "1"
    slow = true;
  }
};

void Drive::driveResume () {
  if (hold == true) { // run this casee only once after a hold
    hold = false;
    slow = false;
    driveDirection = holdCommand;
    checkValue(driveDirection);
  };
};

void Drive::runSpeed (byte amount) {
  driveSpeed = amount;
};

byte Drive::readSpeed () {
  int driveSpeed1 = int(driveSpeed);
  byte outSpeed = (((driveSpeed1 + 1) / 16) + byte('0') - 7);
  return byte(outSpeed);
};


void Drive::driveAutonomous (long cm)
{
  if (autonomous)
  {
    if (cm = < 15)
    {
      if (cm < cmPrev)
      {
        driveRight = false;
      }
      if (driveRight)
      {
        driveDirection = 'R';
      }
      else
      {
        driveDirection = 'L';
      }
    }
    else
    {
      driveRight = 0;
      driveDirection = 'F';
    }
    cmPrev = cm;
  }
};

void Drive::driveUpdate () {
  if (driveDirection == 'F' ) {
    driveFWD();
  }

  if (driveDirection == 'B' ) {
    driveBACK();
  }

  if (driveDirection == 'S' ) {
    driveSTOP();
  }
};
byte Drive::driveStatus () {

  return driveDirection;
};


void Drive::checkValue (byte value) {

  if (hold != true) {
    if (value >= '0' and value <= '9') {
      driveSpeed = ((((value - '0') + 6) * 16) + 15);
      driveUpdate();
    }
    switch (value) {
      case 'x':
      case 'X':
        driveDirection = 'S';
        driveSTOP();
        break;
      case 's':
      case 'S':
      case '0':
        driveDirection = 'S';
        if (autonomous)
        {
          autonomous = false;
        }
        driveSTOP();
        break;
      case 'f':
      case 'F':
        driveDirection = 'F';
        driveFWD();
        break;
      case 'b':
      case 'B':
        driveDirection = 'B';
        driveBACK();
        break;
      case 'r':
      case 'R':
        driveDirection = 'R';
        driveRIGHT();
        break;
      case 'l':
      case 'L':
        driveDirection = 'L';
        driveLEFT();
        break;
      case 'a':
      case 'A':
        autonomous = true;
        driveAutonomous();
        break;
      default:
        break;
    }
  }
};


void Drive::driveFWD () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, driveSpeed - Left_Comp);
  analogWrite(Rigth_CCW, 0);
  analogWrite(Rigth_CW, driveSpeed - Right_Comp);
  driveDirection = 'F';
};

void Drive::driveBACK () {
  analogWrite(Left_CW, driveSpeed - LeftBack_Comp);
  analogWrite(Left_CCW, 0);
  analogWrite(Rigth_CCW, driveSpeed - RightBack_Comp);
  analogWrite(Rigth_CW, 0);
  driveDirection = 'B';
};

void Drive::driveSTOP () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, 0);
  analogWrite(Rigth_CCW, 0);
  analogWrite(Rigth_CW, 0);
  driveDirection = 'S';
};

void Drive::driveRIGHT () {
  analogWrite(Left_CW, 0);
  analogWrite(Left_CCW, driveSpeed / 2);
  analogWrite(Rigth_CCW, driveSpeed / 2);
  analogWrite(Rigth_CW, 0);
  driveDirection = 'R';
};

void Drive::driveLEFT () {
  analogWrite(Left_CW, driveSpeed / 2);
  analogWrite(Left_CCW, 0);
  analogWrite(Rigth_CCW, 0);
  analogWrite(Rigth_CW, driveSpeed / 2);
  driveDirection = 'L';
};

