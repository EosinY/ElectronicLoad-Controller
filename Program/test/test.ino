
// Debug Mode Switch
#define DEBUG
// Microcomputer Configuration
const int ADResolution = (2 << (10 - 1)) - 1;
const int DAResolution = (2 << (8 - 1)) - 1;
// Device Configuration
const float MaxAmp = 10.0; // [A]
const float Vthr = 3.0;    // [V]
// Pin Settings
// -Input-
const int Reference = A0;
const int Shunt = A1;
// -Output-
const int SigOut = 10;
const int DbgOut = 9;
// Control Begining Threashold [%]
const float CtrlThrsld = 10.0;
// PID Control Constant
const float KP = 0.0;
const float KI = 0.0;
const float KD = 0.0;
const int T = 0.0;

float GetCurrentAmpere(int *percent);
float GetCurrentReferenceAmpere(int *percent);
void SetOutAmpere(int percent);

void setup()
{
  pinMode(Reference, INPUT);
  pinMode(Shunt, INPUT);
  pinMode(SigOut, OUTPUT);
  TCCR1B &= 0xF8; // PWM freq 490.2 -> 31.25k (Pin: 9,10)
  TCCR1B |= 0x01;
#ifdef DEBUG
  pinMode(DbgOut, OUTPUT);
  Serial.begin(9600);
#endif
}

void loop()
{
  int refPct, crrPct;
  float ref = GetCurrentReferenceAmpere(&refPct);
  float crr = GetCurrentAmpere(&crrPct);
  float err = abs((ref - crr));
  float errPct = (err / ref) * 100.0;
#ifdef DEBUG
  // Serial.print("Reference > ");
  // Serial.print(ref);
  // Serial.print("  Current > ");
  // Serial.print(crr);
  // Serial.println();
  // Serial.print("Absolute Error > ");
  // Serial.print(err);
  // Serial.print("  Error Percent > ");
  // Serial.print(errPct);
  // Serial.println();
#endif
  if (errPct > CtrlThrsld)
  {
    // PID loop
#ifdef DEBUG
    // Serial.println("In control");
#endif
  }
  else
  {
#ifdef DEBUG
    // Serial.println("Not in control");
#endif
  }
  SetOutAmpere(refPct);
  delay(2);
}

float GetCurrentAmpere(int *percent)
{
  int sht = analogRead(Shunt);
  int pct = map(sht, 0, 1023, 0, 100);
  *percent = pct;
  return MaxAmp * ((float)pct / 100.0);
}

float GetCurrentReferenceAmpere(int *percent)
{
  int ref = analogRead(Reference);
  int pct = map(ref, 0, 1023, 0, 100);
  *percent = pct;
  return MaxAmp * ((float)pct / 100.0);
}

void SetOutAmpere(int percent)
{
  int min = (int)((float)DAResolution * (Vthr / 5.0));
  int val = map(percent, 0, 100, min, DAResolution);
  Serial.println(val);
  analogWrite(SigOut, val);
  analogWrite(DbgOut, val);
}

// const int analogInPin = A0; // ポテンショメータに接続するアナログ入力ピン
//
// const int analogOutPin = 3; // LEDに接続するアナログ出力ピン
//
// int sensorValue = 0;        // ポテンショメータから読み取った値
// int outputValue = 0;        // アナログ出力でＰＷＭ出力する値
//
// void setup() {
//   // シリアル通信を初期化する。ボーレートは9600bps
//   Serial.begin(9600);
// }
//
// void loop() {
//   // アナログ入力の値を読む
//   sensorValue = analogRead(analogInPin);
//   // アナログ入力の0～1024の値を、アナログ出力の使用範囲0～255に変換する
//   outputValue = map(sensorValue, 0, 1023, 0, 255);
//   // アナログ出力値を変更する
//   analogWrite(analogOutPin, outputValue);
//
//   // シリアルモニターに結果をプリントする
//   Serial.print("sensor = ");
//   Serial.print(sensorValue);
//   Serial.print("\t output = ");
//   Serial.println(outputValue);
//
//   // アナログ->デジタル変換のために2ミリ秒のウェイトが必要
//   delay(2);
// }
