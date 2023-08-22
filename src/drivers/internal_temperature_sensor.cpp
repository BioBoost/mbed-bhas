#include "internal_temperature_sensor.h"

namespace BHAS::Drivers {

#if defined(TARGET_LPC1768)

  InternalTemperature::InternalTemperature() { }
  
  int8_t InternalTemperature::temperature() {
    return 0;
  }

#else

  InternalTemperature::InternalTemperature()
    : _internalTemperature(ADC_TEMP), _vrefInt(ADC_VREF) {

  }

  int8_t InternalTemperature::temperature() {
    int adcValue = _vrefInt.read_u16() >> 4;
    int voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adcValue, LL_ADC_RESOLUTION_12B);

    int adcTemperature = _internalTemperature.read_u16() >> 4;
    return __LL_ADC_CALC_TEMPERATURE(voltage, adcTemperature, LL_ADC_RESOLUTION_12B);
  }

#endif

};
