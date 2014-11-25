/** @file TI_Fee_Cfg.c 
*   @brief FEE Driver Implementation File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This is the FEE configuration parameter file.
*
*   (c) Texas Instruments 2009-2014, All rights reserved.
*/



/* Include Files                                                              */

#include "ti_fee.h"



/*----------------------------------------------------------------------------*/
/* Fee Version Check                                                          */

 #if (TI_FEE_MAJOR_VERSION != 3U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_MAJOR_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_MAJOR_VERSION */
 #if (TI_FEE_MINOR_VERSION != 0U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_MINOR_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_MINOR_VERSION */
 #if (TI_FEE_PATCH_VERSION != 2U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_PATCH_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_PATCH_VERSION */

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
 #define FEE_START_SEC_CONST_UNSPECIFIED
 /*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h" 

/*----------------------------------------------------------------------------*/
/* TI Fee Configurations                                                     */

/** @struct Fee_VirtualSectorConfigType 	*/
/*  @brief Virtual Sector Configuration 	*/
const Fee_VirtualSectorConfigType Fee_VirtualSectorConfiguration[TI_FEE_NUMBER_OF_VIRTUAL_SECTORS] =
{

    /* Virtual Sector 1 */
    {
       /* Virtual sector number */      1U,
       /* Bank                  */      7U,      
       /* Start Sector          */      (Fapi_FlashSectorType)0U,
       /* End Sector            */      (Fapi_FlashSectorType)0U
    },
    /* Virtual Sector 2 */
    {
        /* Virtual sector number */     2U,
        /* Bank                  */     7U,
        /* Start Sector          */     (Fapi_FlashSectorType)1U,            
		/* End Sector            */     (Fapi_FlashSectorType)1U
    }
  
};


/* Block Configurations         */
/* SourceId : HL_Fee_SourceId_2 */
/* DesignId : HL_FEE_DesignId_3, HL_FEE_DesignId_8 */
/* Requirements : HL_FEE_SR2, HL_FEE_SR3, HL_FEE_SR4, HL_FEE_SR6, HL_FEE_SR85, HL_FEE_SR86
                  HL_FEE_SR87, HL_FEE_SR88, HL_FEE_SR89, HL_FEE_SR90, HL_FEE_SR91 */
const Fee_BlockConfigType Fee_BlockConfiguration[TI_FEE_NUMBER_OF_BLOCKS] =
{
        /*      Block 1 */
        {
               /* Block number                          */     1U, 
               /* Block size                            */     8U,
               /* Block immediate data used             */     TRUE,			   
               /* Number of write cycles                */     0x8U,
               /* Device Index                          */     0x00000000U,
               /* Number of DataSets                    */     1U,			   
               /* EEP number                            */     0U			   
        }

 
};

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*----------------------------------------------------------------------------*/
