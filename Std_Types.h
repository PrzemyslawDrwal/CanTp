#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef uint32 uint8_least;
typedef sint32 sint8_least;
typedef uint32 uint16_least;
typedef sint32 sint16_least;
typedef uint32 uint32_least;
typedef sint32 sint32_least;
typedef uint8_least boolean;
typedef float ieee_float;

#define STD_ON (0x01u)
#define STD_OFF (0x00u)
#define E_OK (0x00u)
#define E_NOT_OK (0x01u)
#define TRUE (0x01u)
#define FALSE (0x00u)
#define STD_LOW (0x00u)
#define STD_HIGH (0x01u)
#define NULL_PTR ((void *)0x00u)

typedef uint32 Std_ReturnType;

typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

#endif /* STD_TYPES_H_ */
