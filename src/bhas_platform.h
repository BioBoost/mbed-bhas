#if defined(DEVICE_CAN) || defined(TARGET_NUCLEO_L476RG) || defined(TARGET_LPC1768)
#define PLATFORM_MBED
#endif

#if defined(CONFIG_SOC_TWAI_SUPPORTED)
#define PLATFORM_ESP
#endif

// CAN WE DETECT THIS ?????
#define PLATFORM_MBED

#if !defined(PLATFORM_MBED) && !defined(PLATFORM_ESP)
#warning "Could not detect the correct platform to compile for"
#endif