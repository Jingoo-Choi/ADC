#ifndef _ADC_H_
#define _ADC_H_

#include <Arduino.h>
//ARDUINO UNO 전용 (ATMEGA328p)

typedef enum { VREF_TURN_OFF, AVCC_EXTERNAL_CAP_AT_AREF_PIN, RESERVED, INTERNAL_1_1V } VoltRefSelForADC;
//#define VREF_TURN_OFF	0b00000000;
//#define AVCC_EXTERNAL_CAP_AT_AREF_PIN	0b01000000;
////#define RESERVED	0b10000000;
//#define INTERNAL_1_1V	0b11000000;

typedef enum { CH0, CH1, CH2, CH3, CH4, CH5 }MuxChannel;
typedef enum { DIV_F_2, DIV_F_4, DIV_F_8, DIV_F_16, DIV_F_32, DIV_F_64, DIV_F_128 } DivisionFactor;
typedef enum { FREE_RUN, ANAL_COMP, EXT_INT_REQ0, TC0_COMP_A, TC0_OVF, TC1_COMP_B, TC1_OVF, TC1_CAP } AutoTrigSource;

#define SET 1
#define UNSET 0

#define WAIT_MUX_SET 1000

class AnalogToDigitalConverter {
public:
	//AnalogToDigitalConverter();
	//~AnalogToDigitalConverter(); //소멸자가 필요한가?
	
	void init();
	//ADMUX register options
	void voltageReferenceSelections(VoltRefSelForADC voltage); // select에쓰는 단어는?
	void leftAdjustResult(bool set); // on off 에 좋은 이름은?
	void muxChannelSel(MuxChannel channel);

	//ADCSRA Reg options
	void adcEnable(bool enable); // on_off
	void adcStart();
	void adcAutoTrigEnable(bool enable);

	void adcInterruptFlag(bool enable);
	void adcInterruptEnable(bool enable);
	void setAdcPrescalerSel(DivisionFactor factor);

	//ADCSRB
	void setAutoTrigSource(AutoTrigSource source);

	//DIDR0
	void digitalInputDisable(MuxChannel channel);

	uint16_t getAdc(MuxChannel channel);

	void waitCount(uint32_t count);
};


#endif