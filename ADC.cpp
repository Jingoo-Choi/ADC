#include "ADC.h"

void AnalogToDigitalConverter::init() {
	ADMUX = 0;
	ADCSRA = 0;
	ADCSRB = 0;
	DIDR0 = 0;
}

void AnalogToDigitalConverter::voltageReferenceSelections(VoltRefSelForADC voltage) {
	uint8_t reg = 0;
	reg = voltage << 6;
	ADMUX |= reg;
}// select에쓰는 단어는?

void AnalogToDigitalConverter::leftAdjustResult(bool set) {
	uint8_t reg = 0;
	reg = set << 5;
	ADMUX |= reg;
} // on off 에 좋은 이름은?
void AnalogToDigitalConverter::muxChannelSel(MuxChannel channel) {
	uint8_t reg = 0;
	reg = channel;
	ADMUX |= reg;	
}

//ADCSRA Reg options
void AnalogToDigitalConverter::adcEnable(bool enable) {
	uint8_t reg = 0;
	reg = enable << 7;
	ADCSRA |= reg;
} // on_off
void AnalogToDigitalConverter::adcStart() {
	uint8_t reg = 1;
	reg = reg << 6;
	ADCSRA |= reg;
} 
void AnalogToDigitalConverter::adcAutoTrigEnable(bool enable) {
	uint8_t reg = 1;
	reg = enable << 5;
	ADCSRA |= reg;
}

void AnalogToDigitalConverter::adcInterruptFlag(bool enable) {
	uint8_t reg = 1;
	reg = enable << 4;
	ADCSRA |= reg;
}
void AnalogToDigitalConverter::adcInterruptEnable(bool enable) {
	uint8_t reg = 1;
	reg = enable << 3;
	ADCSRA |= reg;
}
void AnalogToDigitalConverter::setAdcPrescalerSel(DivisionFactor factor) {
	uint8_t reg = factor;
	ADCSRA |= reg;
}

//ADCSRB
void AnalogToDigitalConverter::setAutoTrigSource(AutoTrigSource source) {
	uint8_t reg = source;
	ADCSRB |= reg;
}

//DIDR0
void AnalogToDigitalConverter::digitalInputDisable(MuxChannel channel) {
	uint8_t reg = channel;
	DIDR0 |= reg;
}

uint16_t AnalogToDigitalConverter::getAdc(MuxChannel channel) {
	uint8_t low_value = 0;
	uint8_t high_value = 0;
	uint16_t ret_value = 0;

	muxChannelSel(channel);
	waitCount(WAIT_MUX_SET);

	low_value = ADCL;
	high_value = ADCH;

	ret_value = (high_value << 8) | low_value;

	return ret_value;
}

void AnalogToDigitalConverter::waitCount(uint32_t count) {
	volatile uint32_t i = 0;
	for (i = 0; i < count; i++);
}