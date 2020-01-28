/******************************************************************************
* NAME        : $Workfile $
*               $Revision $
*               $Date     $
*               $Logfile  $
*
* DESCRIPTION : Defines names for all the ASCII control charactrs.
*
* TARGET      : 16bit DOS 1.2 or better
* TOOLS       : Borland C++ 3.0 or 3.1
*
* MODIFICATION/REV HISTORY :
*
* 02/04/93 rgr Initial Version
*
******************************************************************************/

#ifndef ASCII_H
#define ASCII_H

/*--------------------------------------------------------------------------*/

#define A_NUL  '\000' /* 0 */
#define A_SOH  '\001' /* 1 */
#define A_STX  '\002' /* 2 */
#define A_ETX  '\003' /* 3 */
#define A_EOT  '\004' /* 4 */
#define A_ENQ  '\005' /* 5 */
#define A_ACK  '\006' /* 6 */
#define A_BEL  '\007' /* 7 */
#define A_BS   '\010' /* 8 */
#define A_TAB  '\011' /* 9 */
#define A_HT   '\011' /* 9 */
#define A_LF   '\012' /* 10 */
#define A_VT   '\013' /* 11 */
#define A_FF   '\014' /* 12 */
#define A_CR   '\015' /* 13 */
#define A_SO   '\016' /* 14 */
#define A_SI   '\017' /* 15 */
#define A_DLE  '\020' /* 16 */
#define A_DC1  '\021' /* 17 */
#define A_XON  '\021' /* 17   same as A_DC1 */
#define A_DC2  '\022' /* 18 */
#define A_DC3  '\023' /* 19 */
#define A_XOFF '\023' /* 19   same as A_DC3 */
#define A_DC4  '\024' /* 20 */
#define A_NAK  '\025' /* 21 */
#define A_SYN  '\026' /* 22 */
#define A_ETB  '\027' /* 23 */
#define A_CAN  '\030' /* 24 */
#define A_EM   '\031' /* 25 */
#define A_SUB  '\032' /* 26 */
#define A_ESC  '\033' /* 27 */
#define A_FS   '\034' /* 28 */
#define A_GS   '\035' /* 29 */
#define A_RS   '\036' /* 30 */
#define A_US   '\037' /* 31 */
#define A_SP   '\040' /* 32   SPACE */
#define A_DEL  '\177' /* 0x7F DELETE */

#endif
