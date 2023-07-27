#include "internal_temperature.h"

namespace BHAS::Sensors {

  InternalTemperature::InternalTemperature()
    : _internalTemperature(ADC_TEMP), _vrefInt(ADC_VREF) {

  }

  int8_t InternalTemperature::temperature() {
    int adcValue = _vrefInt.read_u16() >> 4;
    int voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adcValue, LL_ADC_RESOLUTION_12B);

    int adcTemperature = _internalTemperature.read_u16() >> 4;
    return __LL_ADC_CALC_TEMPERATURE(voltage, adcTemperature, LL_ADC_RESOLUTION_12B);
  }

};
