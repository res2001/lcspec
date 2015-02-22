/***************************************************************************//**
  @file lcspec.h
  Файл вместе с файлами из подкаталога с именем компилятора определяет набор 
      макросов и заголовочных файлов для выполнения действий, которые определяются
      специфичным для компилятора способом:
        - упаковка структур
        - выравнивание переменных
        - определение inline-функций

  Для задания упаковки структур используются два файла lcspec_pack_start.h и 
      lcspec_pack_restore.h для возможности указать упаковку через \#pragma.
      Кроме того используется определение #LATTRIBUTE_PACKED для определения 
      упаковки с помощью атрибутов (как в gcc).
      Упакованная структура должна быть обявлена следующим образом :

    @code
    #include "lcspec_pack_start.h"

    struct struct_name {
        ...
    } LATTRIBUTE_PACKED;
    typedef struct struct_name type_name;

    ...

    #include "lcspec_pack_restore.h"
    @endcode

  Выравнивание на n байт выполняется также через включение файла с предварительным 
	определением границы выравнивания через LSPEC_ALIGNMENT. 
       Ниже объявлены две переменные с выравниванием 128 байт:
    @code
    #define LSPEC_ALIGNMENT 128
    #include "lcspec_align.h"  
    int v1;
    #include "lcspec_align.h"  
    unsigned v2;
    #undef LSPEC_ALIGNMENT
    @endcode
 
  Для встроенных функций определено определение #LINLINE, которое должно быть указано 
  в начале определения функции перед типом возвращаемого значения 
  (после слова static для статической функции) 

  На настоящий момент реализованы определения для GCC, IAR, MSVC, OpenWatcom и LabWindow/CVI.

  @author Borisov Alexey <borisov@lcard.ru>
  @date   10.01.2011
*******************************************************************************/

#ifndef LCSPEC_H_
#define LCSPEC_H_

#if defined   (  __GNUC__  )
    /*------------------------ определения GCC -------------------------------*/
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED     __attribute__ ((packed))
#elif defined ( _MSC_VER )
    /*------------------------ определения MSVC ------------------------------*/
    #define LINLINE                 __inline
    #define LATTRIBUTE_PACKED
    /*------------------------ Watcom/Open Watcom ----------------------------*/
#elif defined ( _WATCOMC_ ) || defined (__WATCOMC__)
    #define LINLINE                 __inline
    #define LATTRIBUTE_PACKED
#elif defined ( _CVI_ )
    /*------------------- определения для LabWindow/CVI ----------------------*/
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED
#elif defined ( __CC_ARM   )
    #error "cc arm compiler spec. is't defined"
#elif defined ( __ICCARM__ )
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED
#elif defined   (  __TASKING__  )
    #error "tasking compiler spec. is't defined"
#else
    #error "compiler is't specified"


    /** Определение встраиваемой (inline) функции  */
    #define LINLINE inline
    /** Определение упакованной структуры через атрибут в конце структуры (как в GCC).
         Если не используется, то этот макрос должен быть определен как пустой. */
    #define LATTRIBUTE_PACKED __attribute__ ((packed))    
#endif


/* теперь вместо определения содержимого\#pragma используются include-файлы
 * (так как предыдущий вариант работал не на всех компиляторах) */
#define LPRAGMA_PACKED       error: you must use new syntax for packed structs
#define LPRAGMA_PACK_RESTORE error: you must use new syntax for packed structs
#define LALIGN               error: you must use new syntax for aligned variables


#endif /* LCSPEC_H_ */
