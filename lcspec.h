/***************************************************************************//**
  @file lcspec.h
  Файл определяет набор макросов для выполнения действий, которые определяются
      специфичным для компилятора способом:
        упаковка стркутур
        выравние переменных
        определение inline-функций

  Константы вида LPRAGMA_XXX определяют содержимое директивы @c \#pragma, если она
  нужна. Если данное действие задается не через @c \#pragma, то константа LPRAGMA_XXX
  не определяется вообще.

  Остальные определения используются в коде как есть и должны быть всегда
  определены, пусть и пустым определением.

  Объявление упакованной структуры с использованием макросов из данного файла
  выполняется следующим образом:

    @code
    #ifdef LPRAGMA_PACKED
        #pragma LPRAGMA_PACKED
    #endif

    struct struct_name
    {
        ...
    } LATTRIBUTE_PACKED;
    typedef struct struct_name type_name;

    ...

    #ifdef LPRAGMA_PACK_RESTORE
        #pragma LPRAGMA_PACK_RESTORE
    #endif
    @endcode

  Выравнивание на n байт выполняется подобным образом:
    @code
    LALIGN(n) int i LATTRIBUTE_ALIGN(n);
    @endcode

  На настоящий момент реализованы определения для GCC, MSVC и LabWindow/CVI.

  @author Borisov Alexey <borisov@lcard.ru>
  @date   10.01.2011
*******************************************************************************/

#ifndef LCSPEC_H_
#define LCSPEC_H_

#if defined   (  __GNUC__  )
    /*------------------------ определения GCC -------------------------------*/
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED     __attribute__ ((packed))
    //#define LPRAGMA_PACKED   pack(1)
    //#define LPRAGMA_PACK_RESTORE  pack()
    #define LALIGN(n)
    #define LATTRIBUTE_ALIGN(n)   __attribute__ ((aligned (n)))
#elif defined ( _MSC_VER )
    /*------------------------ определения MSVC ------------------------------*/
    #define LINLINE                 __inline
    #define LATTRIBUTE_PACKED
    #define LPRAGMA_PACKED          pack(1)
    #define LPRAGMA_PACK_RESTORE    pack()
    #define LALIGN(n)               __declspec( align( n ) )
    #define LATTRIBUTE_ALIGN(n)
#elif defined ( _CVI_ )
    /*------------------- определения для LabWindow/CVI ----------------------*/
    #define LINLINE               inline
    #define LATTRIBUTE_PACKED
    #define LPRAGMA_PACKED        pack(1)
    #define LPRAGMA_PACK_RESTORE  pack()
    #define LALIGN(n)             __declspec( align( n ) )
    #define LATTRIBUTE_ALIGN(n)
#elif defined ( __CC_ARM   )
    #error "cc arm compiler spec. is't defined"
#elif defined ( __ICCARM__ )
    #error "iar compiler spec. is't defined"
#elif defined   (  __TASKING__  )
    #error "tasking compiler spec. is't defined"
#else
    #error "compiler is't specified"


    /** Определение встраиваемой (inline) функции  */
    #define LINLINE inline
    /** Определение упакованной структуры через атрибут в конце стркутуры (как в GCC).
         Если не используется, то этот макрос должен быть определен как пустой. */
    #define LATTRIBUTE_PACKED __attribute__ ((packed))
    /** Содержимое @c \#pragmа для указания, что дальше в файле идут упакованные
         данные. Если не используется, то макрос не должен быть определен */
    #define LPRAGMA_PACKED   pack(1)

    /** Содержимое @c \#pragmа для указания, что дальше в файле идут данные c
        режимом упаковки по-умолчанию.
        Если не используется, то макрос не должен быть определен */
    #define LPRAGMA_PACK_RESTORE  pack()

    /** Указание, что следующая переменная должна быть
        помещена по адресу, кратному n байт.
        Если не используется, то этот макрос должен быть определен как пустой. */
    #define LALIGN(n) __declspec( align( n ) )
    /** Определение, что переменная должна быть помещена по адресу, кратному n байт,
        через атрибут в конце определения этой переменной (как в GCC).
        Если не используется, то этот макрос должен быть определен как пустой. */
    #define LATTRIBUTE_ALIGN(n) __attribute__ ((aligned (n)))
#endif


#endif /* LCSPEC_H_ */
