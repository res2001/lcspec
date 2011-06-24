/*
 * lcspec.h
 *  Файл определяет набор макросов, специфичных для компилятора:
        упаковка стркутур
        выравние переменных
        inline-функции
 *  Created on: 10.01.2011
 *      Author: Melkor
 */

#ifndef LCSPEC_H_
#define LCSPEC_H_

#if defined   (  __GNUC__  )
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED     __attribute__ ((packed))
    //#define LPRAGMA_PACKED   pack(1)
    //#define LPRAGMA_PACK_RESTORE  pack()
	//#define LPRAGMA_ALIGN(n) align(n)
	#define LATTRIBUTE_ALIGN(n) __attribute__ ((aligned (n)))
#elif defined ( __CC_ARM   )
	#error "cc arm compiler spec. is't defined"
#elif defined ( __ICCARM__ )
	#error "iar compiler spec. is't defined"                                /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */
#elif defined   (  __TASKING__  )
 	#error "tasking compiler spec. is't defined"
#else
	#error "compiler is't specifed"

    #define LINLINE
    #define LATTRIBUTE_PACKED
    //#define LPRAGMA_PACKED   pack(1)
    //#define LPRAGMA_PACK_RESTORE  pack()
    //#define LPRAGMA_ALIGN(n)
    #define LATTRIBUTE_ALIGN(n)
#endif


#endif /* LCSPEC_H_ */
