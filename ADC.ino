#include "ADC.h"

AnalogToDigitalConverter ADConv;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
ADConv.voltageReferenceSelections(AVCC_EXTERNAL_CAP_AT_AREF_PIN);
ADConv.muxChannelSel(CH0);
ADConv.adcEnable(SET);
ADConv.adcStart();
ADConv.adcAutoTrigEnable(SET);
ADConv.setAutoTrigSource(FREE_RUN);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ADConv.getAdc(1));

}
